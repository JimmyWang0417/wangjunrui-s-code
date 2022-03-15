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
const int N=205,M=5005;
int n,m,s,t;
struct Edge
{
	int next,to,cap,flow;
} edge[M<<1];
int head[N],num_edge=1;
inline void add_edge(int from,int to,int cap)
{
	edge[++num_edge].next=head[from];
	edge[num_edge].to=to;
	edge[num_edge].cap=cap;
	edge[num_edge].flow=0;
	head[from]=num_edge;
}
bool vis[N];
int dis[N],cur[N];
inline bool bfs()
{
	memset(vis,0,sizeof(vis));
	for(re int i=1; i<=n; ++i)
		cur[i]=head[i];
	vis[s]=true;
	std::queue<int>q;
	q.push(s);
	while(!q.empty())
	{
		int u=q.front();
		q.pop();
		for(re int i=head[u]; i; i=edge[i].next)
		{
			int &v=edge[i].to;
			if(!vis[v]&&edge[i].cap>edge[i].flow)
			{
				vis[v]=true;
				dis[v]=dis[u]+1;
				q.push(v);
			}
		}
	}
	return vis[t];
}
inline int dinic(int u,int flow)
{
	if(u==t||!flow)
		return flow;
	int res=0;
	for(int &i=cur[u]; i; i=edge[i].next)
	{
		int &v=edge[i].to;
		if(dis[v]==dis[u]+1&&edge[i].cap>edge[i].flow)
		{
			int f=dinic(v,std::min(flow,edge[i].cap-edge[i].flow));
			if(f)
			{
				res+=f;
				edge[i].flow+=f;
				edge[i^1].flow-=f;
				flow-=f;
				if(!flow)
					return res;
			}
		}
	}
	return res;
}
signed main()
{
	read(n,m,s,t);
	for(re int i=1; i<=m; ++i)
	{
		int u,v,w;
		read(u,v,w);
		add_edge(u,v,w);
		add_edge(v,u,0);
	}
	ll ans=0;
	while(bfs())
		ans+=dinic(s,0x7fffffff);
	printf("%lld\n",ans);
	return 0;
}

