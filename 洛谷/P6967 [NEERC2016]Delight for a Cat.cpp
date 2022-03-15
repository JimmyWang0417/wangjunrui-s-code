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
const int N=1e5+5;
const int INF=0x7fffffff;
struct Edge
{
	int next,to,flow,cap,cost;
} edge[N];
int head[N],num_edge=1;
inline void add_edge(int from,int to,int cap,int cost,bool flag=true)
{
	edge[++num_edge].next=head[from];
	edge[num_edge].to=to;
	edge[num_edge].flow=0;
	edge[num_edge].cap=cap;
	edge[num_edge].cost=cost;
	head[from]=num_edge;
	if(flag)
		add_edge(to,from,0,-cost,false);
}
int n,k,ma,mb,a[N],b[N];
int S,T;
ll dis[N];
int cur[N];
bool exist[N];
inline bool spfa()
{
	memset(exist,0,sizeof(exist));
	memcpy(cur,head,sizeof(head));
	memset(dis,~0x3f,sizeof(dis));
	queue<int>q;
	q.push(S);
	dis[S]=0;
	exist[S]=true;
	while(!q.empty())
	{
		int u=q.front();
		q.pop();
		exist[u]=false;
		for(re int i=head[u]; i; i=edge[i].next)
		{
			int &v=edge[i].to;
			if(edge[i].cap>edge[i].flow&&dis[v]<dis[u]+edge[i].cost)
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
//	for(int i=0; i<=n+2; ++i)
//		printf("%lld ",dis[i]);
//	putchar('\n');
	return dis[T]>-5e17;
}
inline int dinic(int u,int flow)
{
	if(u==T||!flow)
		return flow;
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
					break;
				}
			}
		}
	}
	return res;
}
inline ll maxcost_maxflow()
{
	ll res=0;
	while(spfa())
		res+=dis[T]*dinic(S,INF);
	return res;
}
int id[N];
signed main()
{
	read(n,k,ma,mb);
	ll sum=0;
	for(int i=1; i<=n; ++i)
	{
		read(a[i]);
		sum+=a[i];
	}
	S=0,T=n+2;
	int s0=n+1;
	for(int i=1; i<=n; ++i)
		read(b[i]);
	add_edge(S,s0,k-ma,0);
	add_edge(s0,1,k-ma-mb,0);
	for(int i=1; i<n; ++i)
		add_edge(i,i+1,k-ma-mb,0);
	for(int i=1; i<=k; ++i)
	{
		add_edge(s0,i,1,b[i]-a[i]);
		id[i]=num_edge-1;
	}
	for(int i=k+1; i<=n; ++i)
	{
		add_edge(i-k,i,1,b[i]-a[i]);
		id[i]=num_edge-1;
	}
	for(int i=n-k+1; i<=n; ++i)
		add_edge(i,T,INF,0);
	printf("%lld\n",sum+maxcost_maxflow());
	for(int i=1; i<=n; ++i)
		putchar(edge[id[i]].flow==edge[id[i]].cap?'E':'S');
	return 0;
}


