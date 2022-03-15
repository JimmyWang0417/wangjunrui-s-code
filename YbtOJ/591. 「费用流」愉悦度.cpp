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
const int N=1e4+5;
const ll INF=1e18;
int n,k,S,E;
struct Edge
{
	int next,to;
	int cost;
	int cap,flow;
} edge[N];
int head[N],num_edge=1;
inline void add_edge(int from,int to,int cap,int cost,bool flag=true)
{
//	printf("%d %d %d %d\n",from,to,cap,cost);
	edge[++num_edge].next=head[from];
	edge[num_edge].to=to;
	edge[num_edge].cap=cap;
	edge[num_edge].flow=0;
	edge[num_edge].cost=cost;
	head[from]=num_edge;
	if(flag)
		add_edge(to,from,0,-cost,false);
}
ll dis[N];
bool exist[N];
int cur[N];
#define s 0
#define ss (n+1)
#define t (n+2)
inline bool spfa()
{
	memset(exist,0,sizeof(exist));
	for(int i=s; i<=t; ++i)
	{
		cur[i]=head[i];
		dis[i]=INF;
	}
	queue<int>q;
	q.push(s);
	dis[s]=0;
	exist[s]=true;
	while(!q.empty())
	{
		int u=q.front();
		q.pop();
		exist[u]=false;
		for(re int i=head[u]; i; i=edge[i].next)
		{
			int &v=edge[i].to;
			if(edge[i].cap>edge[i].flow&&dis[v]>dis[u]+edge[i].cost)
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
	return dis[t]<INF/2;
}
ll ans=0;
inline int dinic(int u,int flow)
{
	if(u==t||!flow)
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
int _s[N],_e[N];

signed main()
{
	freopen("delight.in","r",stdin),freopen("delight.out","w",stdout);
	ll sum=0;
	read(n,k,S,E);
	for(int i=1; i<=n; ++i)
	{
		read(_s[i]);
		sum+=_s[i];
	}
	for(int i=1; i<=n; ++i)
		read(_e[i]);
	add_edge(s,ss,k-S,0);
	add_edge(ss,1,k-S-E,0);
	for(int i=1; i<n; ++i)
		add_edge(i,i+1,k-S-E,0);
	for(int i=1; i<=k; ++i)
		add_edge(ss,i,1,_s[i]-_e[i]);
	for(int i=1; i<=n-k; ++i)
		add_edge(i,i+k,1,_s[i+k]-_e[i+k]);
	for(int i=n-k+1; i<=n; ++i)
		add_edge(i,t,0x3f3f3f3f,0);
	while(spfa())
		ans+=dis[t]*dinic(s,0x3f3f3f3f);
	printf("%lld\n",sum-ans);
	return 0;
}


