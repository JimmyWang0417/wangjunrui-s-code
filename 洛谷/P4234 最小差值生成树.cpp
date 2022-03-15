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
const int N=5e4+5,M=2e5+5,INF=0x3f3f3f3f;
int n,m;
struct node
{
	int u,v,w;
	inline bool operator <(const node&rhs)const
	{
		return w>rhs.w;
	}
} a[M];
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
	return a[x].w>a[y].w?x:y;
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
inline void cut(int x,int y)
{
	split(x,y);
	lc(y)=fa(x)=0;
	pushup(y);
}
bool vis[M];
signed main()
{
	read(n,m);
	for(re int i=1; i<=m; ++i)
	{
		read(a[i].u,a[i].v,a[i].w);
		tree[i+n].id=i;
	}
	sort(a+1,a+1+m);
	for(re int i=n+m; i>=1; --i)
		pushup(i);
//	for(re int i=1; i<=m; ++i)
//		printf("\n%d %d %d",a[i].u,a[i].v,a[i].w);
//	putchar('\n');
	int cnt=0,ans=INF;
	for(re int i=1,head=1; i<=m; ++i)
	{
		int &u=a[i].u,&v=a[i].v,&w=a[i].w;
		makeroot(u);
		if(u==findroot(v))
		{
			split(u,v);
			int id=tree[v].max;
//			printf("----%d\n",a[id].w);
			if(a[id].w>w)
			{
				vis[id]=true;
				cut(a[id].u,id+n),cut(id+n,a[id].v);
				link(u,i+n),link(i+n,v);
				while(vis[head])
					++head;
				if(cnt==n-1)
					ans=min(ans,a[head].w-w);
			}
			else
				vis[i]=true;
		}
		else
		{
			++cnt;
			link(u,i+n),link(i+n,v);
			if(cnt==n-1)
				ans=min(ans,a[head].w-w);
		}
//		printf("%d %d\n",cnt,head);
	}
	printf("%d\n",ans);
	return 0;
}

