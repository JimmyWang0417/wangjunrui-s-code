#include <cstdio>
#include <algorithm>
#define re register
#define ll long long
using namespace std;
template<typename T>
inline void read(T&x)
{
	x=0;
	char s=(char)getchar();
	bool f=false;
	while(!(s>='0'&&s<='9'))
	{
		if(s=='-')
			f=true;
		s=(char)getchar();
	}
	while(s>='0'&&s<='9')
	{
		x=(x<<1)+(x<<3)+s-'0';
		s=(char)getchar();
	}
	if(f)
		x=(~x)+1;
}
template<typename T,typename ...T1>
inline void read(T&x,T1&...x1)
{
	read(x);
	read(x1...);
}
const int N=5005,M=2e5+5;
struct node
{
	int u,v,w;
} a[M];
struct Tree
{
	int ch[2],fa;
	int size;
	int id,mx;
	bool reverse;
} tree[N+M];
#define lc(x) tree[x].ch[0]
#define rc(x) tree[x].ch[1]
#define fa(x) tree[x].fa
#define rev(x) tree[x].reverse
inline bool check(int x)
{
	return rc(fa(x))==x;
}
inline bool nroot(int x)
{
	return lc(fa(x))==x||rc(fa(x))==x;
}
inline int getmax(int x,int y)
{
	return a[x].w>a[y].w?x:y;
}
inline void pushup(int x)
{
	tree[x].size=tree[lc(x)].size+tree[rc(x)].size+1;
	tree[x].mx=getmax(tree[x].id,getmax(tree[lc(x)].mx,tree[rc(x)].mx));
}
inline void pushdown(int x)
{
	if(rev(x))
	{
		swap(lc(x),rc(x));
		if(lc(x))
			rev(lc(x))^=1;
		if(rc(x))
			rev(rc(x))^=1;
		rev(x)=false;
	}
}
inline void rotate(int x)
{
	int y=fa(x),z=fa(y),k=check(x),w=tree[x].ch[k^1];
	if(nroot(y))
		tree[z].ch[check(y)]=x;
	tree[y].ch[k]=w;
	tree[x].ch[k^1]=y;
	if(w)
		fa(w)=y;
	fa(y)=x;
	fa(x)=z;
	pushup(y),pushup(x);
}
int st[N];
inline void splay(int x)
{
	int top;
	st[top=1]=x;
	for(re int y=x; nroot(y); y=fa(y))
		st[++top]=fa(y);
	while(top)
		pushdown(st[top--]);
	while(nroot(x))
	{
		if(nroot(fa(x)))
			rotate(check(x)==check(fa(x))?fa(x):x);
		rotate(x);
	}
}
inline void access(int x)
{
	for(re int y=0; x; x=fa(y=x))
	{
		splay(x);
		rc(x)=y;
		pushup(x);
	}
}
inline void makeroot(int x)
{
	access(x);
	splay(x);
	rev(x)^=1;
}
inline int findroot(int x)
{
	access(x);
	splay(x);
	while(pushdown(x),lc(x))
		x=lc(x);
	splay(x);
	return x;
}
inline void split(int x,int y)
{
	makeroot(x);
	access(y);
	splay(y);
}
inline void link(int x,int y)
{
	makeroot(x);
	fa(x)=y;
}
inline void cut(int x,int y)
{
	split(x,y);
	lc(y)=fa(x)=0;
	pushup(y);
}
signed main()
{
	int cnt=0,n,m;
	read(n,m);
	for(re int i=1; i<=m; ++i)
		read(a[i].u,a[i].v,a[i].w);
	ll ans=0;
	for(re int i=1; i<=m; ++i)
	{
		int &x=a[i].u,&y=a[i].v,&w=a[i].w;
		tree[i+n].id=i;
		makeroot(x);
		if(x==findroot(y))
		{
			split(x,y);
			int id=tree[y].mx;
			if(a[id].w>w)
			{
				ans=ans-a[id].w+w;
				cut(a[id].u,id+n),cut(id+n,a[id].v);
				link(x,n+i),link(n+i,y);
			}
		}
		else
		{
			link(x,n+i),link(n+i,y);
			ans+=w;
			++cnt;
		}
	}
	if(cnt==n-1)
		printf("%lld\n",ans);
	else
		printf("orz\n");
	return 0;
}
