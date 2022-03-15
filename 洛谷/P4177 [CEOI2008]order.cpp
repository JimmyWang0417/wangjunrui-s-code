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
const int N=2400+5,M=N*N;
int n,m;
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
int cur[N],dis[N];
#define s 0
#define t (n+m+1)
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
//		printf("%d\n",u);
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
//	for(int i=s; i<=t; ++i)
//		printf("%d ",dis[i]);
//	putchar('\n');
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
//	printf("%uMB\n",sizeof(edge)/(1<<20));
	read(n,m);
	int sum=0;
	for(int i=1; i<=n; ++i)
	{
		int x,cnt;
		read(x,cnt);
		add_edge(s,i,x);
		sum+=x;
		while(cnt--)
		{
			int a,b;
			read(a,b);
			add_edge(i,a+n,b);
		}
	}
	for(int i=1; i<=m; ++i)
	{
		int y;
		read(y);
		add_edge(i+n,t,y);
	}
	int maxflow=0;
	while(bfs())
		maxflow+=dinic(s,0x3f3f3f3f);
	printf("%d\n",sum-maxflow);
	return 0;
}


