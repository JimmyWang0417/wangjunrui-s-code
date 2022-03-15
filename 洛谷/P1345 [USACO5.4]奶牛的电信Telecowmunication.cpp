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
const int N=1e5+5;
const int INF=0x3f3f3f3f;
struct Edge
{
	int next,to;
	int flow,cap;
} edge[N];
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
int cur[N];
bitset<N>vis;
int dis[N];
int n,m,s,t;
inline bool bfs()
{
	memcpy(cur,head,sizeof(head));
	memset(dis,0,sizeof(dis));
	vis.reset();
	queue<int>q;
	q.push(s);
	dis[s]=1;
	while(!q.empty())
	{
		int u=q.front();
		q.pop();
		if(u==t)
			return true;
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
	return false;
}
inline int dinic(int u,int flow)
{
	if(u==t||!flow)
		return flow;
	vis[u]=true;
	int res=0;
	for(int i=head[u]; i; i=edge[i].next)
	{
		int &v=edge[i].to;
		if(dis[v]==dis[u]+1&&edge[i].cap>edge[i].flow&&!vis[v])
		{
			int f=dinic(v,min(flow,edge[i].cap-edge[i].flow));
			if(f)
			{
				res+=f;
				edge[i].flow+=f;
				edge[i^1].flow-=f;
				flow-=f;
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
signed main()
{
	read(n,m,s,t);
//	printf("%d %d\n",s,t);
	for(int i=1; i<=n; ++i)
	{
		if(i!=s&&i!=t)
			add_edge(i,i+n,1);
		else
			add_edge(i,i+n,INF);
	}
	for(int i=1; i<=m; ++i)
	{
		int u,v;
		read(u,v);
		add_edge(u+n,v,INF);
		add_edge(v+n,u,INF);
	}
	int ans=0;
	while(bfs())
		ans+=dinic(s,INF);
	printf("%d\n",ans);
	return 0;
}


