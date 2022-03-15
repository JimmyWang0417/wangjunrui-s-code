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
const int N=505,INF=0x7fffffff;
struct Edge
{
	int next,to,cap,flow;
} edge[N*N<<3];
int head[N],num_edge=1;
inline void add_edge(int from,int to,int cap=INF,bool flag=true)
{
	edge[++num_edge].next=head[from];
	edge[num_edge].to=to;
	edge[num_edge].cap=cap;
	edge[num_edge].flow=0;
	head[from]=num_edge;
	if(flag)
		add_edge(to,from,0,false);
}
int n;
#define s 0
#define t (n+1)
int dis[N],cur[N];
inline bool bfs()
{
	memset(dis,0,sizeof(dis));
	for(re int i=s; i<=t; ++i)
		cur[i]=head[i];
	std::queue<int>q;
	dis[s]=1;
	q.push(s);
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
inline int dinic(int u,int flow=INF)
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
int b[N][N],c[N];
signed main()
{
	read(n);
	int sum=0;
	for(re int i=1; i<=n; ++i)
		for(re int j=1; j<=n; ++j)
		{
			read(b[i][j]);
			sum+=b[i][j];
		}
	for(re int i=1; i<=n; ++i)
		read(c[i]);
	for(re int i=1; i<=n; ++i)
	{
		add_edge(i,t,2*c[i]);
		add_edge(s,i,2*b[i][i]);
	}
	for(re int i=1; i<=n; ++i)
		for(re int j=i+1; j<=n; ++j)
		{
			add_edge(s,i,b[i][j]+b[j][i]);
			add_edge(s,j,b[i][j]+b[j][i]);
			add_edge(i,j,b[i][j]+b[j][i]);
			add_edge(j,i,b[i][j]+b[j][i]);
		}
	int ans=0;
	while(bfs())
		ans+=dinic(s);
	printf("%d\n",sum-ans/2);
	return 0;
}


