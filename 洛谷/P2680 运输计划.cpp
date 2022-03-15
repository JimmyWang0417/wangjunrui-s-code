#include <cmath>
#include <cstdio>
#include <bitset>
#include <cstring>
#include <algorithm>
#define lowbit(x) (x&(-x))
#define re register
#define ll long long
#define ui unsigned int
#define ull unsigned long long
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
const int N=3e5+5;
int n,m;
struct node
{
	int u,v,w;
	inline bool operator <(const node&rhs)const
	{
		return w>rhs.w;
	}
} a[N];
struct Queue
{
	int x,y,lca;
	ll dis;
	inline bool operator <(const Queue&rhs)const
	{
		return dis>rhs.dis;
	}
} q[N];
struct Edge
{
	int next,to,dis;
	Edge(int ne=0,int t=0,int d=0):next(ne),to(t),dis(d) {}
} edge[N<<1];
int head[N],num_edge;
inline void add_edge(int from,int to,int dis)
{
	edge[++num_edge]=Edge(head[from],to,dis);
	head[from]=num_edge;
}
int Log[N];
int fa[N][20],dep[N];
int dfn[N],low[N],dfstime;
int diff[N],sum[N];
ll dist[N];
inline void dfs(int u,int _fa)
{
	dfn[u]=++dfstime;
	fa[u][0]=_fa;
	dep[u]=dep[_fa]+1;
	for(re int i=0; i<Log[dep[u]]; ++i)
		fa[u][i+1]=fa[fa[u][i]][i];
	for(re int i=head[u]; i; i=edge[i].next)
	{
		int &v=edge[i].to;
		if(v==_fa)
			continue;
		dist[v]=dist[u]+edge[i].dis;
		dfs(v,u);
	}
	low[u]=dfstime;
}
inline int LCA(int x,int y)
{
	if(dep[x]<dep[y])
		swap(x,y);
	for(re int i=Log[dep[x]]; i>=0; --i)
		if(dep[fa[x][i]]>=dep[y])
			x=fa[x][i];
	if(x==y)
		return x;
	for(re int i=Log[dep[x]]; i>=0; --i)
		if(fa[x][i]!=fa[y][i])
			x=fa[x][i],y=fa[y][i];
	return fa[x][0];
}
#define ask(x) (sum[low[x]]-sum[dfn[x]-1])
inline void clear()
{
	memset(head,num_edge=0,sizeof(head));
	memset(diff,0,sizeof(diff));
	memset(dist,0,sizeof(dist));
}
inline bool check(ll val)
{
	clear();
	int cnt=0;
	for(re int i=1; i<=m; ++i)
	{
		if(q[i].dis<=val)
			break;
		++cnt;
		int &x=q[i].x,&y=q[i].y,&lca=q[i].lca;
		++diff[dfn[x]],++diff[dfn[y]];
		diff[dfn[lca]]-=2;
	}
//	printf("-----%d %d %d ",q[1].dis,val,cnt);
	for(re int i=1; i<=n; ++i)
		sum[i]=sum[i-1]+diff[i];
	int id=0;
	for(re int i=1; i<n; ++i)
		if(ask(a[i].u)>=cnt)
		{
			id=i;
			break;
		}
//	printf("%d\n",id);
	if(!id||q[1].dis-a[id].w>val)
		return false;
	return true;
}
signed main()
{
	read(n,m);
	Log[0]=-1;
	for(re int i=1; i<=n; ++i)
		Log[i]=Log[i>>1]+1;
	for(re int i=1; i<n; ++i)
	{
		int &u=a[i].u,&v=a[i].v,&w=a[i].w;
		read(u,v,w);
		add_edge(u,v,w);
		add_edge(v,u,w);
	}
	dfs(1,0);
	for(re int i=1; i<=m; ++i)
	{
		int &x=q[i].x,&y=q[i].y,&lca=q[i].lca;
		read(x,y);
		lca=LCA(x,y);
		q[i].dis=dist[x]+dist[y]-(dist[lca]<<1);
		++diff[dfn[x]],++diff[dfn[y]];
		diff[dfn[lca]]-=2;
//		printf("%d %d %d %d\n",x,y,lca,fa[lca][0]);
	}
	for(re int i=1; i<=n; ++i)
	{
		int &u=a[i].u,&v=a[i].v;
		if(dep[u]<dep[v])
			swap(u,v);
	}
	sort(q+1,q+1+m);
	sort(a+1,a+1+n);
	for(re int i=1; i<=n; ++i)
		sum[i]=sum[i-1]+diff[i];
	ll l=0,r=3e9,ans=3e9;
	while(l<=r)
	{
		ll mid=(l+r)>>1;
		if(check(mid))
		{
			r=mid-1;
			ans=mid;
		}
		else
			l=mid+1;
//		printf("%lld %lld\n",l,r);
	}
	printf("%lld\n",ans);
	return 0;
}

