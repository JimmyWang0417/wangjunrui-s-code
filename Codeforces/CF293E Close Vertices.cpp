#include <bits/stdc++.h>
#define int ll
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
const int N=1e6+5;
int n,m,q;
struct Edge
{
	int next,to,dis;
} edge[N*2];
int head[N],num_edge;
inline void add_edge(int from,int to,int dis)
{
	edge[++num_edge].next=head[from];
	edge[num_edge].to=to;
	edge[num_edge].dis=dis;
	head[from]=num_edge;
//	if(num_edge&1)
//		printf("%d %d %d\n",from,to,dis);
}
struct Tree_array
{
	int sum[N];
	inline void update(int pos,int val)
	{
		for(int i=pos; i<=m+1; i+=lowbit(i))
			sum[i]+=val;
	}
	inline int query(int pos)
	{
		int res=0;
		for(int i=pos; i>0; i-=lowbit(i))
			res+=sum[i];
		return res;
	}
} tree;
int maxsize[N],size[N],sum,root;
bool vis[N];
inline void getroot(int u,int _fa)
{
	size[u]=1;
	maxsize[u]=0;
	for(int i=head[u]; i; i=edge[i].next)
	{
		int &v=edge[i].to;
		if(vis[v]||v==_fa)
			continue;
		getroot(v,u);
		size[u]+=size[v];
		maxsize[u]=max(maxsize[u],size[v]);
	}
	maxsize[u]=max(maxsize[u],sum-size[u]);
	if(maxsize[u]<maxsize[root])
		root=u;
}
inline void dfs(int u,int _fa)
{
	size[u]=1;
	for(int i=head[u]; i; i=edge[i].next)
	{
		int &v=edge[i].to;
		if(vis[v]||v==_fa)
			continue;
		dfs(v,u);
		size[u]+=size[v];
	}
}
int cnt;
struct node
{
	int dep,dis;
	node(int _dep=0,int _dis=0):dep(_dep),dis(_dis) {}
	inline bool operator <(const node &rhs)const
	{
		return dis<rhs.dis;
	}
} a[N];
int dis[N],dep[N];
inline void calc(int u,int _fa)
{
	if(dep[u]<=m)
		a[++cnt]=node(dep[u],dis[u]);
	for(int i=head[u]; i; i=edge[i].next)
	{
		int &v=edge[i].to;
		if(vis[v]||v==_fa)
			continue;
		dep[v]=dep[u]+1;
		dis[v]=dis[u]+edge[i].dis;
		calc(v,u);
	}
}
inline ll get(int u,int initdep,int initdis)
{
	cnt=0;
	dep[u]=initdep,dis[u]=initdis;
	calc(u,0);
	sort(a+1,a+1+cnt);
	int l=1,r=cnt;
//	for(int i=1; i<=cnt; ++i)
//		printf(" %d %d\n",a[i].dep,a[i].dis);
//	putchar('\n');
	for(int i=1; i<=cnt; ++i)
		tree.update(a[i].dep+1,1);
	ll res=0;
	while(l<r)
	{
		if(a[l].dis+a[r].dis<=q)
		{
			tree.update(a[l].dep+1,-1);
			res+=tree.query(m-a[l].dep+1);
			++l;
		}
		else
		{
			tree.update(a[r].dep+1,-1);
			--r;
		}
	}
	tree.update(a[l].dep+1,-1);
	return res;
}
ll ans=0;
inline void solve(int u)
{
	getroot(u,0);
//	printf("%d %d %d %d\n",u,root,sum,maxsize[u],maxsize[root]);
	u=root;
	dfs(u,0);
	vis[u]=true;

	ans+=get(u,0,0);

	for(int i=head[u]; i; i=edge[i].next)
	{
		int &v=edge[i].to;
		if(vis[v])
			continue;
		ans-=get(v,1,edge[i].dis);
		maxsize[root=0]=sum=size[v];
		solve(v);
	}
}
signed main()
{
	read(n,m,q);
	for(int i=2; i<=n; ++i)
	{
		int fa,w;
		read(fa,w);
		add_edge(fa,i,w);
		add_edge(i,fa,w);
	}
	maxsize[root=0]=sum=n;
	solve(1);
	printf("%lld\n",ans);
	return 0;
}


