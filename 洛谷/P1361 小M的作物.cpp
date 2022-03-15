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
const int N=3e3+5,M=2e6+5;
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
	printf("nmsl\n");
	return dis[T];
}
inline int dinic(int u,int flow)
{
	if(u==T)
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
inline int mincut()
{
	int res=0;
	while(bfs())
		res+=dinic(S,INF);
	return res;
}
int n,m,a[N],b[N];
signed main()
{
	int sum=0;
	read(n);
	for(int i=1; i<=n; ++i)
		read(a[i]);
	for(int i=1; i<=n; ++i)
		read(b[i]);
	read(m);
	S=0,T=n+2*m+1;
	for(int i=1; i<=n; ++i)
	{
		add_edge(S,i,a[i]);
		add_edge(i,T,b[i]);
		sum+=a[i]+b[i];
	}
	for(int i=1; i<=m; ++i)
	{
		int k,c1,c2;
		read(k,c1,c2);
		sum+=c1+c2;
		add_edge(S,i+n,c1);
		add_edge(i+n+m,T,c2);
		while(k--)
		{
			int x;
			read(x);
			add_edge(i+n,x,INF);
			add_edge(x,i+n+m,INF);
		}
	}
	printf("%d\n",sum-mincut());
	return 0;
}


