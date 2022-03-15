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
const int N=200*200*2+5,M=1e7+5;
int n,m;
int a[205][205];
int cnthang,hang[205][205];
int cntlie,lie[205][205];
int id[205][205];
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
int cur[N];
int dis[N];
#define s 0
#define t (cnthang+cntlie+1)
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
	for(int i=1; i<=n; ++i)
		for(int j=1; j<=m; ++j)
			read(a[i][j]);
	for(int i=1; i<=n; ++i)
	{
		bool flag=true;
		for(int j=1; j<=m; ++j)
		{
			if(a[i][j]==0)
			{
				if(flag)
				{
					++cnthang;
					flag=false;
				}
				hang[i][j]=cnthang;
			}
			else if(a[i][j]==2)
				flag=true;
		}
	}
	for(int j=1; j<=m; ++j)
	{
		bool flag=true;
		for(int i=1; i<=n; ++i)
		{
			if(a[i][j]==0)
			{
				if(flag)
				{
					++cntlie;
					flag=false;
				}
				lie[i][j]=cntlie;
			}
			else if(a[i][j]==2)
				flag=true;
		}
	}
//	for(int i=1; i<=n; ++i)
//	{
//		for(int j=1; j<=m; ++j)
//			printf("%d ",hang[i][j]);
//		putchar('\n');
//	}
//	for(int i=1; i<=n; ++i)
//	{
//		for(int j=1; j<=m; ++j)
//			printf("%d ",lie[i][j]);
//		putchar('\n');
//	}
	for(int i=1; i<=cnthang; ++i)
		add_edge(s,i,1);
	for(int i=1; i<=cntlie; ++i)
		add_edge(i+cnthang,t,1);
	for(int i=1; i<=n; ++i)
		for(int j=1; j<=m; ++j)
			if(a[i][j]==0)
			{
				add_edge(hang[i][j],lie[i][j]+cnthang,1);
				id[i][j]=num_edge-1;
			}
	int maxflow=0;
	while(bfs())
		maxflow+=dinic(s,0x3f3f3f3f);
	printf("%d\n",maxflow);
	for(int i=1; i<=n; ++i)
		for(int j=1; j<=m; ++j)
			if(id[i][j]&&edge[id[i][j]].flow==edge[id[i][j]].cap)
				printf("%d %d\n",i,j);
	return 0;
}


