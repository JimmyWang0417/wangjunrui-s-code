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
const int N=1005,INF=0x3f3f3f3f;
int n,m;
int a[N];
struct Edge
{
	int next,to,flow,cap;
} edge[N*16];
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
#define t (2*n+1)
int dis[N];
int cur[N];
inline bool bfs()
{
	for(int i=s; i<=t; ++i)
		cur[i]=head[i];
	memset(dis,0,sizeof(dis));
	dis[s]=1;
	queue<int>q;
	q.push(s);
	while(!q.empty())
	{
		int u=q.front();
		if(u==t)
			return true;
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
			int f=dinic(v,min(edge[i].cap-edge[i].flow,flow));
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
	freopen("permutation.in","r",stdin),freopen("permutation.out","w",stdout);
	read(n,m);
	for(int i=1; i<=n; ++i)
		read(a[i]);
	int sum=0;
	for(int i=1; i<=n; ++i)
	{
		if(a[i]>=0)
		{
			add_edge(s,i,a[i]);
			add_edge(i,i+n,0);
			add_edge(i+n,t,a[i]);
			sum+=a[i];
		}
		else
		{
			add_edge(s,i,0);
			add_edge(i,i+n,-a[i]);
			add_edge(i+n,t,0);
		}
	}
	for(int i=1; i<=m; ++i)
	{
		int x,y;
		read(x,y);
		add_edge(x,y,INF);
		add_edge(x+n,y+n,INF);
	}
	while(bfs())
		sum-=dinic(s,INF);
	printf("%d\n",sum);
	return 0;
}


