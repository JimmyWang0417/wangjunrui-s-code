#include<cstdio>
#include<iostream>
#define re register
#define ll long long
using namespace std;
template<typename T>
inline void read(T&x)
{
	x=0;
	char s=getchar();
	bool f=false;
	while(!(s>='0'&&s<='9'))
	{
		if(s=='-')
			f=true;
		s=getchar();
	}
	while(s>='0'&&s<='9')
	{
		x=(x<<1)+(x<<3)+s-'0';
		s=getchar();
	}
	if(f)
		x=(~x)+1;
}
const int N=5e4+5,K=505;
struct Edge
{
	int next,to;
} edge[N<<1];
int num_edge,head[N];
inline void add_edge(int from,int to)
{
	edge[++num_edge].next=head[from];
	edge[num_edge].to=to;
	head[from]=num_edge;
}
int n,k,fa[N];
int dp[N][K];
inline void dfs(int u,int f)
{
	dp[u][0]=1;
	for(re int i=head[u]; i; i=edge[i].next)
	{
		int &v=edge[i].to;
		if(v==f)
			continue;
		fa[v]=u;
		dfs(v,u);
		for(re int j=1; j<=k; ++j)
			dp[u][j]+=dp[v][j-1];
	}
}
int main()
{
	read(n);
	read(k);
	for(re int i=1; i<n; ++i)
	{
		static int u,v;
		scanf("%d%d",&u,&v);
		add_edge(u,v);
		add_edge(v,u);
	}
	dfs(1,1);
	ll ans=0;
	for(re int i=1; i<=n; ++i)
	{
		re int cur=i,last=i;
		for(re int d=1; d<=k; ++d)
		{
			cur=fa[cur];
			if(!cur)
				continue;
			dp[i][k]+=dp[cur][k-d]-(k==d?0:dp[last][k-d-1]);
			last=cur;
		}
		ans+=dp[i][k];
	}
	cout<<(ans>>1ll)<<endl;
	return 0;
}
