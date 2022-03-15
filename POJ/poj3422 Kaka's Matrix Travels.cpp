#include <cstdio>
#include <algorithm>
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
const int N=1e6+5,INF=0x3f3f3f3f;
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
int n,k;
inline int calc(int x,int y)
{
	return (x-1)*n+y;
}
#define s 0
#define t n*n*2+1
int dis[N],cur[N];
bool exist[N];
inline bool spfa()
{
	clear(exist,s,t,false);
	for(re int i=s; i<=t; ++i)
	{
		cur[i]=head[i];
		dis[i]=~0x3f3f3f3f;
	}
	std::queue<int>q;
	q.push(s);
	dis[s]=0;
	while(!q.empty())
	{
		int u=q.front();
//		printf("%d:",u);
		q.pop();
		exist[u]=false;
		for(re int i=head[u]; i; i=edge[i].next)
		{
			int &v=edge[i].to;
//			printf("%d %d ",dis[v],dis[u]+edge[i].cost);
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
//		putchar('\n');
	}
//	putchar('\n');
	return dis[t]>=0;
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
	while(scanf("%d%d",&n,&k)!=EOF)
	{
		for(re int i=1; i<=n; ++i)
			for(re int j=1; j<=n; ++j)
			{
				int val;
				read(val);
				add_edge(calc(i,j),calc(i,j)+n*n,1,val);
				add_edge(calc(i,j),calc(i,j)+n*n,INF,0);
			}
		for(re int i=1; i<=n; ++i)
			for(re int j=1; j<=n; ++j)
			{
				if(i<n)
					add_edge(calc(i,j)+n*n,calc(i+1,j),INF,0);
				if(j<n)
					add_edge(calc(i,j)+n*n,calc(i,j+1),INF,0);
			}
//	printf("%d\n",spfa());
		add_edge(s,1,k,0);
		add_edge(2*n*n,t,k,0);
		while(spfa())
			dinic(s,INF);
		printf("%lld\n",ans);
		clear(head,s,t,0);
		num_edge=1;
		ans=0;
	}
	return 0;
}


