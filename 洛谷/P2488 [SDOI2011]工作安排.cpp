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
const int N=505,INF=0x3f3f3f3f;
struct Edge
{
	int next,to,cap,flow,cost;
} edge[N*N<<2];
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
int m,n;
int cur[N],dis[N];
bool exist[N];
#define s 0
#define t (n+m+1)
inline bool spfa()
{
	clear(dis,s,t,INF);
	clear(exist,s,t,0);
	for(re int i=s; i<=t; ++i)
		cur[i]=head[i];
	std::queue<int>q;
	q.push(s);
	exist[s]=true;
	dis[s]=0;
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
					exist[v]=true;
					q.push(v);
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
		ans+=(ll)flow*dis[t];
		return flow;
	}
	int res=0;
	exist[u]=true;
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
int a[N];
signed main()
{
	read(m,n);
	for(re int i=1; i<=n; ++i)
	{
		int val;
		read(val);
		add_edge(s,i,val,0);
	}
	for(re int i=1; i<=m; ++i)
		for(re int j=1; j<=n; ++j)
		{
			int opt;
			read(opt);
			if(opt==1)
				add_edge(j,i+n,INF,0);
		}
	for(re int i=1; i<=m; ++i)
	{
		int cnt,val;
		read(cnt);
		a[0]=0;
		for(re int j=1; j<=cnt; ++j)
			read(a[j]);
		for(re int j=1; j<=cnt; ++j)
		{
			read(val);
			add_edge(i+n,t,a[j]-a[j-1],val);
		}
		read(val);
		add_edge(i+n,t,INF,val);
	}
	while(spfa())
		dinic(s,INF);
	printf("%lld\n",ans);
	return 0;
}


