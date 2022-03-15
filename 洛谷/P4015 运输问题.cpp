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
const int N=1e5+5,INF=0x3f3f3f3f;
int m,n;
struct Edge
{
	int next,to,flow,cap,cost;
} edge[N];
int head[N],num_edge=1;
inline void add_edge(int from,int to,int cap,int cost,bool flag=true)
{
	edge[++num_edge].next=head[from];
	edge[num_edge].to=to;
	edge[num_edge].cap=cap;
	edge[num_edge].cost=cost;
	head[from]=num_edge;
	if(flag)
		add_edge(to,from,0,-cost,false);
}
int dis[N],cur[N];
bitset<N>exist;
#define s 0
#define t (n+m+1)
inline bool spfamin()
{
	memset(dis,INF,sizeof(dis));
	memcpy(cur,head,sizeof(head));
	exist.reset();
	queue<int>q;
	dis[s]=0;
	q.push(s);
	while(!q.empty())
	{
		int u=q.front();
		q.pop();
		for(int i=head[u]; i; i=edge[i].next)
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
		exist[u]=false;
	}
	return dis[t]<INF;
}
inline bool spfamax()
{
	memset(dis,~INF,sizeof(dis));
	memcpy(cur,head,sizeof(head));
	exist.reset();
	queue<int>q;
	dis[s]=0;
	q.push(s);
	while(!q.empty())
	{
		int u=q.front();
		q.pop();
		for(int i=head[u]; i; i=edge[i].next)
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
		exist[u]=false;
	}
	return dis[t]>~INF;
}
inline int dinic(int u,int flow)
{
	if(u==t)
		return flow;
	if(!flow)
		return 0;
	exist[u]=true;
	int res=0;
	for(int i=cur[u]; i; i=edge[i].next)
	{
		int &v=edge[i].to;
		if(!exist[v]&&edge[i].cap>edge[i].flow&&dis[v]==dis[u]+edge[i].cost)
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
signed main()
{
	read(m,n);
	for(int i=1; i<=m; ++i)
	{
		int val;
		read(val);
		add_edge(s,i,val,0);
	}
	for(int i=1; i<=n; ++i)
	{
		int val;
		read(val);
		add_edge(i+m,t,val,0);
	}
	for(int i=1; i<=m; ++i)
		for(int j=1; j<=n; ++j)
		{
			int val;
			read(val);
			add_edge(i,j+m,INF,val);
		}
	ll ans=0;
	while(spfamin())
		ans+=(ll)dinic(s,INF)*dis[t];
	printf("%lld\n",ans);
	ans=0;
	for(int i=1; i<=num_edge; ++i)
		edge[i].flow=0;
	while(spfamax())
		ans+=(ll)dinic(s,INF)*dis[t];
	printf("%lld\n",ans);
	return 0;
}


