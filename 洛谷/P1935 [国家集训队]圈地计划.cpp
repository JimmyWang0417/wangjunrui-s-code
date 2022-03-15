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
const int N=1e5+5,INF=0x7fffffff;

const int dx[]= {1,-1,0,0};
const int dy[]= {0,0,1,-1};

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
int dis[N],cur[N];
int S,T;
inline bool bfs()
{
	memset(dis,0,sizeof(dis));
	memcpy(cur,head,sizeof(head));
	queue<int>q;
	q.push(S);
	dis[S]=1;
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
	int res=0;
	for(int i=head[u]; i; i=edge[i].next)
	{
		int &v=edge[i].to;
		if(dis[v]==dis[u]+1&&edge[i].cap>edge[i].flow)
		{
			int f=dinic(v,min(flow,edge[i].cap-edge[i].flow));
			if(f)
			{
				res+=f;
				flow-=f;
				edge[i].flow+=f;
				edge[i^1].flow-=f;
			}
		}
	}
	return res;
}
inline int mincut()
{
	int res=0;
	while(bfs())
		res+=dinic(S,INF);
	return res;
}
int n,m;
int A[105][105],B[105][105],C[105][105];
inline int calc(int x,int y)
{
	return (x-1)*m+y;
}
signed main()
{
	int sum=0;
	read(n,m);
	for(int i=1; i<=n; ++i)
		for(int j=1; j<=m; ++j)
			read(A[i][j]);
	for(int i=1; i<=n; ++i)
		for(int j=1; j<=m; ++j)
			read(B[i][j]);
	for(int i=1; i<=n; ++i)
		for(int j=1; j<=m; ++j)
			read(C[i][j]);

	S=0,T=n*m+1;
	for(int i=1; i<=n; ++i)
		for(int j=1; j<=m; ++j)
			if((i+j)&1)
			{
				sum+=A[i][j]+B[i][j];
				add_edge(S,calc(i,j),A[i][j]);
				add_edge(calc(i,j),T,B[i][j]);
				for(int d=0; d<4; ++d)
				{
					int x=i+dx[d],y=j+dy[d];
					if(1<=x&&x<=n&&1<=y&&y<=m)
					{
						sum+=C[i][j]+C[x][y];
						add_edge(calc(i,j),calc(x,y),C[i][j]+C[x][y]);
						add_edge(calc(x,y),calc(i,j),C[i][j]+C[x][y]);
					}
				}
			}
			else
			{
				sum+=A[i][j]+B[i][j];
				add_edge(S,calc(i,j),B[i][j]);
				add_edge(calc(i,j),T,A[i][j]);
			}
	printf("%d\n",sum-mincut());
	return 0;
}


