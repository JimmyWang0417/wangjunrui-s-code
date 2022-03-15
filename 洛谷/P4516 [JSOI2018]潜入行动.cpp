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
const int N=1e5+5,K=105;
const int mod=1e9+7;
struct Edge
{
	int next,to;
} edge[N*2];
int head[N],num_edge;
inline void add_edge(int from,int to)
{
	edge[++num_edge].next=head[from];
	edge[num_edge].to=to;
	head[from]=num_edge;
}
int dp[N][K][2][2],g[K][2][2];//第一个是该点是否放置探测器，第二个是该点是否被覆盖
int size[N];
int n,k;
#define times(x,y) ((int)((ll)(x)*(y)%mod))
inline void dfs(int u,int _fa)
{
	size[u]=1;
	dp[u][1][1][0]=dp[u][0][0][0]=1;
	for(int e=head[u]; e; e=edge[e].next)
	{
		int &v=edge[e].to;
		if(v==_fa)
			continue;
		dfs(v,u);
		memset(g,0,sizeof(g));
		for(int i=0; i<=size[u]&&i<=k; ++i)
			for(int j=0; j<=size[v]&&i+j<=k; ++j)
			{
				(g[i+j][0][0]+=times(dp[u][i][0][0],dp[v][j][0][1]))%=mod;
				(g[i+j][0][1]+=(times(dp[u][i][0][0],dp[v][j][1][1])+times(dp[u][i][0][1],dp[v][j][0][1]+dp[v][j][1][1]))%mod)%=mod;

				(g[i+j][1][0]+=times(dp[u][i][1][0],dp[v][j][0][1]+dp[v][j][0][0]))%=mod;
				(g[i+j][1][1]+=(times(dp[u][i][1][0],dp[v][j][1][0]+dp[v][j][1][1])+times(dp[u][i][1][1],(ll)dp[v][j][0][0]+dp[v][j][0][1]+dp[v][j][1][0]+dp[v][j][1][1]))%mod)%=mod;
			}
		size[u]+=size[v];
		memcpy(dp[u],g,sizeof(g));
	}
}
signed main()
{
//	cerr<<(sizeof(dp)+sizeof(g))/(1<<20)<<endl;
	read(n,k);
	for(int i=1; i<n; ++i)
	{
		int u,v;
		read(u,v);
		add_edge(u,v);
		add_edge(v,u);
	}
	dfs(1,0);
	printf("%d\n",(dp[1][k][0][1]+dp[1][k][1][1])%mod);
	return 0;
}


