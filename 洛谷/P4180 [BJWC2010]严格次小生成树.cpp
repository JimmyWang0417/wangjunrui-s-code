#include <cstdio>
#include <cstring>
#include <algorithm>
#define re register
#define ll long long
using namespace std;
namespace IO
{
	const int SIZE=30*3e5;
	char ibuf[SIZE],*iS,*iT;
#define gc() (char)(iS==iT?(iT=(iS=ibuf)+fread(ibuf,1,SIZE,stdin),iS==iT?EOF:*iS++):*iS++)
	template<typename T>
	inline void read(T & x)
	{
		x=0;
		bool b=false;
		char ch=gc();
		while((ch<'0'||ch>'9')&&ch^'-')
			ch=gc();
		if(ch=='-')
		{
			b=true;
			ch=gc();
		}
		while(ch>='0'&&ch<='9')
		{
			x=(x<<1)+(x<<3)+(ch^'0');
			ch=gc();
		}
		if(b)
			x=~x+1;
		return;
	}
	template<typename T,typename ...T1>
	inline void read(T&x,T1&...x1)
	{
		read(x);
		read(x1...);
	}
#undef gc
}
using IO::read;
const int N=1e5+5,M=3e5+5,INF=0x3f3f3f3f;
int n,m;
struct node
{
	int u,v,w;
	inline bool operator < (const node&rhs)const
	{
		return w<rhs.w;
	}
} a[M];
struct Tree
{
	int ch[2],fa;
	int size;
	int val,max,max2;
	bool reverse;
} tree[N+M];
#define lc(x) tree[x].ch[0]
#define rc(x) tree[x].ch[1]
#define fa(x) tree[x].fa
#define rev(x) tree[x].reverse
#define check(x) (rc(fa(x))==x)
#define nroot(x) (lc(fa(x))==x||rc(fa(x))==x)
inline void pushup(int x)
{
	tree[x].size=tree[lc(x)].size+tree[rc(x)].size+1;
	tree[x].max=max(tree[x].val,max(tree[lc(x)].max,tree[rc(x)].max));
	tree[x].max2=max(tree[lc(x)].max2,tree[rc(x)].max2);
	if(tree[x].val^tree[x].max)
		tree[x].max2=max(tree[x].max2,tree[x].val);
	if(tree[lc(x)].max^tree[x].max)
		tree[x].max2=max(tree[x].max2,tree[lc(x)].max);
	if(tree[rc(x)].max^tree[x].max)
		tree[x].max2=max(tree[x].max2,tree[rc(x)].max);
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
signed main()
{
	read(n,m);
	for(re int i=1; i<=m; ++i)
		read(a[i].u,a[i].v,a[i].w);
	stable_sort(a+1,a+1+m);
	ll cnt=0;
	int ans=INF;
	for(re int i=1; i<=m; ++i)
	{
		int &u=a[i].u,&v=a[i].v,&w=a[i].w;
		if(findroot(u)==findroot(v))
		{
			split(u,v);
			ans=min(ans,tree[v].max^w?w-tree[v].max:w-tree[v].max2);
		}
		else
		{
			cnt+=w;
			tree[n+i].val=tree[n+i].max=w;
			link(u,n+i),link(n+i,v);
		}
	}
//	printf("%lld\n",cnt);
	printf("%lld\n",ans+cnt);
	return 0;
}
