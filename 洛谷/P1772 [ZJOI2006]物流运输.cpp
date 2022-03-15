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
const int N=105;
struct Edge
{
	int next,to,dis;
} edge[N*N];
int head[N],num_edge;
inline void add_edge(int from,int to,int dis)
{
	edge[++num_edge].next=head[from];
	edge[num_edge].to=to;
	edge[num_edge].dis=dis;
	head[from]=num_edge;
}
int n,m,k,e,d;
int a[N];
int cost[N][N];
int dis[N];
bool vis[N];
inline int dijkstra(int S)
{
	priority_queue<pair<int,int>,vector<pair<int,int> >,greater<pair<int,int> > >q;
	memset(dis,0x3f,sizeof(dis));
	memset(vis,0,sizeof(vis));
	q.push(make_pair(dis[1]=0,1));
	while(!q.empty())
	{
		int u=q.top().second;
		q.pop();
		if(vis[u])
			continue;
		vis[u]=true;
		for(int i=head[u]; i; i=edge[i].next)
		{
			int &v=edge[i].to;
			if(dis[v]>dis[u]+edge[i].dis&&((S>>v)&1))
				q.push(make_pair(dis[v]=dis[u]+edge[i].dis,v));
		}
	}
	return dis[m];
}
ll dp[N];
signed main()
{
	read(n,m,k,e);
	for(int i=1; i<=e; ++i)
	{
		int u,v,w;
		read(u,v,w);
		add_edge(u,v,w);
		add_edge(v,u,w);
	}
	for(int i=1; i<=n; ++i)
		a[i]=((1<<m)-1)<<1;
	read(d);
	for(int i=1; i<=d; ++i)
	{
		int p,x,y;
		read(p,x,y);
		for(int j=x; j<=y; ++j)
			a[j]&=~(1<<p);
	}
	for(int i=1; i<=n; ++i)
	{
		int S=((1<<m)-1)<<1;
		for(int j=i; j<=n; ++j)
		{
			S&=a[j];
			cost[i][j]=dijkstra(S);
		}
	}
	memset(dp,0x3f,sizeof(dp));
	dp[0]=-k;
	for(int i=1; i<=n; ++i)
	{
		for(int j=0; j<i; ++j)
			dp[i]=min(dp[i],dp[j]+(ll)cost[j+1][i]*(i-j)+k);
	}
	printf("%lld\n",dp[n]);
	return 0;
}


