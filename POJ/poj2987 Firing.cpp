#include <cstdio>
#include <queue>
#include <iostream>
#include <cstring>
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
	char ss=(char)getchar();
	bool f=false;
	while(!(ss>='0'&&ss<='9'))
	{
		if(ss=='-')
			f=true;
		ss=(char)getchar();
	}
	while(ss>='0'&&ss<='9')
	{
		x=(x<<1)+(x<<3)+ss-'0';
		ss=(char)getchar();
	}
	if(f)
		x=(~x)+1;
}
template<typename T>
inline void clear(T*a,int l,int r,int val)
{
	memset(&a[l],val,sizeof(T)*(r-l+1));
}
const int N=5e3+5,M=6e4+5,INF=0x7fffffff;
int n,m;
struct Edge
{
	int next,to,cap,flow;
} edge[(N+M)<<1];
int head[N],num_edge=1;
inline void add_edge(int from,int to,int cap,bool flag=true)
{
	edge[++num_edge].next=head[from];
	edge[num_edge].to=to;
	edge[num_edge].cap=cap;
	edge[num_edge].flow=0;
	head[from]=num_edge;
	if(flag)
		add_edge(to,from,0,false);
}
#define s 0
#define t (n+1)
int dis[N],cur[N];
inline bool bfs()
{
	std::queue<int>q;
	q.push(s);
	memset(dis,0,sizeof(dis));
	dis[s]=1;
	for(re int i=s; i<=t; ++i)
		cur[i]=head[i];
	while(!q.empty())
	{
		int u=q.front();
		if(u==t)
			return true;
		q.pop();
		for(re int i=head[u]; i; i=edge[i].next)
		{
			int &v=edge[i].to;
			if(!dis[v]&&edge[i].cap>edge[i].flow)
			{
				dis[v]=dis[u]+1;
				q.push(v);
			}
		}
	}
	return false;
}
inline int dinic(int u,int flow)
{
	if(u==t||!flow)
		return flow;
	int res=0;
	for(int &i=cur[u]; i; i=edge[i].next)
	{
		int &v=edge[i].to;
		if(dis[v]==dis[u]+1&&edge[i].cap>edge[i].flow)
		{
			int f=dinic(v,std::min(flow,edge[i].cap-edge[i].flow));
			if(f)
			{
				res+=f;
				edge[i].flow+=f;
				edge[i^1].flow-=f;
				flow-=f;
			}
			if(!flow)
				return res;
		}
	}
	return res;
}
int cnt;
bool vis[N];
inline void dfs(int u)
{
//	printf("%d ",u);
	for(re int i=head[u]; i; i=edge[i].next)
	{
		int &v=edge[i].to;
		if(!vis[v]&&edge[i].cap>edge[i].flow)
		{
			vis[v]=true;
			++cnt;
			dfs(v);
		}
	}
}
signed main()
{
	read(n),read(m);
	ll ans=0;
	for(re int i=1; i<=n; ++i)
	{
		int val;
		read(val);
		if(val>=0)
		{
			add_edge(s,i,val);
			ans+=val;
		}
		else
			add_edge(i,t,-val);
	}
	for(re int i=1; i<=m; ++i)
	{
		int u,v;
		read(u),read(v);
		add_edge(u,v,INF);
	}
	while(bfs())
		ans-=dinic(s,INF);
	vis[s]=true;
	dfs(s);
	printf("%d %lld\n",cnt,ans);
	return 0;
}


