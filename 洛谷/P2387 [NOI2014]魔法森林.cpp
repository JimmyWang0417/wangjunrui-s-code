#include <cstdio>
#include <algorithm>
#define re register
#define ll long long
#define rep(i,a,b) for(re int i=a;i<=b;++i)
#define per(i,a,b) for(re int i=a;i>=b;--i)
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
const int N=5e4+5,M=1e5+5;
struct node
{
	int u,v,w1,w2;
	inline bool operator <(const node&rhs)const
	{
		return w1<rhs.w1;
	}
	inline bool operator >(const node&rhs)const
	{
		return w2>rhs.w2;
	}
} a[M];
int n,m;
struct Tree
{
	int ch[2],fa;
	int size;
	int id,max;
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
	return a[x]>a[y]?x:y;
}
inline void pushup(int x)
{
	tree[x].size=tree[lc(x)].size+tree[rc(x)].size+1;
	tree[x].max=getmax(tree[x].id,getmax(tree[lc(x)].max,tree[rc(x)].max));
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
	tree[x].ch[k^1]=y;
	tree[y].ch[k]=w;
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
inline void cut(int id)
{
	int &x=a[id].u,&y=a[id].v,now=id+n;
	split(x,y);
	splay(now);
	lc(now)=rc(now)=fa(x)=fa(y)=0;
	pushup(now);
}
signed main()
{
	read(n,m);
	for(re int i=1; i<=m; ++i)
	{
		read(a[i].u,a[i].v,a[i].w1,a[i].w2);
		tree[i+n].id=i;
	}
	for(re int i=1; i<=n+m; ++i)
		pushup(i);
	sort(a+1,a+1+m);
	int ans=0x3f3f3f3f;
	for(re int i=1; i<=m; ++i)
	{
		int &u=a[i].u,&v=a[i].v;
		if(findroot(u)==findroot(v))
		{
			split(u,v);
			int id=tree[v].max;
			if(a[id]>a[i])
			{
				cut(id);
				link(u,i+n),link(i+n,v);
			}
		}
		else
			link(u,i+n),link(i+n,v);
		if(findroot(1)==findroot(n))
		{
			split(1,n);
			ans=min(ans,a[i].w1+a[tree[n].max].w2);
		}
	}
	printf("%d\n",ans==0x3f3f3f3f?-1:ans);
	return 0;
}

