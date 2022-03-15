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
inline void clear(T*a,int l,int r,int val)
{
	memset(&a[l],val,sizeof(T)*(r-l+1));
}
const int N=1e6+5,M=1e6+5,INF=0x7fffffff;
struct Edge
{
	int next,to,cap,flow,cost;
} edge[M<<1];
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
int cur[N],dis[N];
int n,m,s,t;
bool exist[N];
inline bool spfa()
{
	memset(dis,0x3f3f3f3f,sizeof(dis));
	memset(exist,false,sizeof(exist));
	for(re int i=1; i<=n; ++i)
		cur[i]=head[i];
	std::queue<int>q;
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
	return dis[t]<0x3f3f3f3f;
}
using std::pair;
using std::make_pair;
ll ans=0;
inline int dinic(int u,int flow)
{
	if(u==t)
	{
		ans+=dis[t]*flow;
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
					break;
				}
			}
		}
	}
	return res;
}
signed main()
{
//	freopen("ans.in","r",stdin),freopen("ans.out","w",stdout);
	read(n,m,s,t);
	for(re int i=1; i<=m; ++i)
	{
		int u,v,w,c;
		read(u,v,w,c);
		add_edge(u,v,w,c);
	}
	int res=0;
	while(spfa())
		res+=dinic(s,INF);
	printf("%d %lld\n",res,ans);
	return 0;
}


