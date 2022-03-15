#include <cstdio>
#include <queue>
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
template<typename T>
inline void clear(T*a,int l,int r,int val)
{
	memset(&a[l],val,sizeof(T)*(r-l+1));
}
const int N=64*2+1e4+5,INF=0x3f3f3f3f;
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
int n,m;
int dis[N],cur[N];
bool exist[N];
#define s 1
#define t (2*n)
inline bool spfa()
{
	clear(exist,s,t,false);
	clear(dis,s,t,INF);
	for(re int i=s; i<=t; ++i)
		cur[i]=head[i];
	dis[s]=0;
	std::queue<int>q;
	q.push(s);
	exist[s]=true;
	while(!q.empty())
	{
		int u=q.front();
		q.pop();
		exist[u]=false;
		for(re int i=head[u]; i; i=edge[i].next)
		{
			int &v=edge[i].to;
			if(dis[v]>dis[u]+edge[i].cost&&edge[i].cap>edge[i].flow)
			{
				dis[v]=dis[u]+edge[i].cost;
				if(!exist[v])
				{
					q.push(v);
					exist[v]=true;
				}
			}
		}
	}
	return dis[t]<INF;
}
ll ans=0;
inline int dinic(int u,int flow)
{
	if(u==t)
	{
		ans+=(ll)dis[t]*flow;
		return flow;
	}
	exist[u]=true;
	int res=0;
	for(int &i=cur[u]; i; i=edge[i].next)
	{
		int &v=edge[i].to;
		if(!exist[v]&&dis[v]==dis[u]+edge[i].cost&&edge[i].cap>edge[i].flow)
		{
			int f=dinic(v,std::min(flow,edge[i].cap-edge[i].flow));
			if(f)
			{
				res+=f;
				edge[i].flow+=f;
				edge[i^1].flow-=f;
				flow-=f;
				if(!flow)
				{
					exist[u]=false;
					return res;
				}
			}
		}
	}
	return res;
}
signed main()
{
	int kase=0;
	while(read(n),read(m),n||m)
	{
		for(re int i=1; i<=m; ++i)
		{
			int u,v,w;
			read(u),read(v),read(w);
			++u,++v;
			add_edge(u+n,v,1,w);
		}
		for(re int i=2; i<n; ++i)
			add_edge(i,i+n,1,0);
		add_edge(n,n+n,2,0);
		add_edge(1,1+n,2,0);
		int res=0;
		while(spfa())
			res+=dinic(s,INF);
		printf("Instance #%d: ",++kase);
		if(res<2)
			printf("Not possible\n");
		else
			printf("%lld\n",ans);
		clear(head,s,t,0);
		num_edge=1;
		ans=0;
	}
	return 0;
}


