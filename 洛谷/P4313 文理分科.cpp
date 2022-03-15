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
const int dx[5]= {1,-1,0,0};
const int dy[5]= {0,0,1,-1};
const int INF=0x3f3f3f3f;
struct Edge
{
	int next,to,flow,cap;
} edge[N*10];
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
int n,m;
#define s 0
#define t (n*m*3+1)
inline int calc(int x,int y)
{
	return (x-1)*m+y;
}
int dis[N];
int cur[N];
inline bool bfs()
{
	memset(dis,0,sizeof(dis));
	memcpy(cur,head,sizeof(head));
	queue<int>q;
	dis[s]=1;
	q.push(s);
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
	return dis[t];
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
				edge[i^1].flow-=f;
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
	read(n,m);
	int sum=0;
	for(int i=1; i<=n; ++i)
		for(int j=1; j<=m; ++j)
		{
			int val;
			read(val);
			sum+=val;
			add_edge(s,calc(i,j),val);
		}
	for(int i=1; i<=n; ++i)
		for(int j=1; j<=m; ++j)
		{
			int val;
			read(val);
			sum+=val;
			add_edge(calc(i,j),t,val);
		}
	for(int i=1; i<=n; ++i)
		for(int j=1; j<=m; ++j)
		{
			int val;
			read(val);
			sum+=val;
			add_edge(s,calc(i,j)+n*m,val);
			for(int d=0; d<5; ++d)
			{
				int x=i+dx[d],y=j+dy[d];
				if(x<1||x>n||y<1||y>m)
					continue;
				add_edge(calc(i,j)+n*m,calc(x,y),INF);
			}
		}
	for(int i=1; i<=n; ++i)
		for(int j=1; j<=m; ++j)
		{
			int val;
			read(val);
			sum+=val;
			add_edge(calc(i,j)+2*n*m,t,val);
			for(int d=0; d<5; ++d)
			{
				int x=i+dx[d],y=j+dy[d];
				if(x<1||x>n||y<1||y>m)
					continue;
				add_edge(calc(x,y),calc(i,j)+2*n*m,INF);
			}
		}
	int maxflow=0;
	while(bfs())
		maxflow+=dinic(s,INF);
	printf("%d\n",sum-maxflow);
	return 0;
}


