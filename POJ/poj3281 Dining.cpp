#include <cstdio>
#include <queue>
#include <iostream> 
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
const int N=105;
struct Edge
{
	int next,to,cap,flow;
} edge[N*N<<1];
int head[N<<2],num_edge=1;
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
int n,f,d;
#define s 0
#define t (f+2*n+d+1)
int dis[N<<2],cur[N<<2];
inline bool bfs()
{
	std::queue<int>q;
	q.push(s);
	memset(dis,0,sizeof(dis));
	dis[s]=1;
	for(re int i=s; i<=t; ++i)
		cur[i]=head[i];
	while(!q.empty())
	{
		int u=q.front();
		if(u==t)
			return true;
		q.pop();
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
			}
			if(!flow)
				return res;
		}
	}
	return res;
}
signed main()
{
	read(n),read(f),read(d);
	for(re int i=1; i<=f; ++i)
		add_edge(s,i,1);
	for(re int i=1; i<=d; ++i)
		add_edge(f+2*n+i,t,1);
	for(re int i=1; i<=n; ++i)
	{
		add_edge(f+i,f+n+i,1);
		int cnt1,cnt2,v;
		read(cnt1),read(cnt2);
		for(re int j=1; j<=cnt1; ++j)
		{
			read(v);
			add_edge(v,f+i,1);
		}
		for(re int j=1; j<=cnt2; ++j)
		{
			read(v);
			add_edge(f+n+i,f+2*n+v,1);
		}
	}
	int ans=0;
	while(bfs())
		ans+=dinic(s,0x7fffffff);
	printf("%d\n",ans);
	return 0;
}


