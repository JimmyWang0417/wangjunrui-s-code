#include <bits/stdc++.h>
#define lowbit(x) ((x)&(-(x)))
#define re register
#define ll long long
#define ull unsigned long long
#define rep(i,a,b) for(re int i=a;i<=b;++i)
#define per(i,a,b) for(re int i=a;i>=b;--i)
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
template<typename T>
inline void clear(T*array,int l,int r,int val)
{
	memset(&array[l],val,sizeof(T)*(r-l+1));
}
using namespace std;
const int N=2e5+5;
const ll INF=1e18;
struct Edge
{
	int next,to;
} edge[N*2];
int head[N],num_edge;
inline void add_edge(int from,int to)
{
	edge[++num_edge].next=head[from];
	edge[num_edge].to=to;
	head[from]=num_edge;
}
struct node
{
	int l,r;
	int dist;
	ll p,g;
} tree[N];
int cnt,root[N];
#define lc(x) tree[x].l
#define rc(x) tree[x].r
inline void pushup(int x)
{
	tree[x].dist=tree[rc(x)].dist+1;
}
inline int newnode(ll p,ll g)
{
	int x=++cnt;
	lc(x)=rc(x)=0;
	tree[x].p=p;
	tree[x].g=g;
	pushup(x);
	return x;
}
inline int merge(int x,int y)
{
	if(!x||!y)
		return x|y;
	if(tree[x].p>tree[y].p)
		swap(x,y);
	rc(x)=merge(rc(x),y);
	if(tree[lc(x)].dist<tree[rc(x)].dist)
		swap(lc(x),rc(x));
	pushup(x);
	return x;
}
int n,t,a[N];
inline void dfs(int u,int fa)
{
	for(int i=head[u]; i; i=edge[i].next)
	{
		int &v=edge[i].to;
		if(v==fa)
			continue;
		dfs(v,u);
		root[u]=merge(root[u],root[v]);
	}
	if(u==t)
		root[u]=merge(root[u],newnode(0,INF));
	ll p=0,g=0;
	if(a[u]>=0)
		g=a[u];
	else
		p=-a[u];
	while(root[u]&&((p>tree[root[u]].p&&p<=g)||p>g))
	{
		if(tree[root[u]].p>g)
		{
			p+=tree[root[u]].p-g;
			g=tree[root[u]].g;
		}
		else
			g+=tree[root[u]].g-tree[root[u]].p;
		root[u]=merge(lc(root[u]),rc(root[u]));
	}
	if(p>g)
		root[u]=0;
	else
		root[u]=merge(root[u],newnode(p,g));
}
inline void work()
{
	read(n,t);
	memset(head,0,sizeof(head));
	memset(root,0,sizeof(root));
	cnt=num_edge=0;

	for(int i=1; i<=n; ++i)
		read(a[i]);
	for(int i=1; i<n; ++i)
	{
		int u,v;
		read(u,v);
		add_edge(u,v);
		add_edge(v,u);
	}
	dfs(1,1);
//	for(int i=1; i<=n; ++i)
//		printf("%d ",root[i]);
//	putchar('\n');
	ll ans=0;
	while(root[1]&&tree[root[1]].p<=ans)
	{
//		printf("%lld %lld\n",tree[root[1]].p,tree[root[1]].g);
		ans+=-tree[root[1]].p+tree[root[1]].g;
		root[1]=merge(lc(root[1]),rc(root[1]));
	}
	puts(ans>INF/2?"escaped":"trapped");
}
signed main()
{
	freopen("escape.in","r",stdin),freopen("escape.out","w",stdout);
	int T;
	read(T);
	while(T--)
		work();
	return 0;
}


