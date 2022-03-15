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
const int N=1e5+5;
const ll INF=4557430888798830399;
const ll MAXFLOW=0x7fffffff;
struct Edge
{
	int next,to,cap,flow,cost;
} edge[N];
int head[N],num_edge=1;
inline void add_edge(int from,int to,int cap,int cost,bool flag=true)
{
	edge[++num_edge].next=head[from];
	edge[num_edge].to=to;
	edge[num_edge].cap=cap;
	edge[num_edge].flow=0;
	edge[num_edge].cost=cost;
	head[from]=num_edge;
	if(flag)
		add_edge(to,from,0,-cost,false);
}
int s,t,cnt;
ll dis[N];
int cur[N];
bitset<N>exist;
inline bool spfa()
{
	memcpy(cur,head,sizeof(cur));
	memset(dis,~0x3f,sizeof(dis));
	exist.reset();

	queue<int>q;
	dis[s]=0;
	q.push(s);
	while(!q.empty())
	{
		int u=q.front();
		q.pop();
		exist[u]=false;
		for(int i=head[u]; i; i=edge[i].next)
		{
			int &v=edge[i].to;
			if(dis[v]<dis[u]+edge[i].cost&&edge[i].cap>edge[i].flow)
			{
				dis[v]=dis[u]+edge[i].cost;
				if(!exist[v])
				{
					exist[v]=true;
					q.push(v);
				}
			}
		}
	}
	return dis[t]>~INF/2;
}
inline int dinic(int u,int flow)
{
	if(u==t)
		return flow;
	if(!flow)
		return 0;
	exist[u]=true;
	int res=0;
	for(int &i=cur[u]; i; i=edge[i].next)
	{
		int &v=edge[i].to;
		if(edge[i].cap>edge[i].flow&&dis[v]==dis[u]+edge[i].cost&&!exist[v])
		{
			int f=dinic(v,min(flow,edge[i].cap-edge[i].flow));
			if(f)
			{
				edge[i].flow+=f;
				edge[i^1].flow-=f;
				res+=f;
				flow-=f;
				if(!flow)
				{
					exist[u]=false;
					break;
				}
			}
		}
	}
	return res;
}
int n,m;
int a[55][55];
int id[55][55];
inline void work1()
{
	s=0,t=cnt*2+1;

	for(int i=1; i<=m; ++i)
		add_edge(s,id[1][i],1,0);
	for(int i=1; i<n; ++i)
		for(int j=1; j<i+m; ++j)
		{
			add_edge(id[i][j],id[i][j]+cnt,1,a[i][j]);
			add_edge(id[i][j]+cnt,id[i+1][j],1,0);
			add_edge(id[i][j]+cnt,id[i+1][j+1],1,0);
		}
	for(int i=1; i<n+m; ++i)
	{
		add_edge(id[n][i],id[n][i]+cnt,1,a[n][i]);
		add_edge(id[n][i]+cnt,t,1,0);
	}


	ll ans=0;
	while(spfa())
		ans+=dinic(s,MAXFLOW)*dis[t];
	printf("%lld\n",ans);
	memset(head,0,sizeof(head));
	num_edge=1;
}
inline void work2()
{
	s=0,t=cnt*2+1;

	for(int i=1; i<=m; ++i)
		add_edge(s,id[1][i],1,0);
	for(int i=1; i<n; ++i)
		for(int j=1; j<i+m; ++j)
		{
			add_edge(id[i][j],id[i][j]+cnt,MAXFLOW,a[i][j]);
			add_edge(id[i][j]+cnt,id[i+1][j],1,0);
			add_edge(id[i][j]+cnt,id[i+1][j+1],1,0);
		}
	for(int i=1; i<n+m; ++i)
	{
		add_edge(id[n][i],id[n][i]+cnt,MAXFLOW,a[n][i]);
		add_edge(id[n][i]+cnt,t,MAXFLOW,0);
	}

	ll ans=0;
	while(spfa())
		ans+=dinic(s,MAXFLOW)*dis[t];
	printf("%lld\n",ans);
	memset(head,0,sizeof(head));
	num_edge=1;
}
inline void work3()
{

	s=0,t=cnt*2+1;

	for(int i=1; i<=m; ++i)
		add_edge(s,id[1][i],1,0);
	for(int i=1; i<n; ++i)
		for(int j=1; j<i+m; ++j)
		{
			add_edge(id[i][j],id[i][j]+cnt,MAXFLOW,a[i][j]);
			add_edge(id[i][j]+cnt,id[i+1][j],MAXFLOW,0);
			add_edge(id[i][j]+cnt,id[i+1][j+1],MAXFLOW,0);
		}
	for(int i=1; i<n+m; ++i)
	{
		add_edge(id[n][i],id[n][i]+cnt,MAXFLOW,a[n][i]);
		add_edge(id[n][i]+cnt,t,MAXFLOW,0);
	}
	
	ll ans=0;
	while(spfa())
		ans+=dinic(s,MAXFLOW)*dis[t];
	printf("%lld\n",ans);
//	printf("%d\n",edge[num_edge-1].flow);
	memset(head,0,sizeof(head));
	num_edge=1;
}
signed main()
{
	read(m,n);
	for(int i=1; i<=n; ++i)
		for(int j=1; j<i+m; ++j)
		{
			read(a[i][j]);
			id[i][j]=++cnt;
		}
	work1();
	work2();
	work3();
	return 0;
}


