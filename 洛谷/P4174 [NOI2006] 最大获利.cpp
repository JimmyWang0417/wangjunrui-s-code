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
const int N=5e4+5e3+5,M=1e6+5;
const int INF=0x7fffffff;
struct Edge
{
	int next,to,flow,cap;
} edge[M];
int head[N],num_edge=1;
inline void add_edge(int from,int to,int cap,bool flag=true)
{
	edge[++num_edge].next=head[from];
	edge[num_edge].to=to;
	edge[num_edge].flow=0;
	edge[num_edge].cap=cap;
	head[from]=num_edge;
	if(flag)
		add_edge(to,from,0,false);
}
int S,T;
int dis[N];
int cur[N];
bool vis[N];
inline bool bfs()
{
	memcpy(cur,head,sizeof(head));
	memset(dis,0,sizeof(dis));
	memset(vis,0,sizeof(vis));
	queue<int>q;
	dis[S]=1;
	q.push(S);
	while(!q.empty())
	{
		int u=q.front();
		q.pop();
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
	return dis[T];
}
inline int dinic(int u,int flow)
{
	if(u==T)
		return flow;
	vis[u]=true;
	int res=0;
	for(int i=head[u]; i; i=edge[i].next)
	{
		int &v=edge[i].to;
		if(!vis[v]&&dis[v]==dis[u]+1&&edge[i].cap>edge[i].flow)
		{
			int f=dinic(v,min(flow,edge[i].cap-edge[i].flow));
			if(f)
			{
				res+=f;
				flow-=f;
				edge[i].flow+=f;
				edge[i^1].flow-=f;
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
inline ll mincut()
{
	ll res=0;
	while(bfs())
		res+=dinic(S,INF);
	return res;
}
int n,m;
signed main()
{
	read(n,m);
	S=0,T=n+m+1;
	for(int i=1; i<=n; ++i)
	{
		int x;
		read(x);
		add_edge(i,T,x);
	}
	ll sum=0;
	for(int i=1; i<=m; ++i)
	{
		int u,v,w;
		read(u,v,w);
		sum+=w;
		add_edge(S,i+n,w);
		add_edge(i+n,u,INF);
		add_edge(i+n,v,INF);
	}
	printf("%lld\n",sum-mincut());
	return 0;
}


