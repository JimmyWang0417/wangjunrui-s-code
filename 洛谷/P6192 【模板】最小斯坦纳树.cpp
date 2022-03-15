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
const int N=105,M=1005;
int n,m,k;
struct Edge
{
	int next,to,dis;
} edge[M];
int head[N],num_edge;
inline void add_edge(int from,int to,int dis)
{
	edge[++num_edge].next=head[from];
	edge[num_edge].to=to;
	edge[num_edge].dis=dis;
	head[from]=num_edge;
}
int dp[(1<<10)+5][N];
bitset<N>vis;
inline void dijkstra(int *dist)
{
	priority_queue<pair<int,int>,vector<pair<int,int> >,greater<pair<int,int> > >q;
	for(int i=1; i<=n; ++i)
		if(dist[i]<0x3f3f3f3f)
			q.push(make_pair(dist[i],i));
	vis.reset();
	while(!q.empty())
	{
		int u=q.top().second;
		q.pop();
		if(vis[u])
			continue;
		vis[u]=true;
//		printf("%d %d\n",u,dist[u]);
		for(int i=head[u]; i; i=edge[i].next)
		{
			int &v=edge[i].to;
//			printf("%d ",v);
			if(dist[v]>dist[u]+edge[i].dis)
				q.push(make_pair(dist[v]=dist[u]+edge[i].dis,v));
		}
//		putchar('\n');
	}
//	putchar('\n');
}
signed main()
{
	read(n,m,k);
	for(int i=1; i<=m; ++i)
	{
		int u,v,w;
		read(u,v,w);
		add_edge(u,v,w);
		add_edge(v,u,w);
	}
	memset(dp,0x3f,sizeof(dp));
	for(int i=0; i<k; ++i)
	{
		int pos;
		read(pos);
		dp[1<<i][pos]=0;
	}
	for(int S=1; S<(1<<k); ++S)
	{
		for(int i=1; i<=n; ++i)
		{
			for(int subs=S&(S-1); subs; subs=S&(subs-1))
				dp[S][i]=min(dp[S][i],dp[subs][i]+dp[S^subs][i]);
		}
		dijkstra(dp[S]);
//		for(int i=1; i<=n; ++i)
//			printf("%d ",dp[S][i]);
//		putchar('\n');
	}
	int ans=0x3f3f3f3f;
	for(int i=1; i<=n; ++i)
		ans=min(ans,dp[(1<<k)-1][i]);
	printf("%d\n",ans);
	return 0;
}


