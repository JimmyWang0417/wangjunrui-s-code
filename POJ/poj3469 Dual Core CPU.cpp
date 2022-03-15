#include <cstdio>
#include <iostream>
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
const int N=2e4+5,M=2e5+5;
int n,m;
struct Edge
{
	int next,to,cap,flow;
} edge[(N+M)<<2];
int head[N],num_edge=1;
inline void add_edge(int from,int to,int cap,bool flag=true)
{
	edge[++num_edge].next=head[from];
	edge[num_edge].to=to;
	edge[num_edge].cap=cap;
	edge[num_edge].flow=0;
	head[from]=num_edge;
	if(flag)
		add_edge(to,from,0,false);
}
#define s 0
#define t (n+1)
int dis[N],cur[N];
inline bool bfs()
{
	memset(dis,0,sizeof(dis));
	for(re int i=s; i<=t; ++i)
		cur[i]=head[i];
	std::queue<int>q;
	q.push(s);
	dis[s]=1;
	while(!q.empty())
	{
		int u=q.front();
		q.pop();
		if(u==t)
			return true;
		for(re int i=head[u]; i; i=edge[i].next)
		{
			int &v=edge[i].to;
			if(!dis[v]&&edge[i].cap>edge[i].flow)
			{
				dis[v]=dis[u]+1;
				q.push(v);
			}
		}
	}
	return false;
}
inline int dinic(int u,int flow)
{
	if(u==t)
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
				edge[i^1].flow+=f;
				flow-=f;
				if(!flow)
					break;
			}
		}
	}
	return res;
}
signed main()
{
	read(n),read(m);
	for(re int i=1; i<=n; ++i)
	{
		int x,y;
		read(x),read(y);
		add_edge(s,i,x);
		add_edge(i,t,y);
	}
	for(re int i=1; i<=m; ++i)
	{
		int u,v,w;
		read(u),read(v),read(w);
		add_edge(u,v,w);
		add_edge(v,u,w);
	}
	int ans=0;
	while(bfs())
		ans+=dinic(s,0x7fffffff);
	printf("%d\n",ans);
	return 0;
}


