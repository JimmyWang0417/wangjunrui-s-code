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
const int N=1005,M=2e5+5,INF=0x7fffffff;
class mindistance
{
	public:
		struct Edge
		{
			int next,to,dis;
		} edge[M];
		int head[N],num_edge;
		inline void add_edge(int from,int to,int d,bool flag=true)
		{
			edge[++num_edge].next=head[from];
			edge[num_edge].to=to;
			edge[num_edge].dis=d;
			head[from]=num_edge;
			if(flag)
				add_edge(to,from,d,false);
		}
		ll dis[N];
		bool vis[N];
		inline void dijkstra()
		{
			priority_queue<pair<ll,int>,vector<pair<ll,int> >,greater<pair<ll,int> > >q;
			memset(dis,0x3f,sizeof(dis));
			q.push(make_pair(dis[1]=0,1));
			while(!q.empty())
			{
				int u=q.top().second;
				q.pop();
				if(vis[u])
					continue;
				vis[u]=true;
				for(int i=head[u]; i; i=edge[i].next)
				{
					int &v=edge[i].to;
					if(dis[v]>dis[u]+edge[i].dis)
					{
						dis[v]=dis[u]+edge[i].dis;
						q.push(make_pair(dis[v],v));
					}
				}
			}
		}
		inline void work(int m)
		{
			for(int i=1; i<=m; ++i)
			{
				int u,v,w;
				read(u,v,w);
				add_edge(u,v,w);
			}
			dijkstra();
		}
} dijkstra;
struct Edge
{
	int next,to,cap,flow;
} edge[M*2];
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
int n,m;
#define s n+1
#define t n
int dis[N];
bool vis[N];
int cur[N];
inline bool bfs()
{
	memset(dis,0,sizeof(dis));
	memset(vis,0,sizeof(vis));
	memcpy(cur,head,sizeof(head));
	queue<int>q;
	dis[s]=1;
	q.push(s);
	while(!q.empty())
	{
		int u=q.front();
		q.pop();
//		printf(" %d\n",u);
		if(u==t)
			return true;
		for(int i=head[u]; i; i=edge[i].next)
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
	if(u==t)
		return flow;
	if(!flow)
		return 0;
	vis[u]=true;
	int res=0;
	for(int &i=cur[u]; i; i=edge[i].next)
	{
		int &v=edge[i].to;
		if(!vis[v]&&dis[v]==dis[u]+1&&edge[i].cap>edge[i].flow)
		{
			int f=dinic(v,min(flow,edge[i].cap-edge[i].flow));
			if(f)
			{
				edge[i].flow+=f;
				edge[i^1].flow-=f;
				flow-=f;
				res+=f;
				if(!flow)
				{
					vis[u]=false;
					break;
				}
			}
		}
	}
	return res;
}
signed main()
{
	read(n,m);
	dijkstra.work(m);
//	for(int i=1; i<=n; ++i)
//		printf("%lld ",dijkstra.dis[i]);
//	putchar('\n');
	for(int u=1; u<=n; ++u)
	{
		int val;
		read(val);
		add_edge(u,u+n,val);
//		printf("%d:\n",u);
		for(int i=dijkstra.head[u]; i; i=dijkstra.edge[i].next)
		{
			int &v=dijkstra.edge[i].to;
//			printf("%d ",v);
			if(dijkstra.dis[v]==dijkstra.dis[u]+dijkstra.edge[i].dis)
				add_edge(u+n,v,INF);
		}
//		putchar('\n');
	}
//	printf("%d\n",num_edge);
	ll ans=0;
	while(bfs())
	{
//		printf("1\n");
		ans+=dinic(s,INF);
	}
	printf("%lld\n",ans);
	return 0;
}


