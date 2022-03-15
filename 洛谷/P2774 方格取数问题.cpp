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
const int N=10000+5;
const int INF=0x3f3f3f3f;
struct Edge
{
	int next,to;
	int cap,flow;
} edge[N*10];
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
bitset<N>vis;
int dis[N];
int cur[N];
int n,m;
#define s 0
#define t (n*m+1)
#define calc(x,y) ((x-1)*m+y)
inline bool bfs()
{
	memcpy(cur,head,sizeof(head));
	vis.reset();
	memset(dis,0,sizeof(dis));
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
	int res=0;
	vis[u]=true;
	for(int &i=cur[u]; i; i=edge[i].next)
	{
		int &v=edge[i].to;
		if(!vis[v]&&dis[v]==dis[u]+1&&edge[i].cap>edge[i].flow)
		{
			int f=dinic(v,min(flow,edge[i].cap-edge[i].flow));
			if(f)
			{
				res+=f;
				edge[i].flow+=f;
				edge[i^1].flow-=f;
				flow-=f;
			}
			if(!flow)
			{
				vis[u]=false;
				break;
			}
		}
	}
	return res;
}
inline bool check(int x,int y)
{
	return x>=1&&x<=n&&y>=1&&y<=m;
}
signed main()
{
	ll sum=0;
	read(n,m);
	for(int i=1; i<=n; ++i)
		for(int j=1; j<=m; ++j)
		{
			int val;
			read(val);
			sum+=val;
			if((i+j)&1)
			{
				add_edge(s,calc(i,j),val);
				if(check(i,j-1))
					add_edge(calc(i,j),calc(i,j-1),INF);
				if(check(i,j+1))
					add_edge(calc(i,j),calc(i,j+1),INF);
				if(check(i-1,j))
					add_edge(calc(i,j),calc(i-1,j),INF);
				if(check(i+1,j))
					add_edge(calc(i,j),calc(i+1,j),INF);
			}
			else
				add_edge(calc(i,j),t,val);
		}
	while(bfs())
		sum-=dinic(s,INF);
	printf("%lld\n",sum);
	return 0;
}


