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
const int N=1e6+5;
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
int n;
int son[N],dep[N];
inline void dfs1(int u,int _fa)
{
	for(int i=head[u]; i; i=edge[i].next)
	{
		int &v=edge[i].to;
		if(v==_fa)
			continue;
		dfs1(v,u);
		if(dep[v]>dep[son[u]])
			son[u]=v;
	}
	dep[u]=dep[son[u]]+1;
}
int wdnmd[N],*now=wdnmd,*dp[N];
int ans[N];
inline void dfs2(int u,int _fa)
{
	dp[u][0]=1;
	if(!son[u])
		return;
	dp[son[u]]=dp[u]+1;
	dfs2(son[u],u);
	if(dp[u][ans[son[u]]+1]>dp[u][ans[u]])
		ans[u]=ans[son[u]]+1;
	for(int i=head[u]; i; i=edge[i].next)
	{
		int &v=edge[i].to;
		if(v==_fa||v==son[u])
			continue;
		dp[v]=now,now+=dep[v];
		dfs2(v,u);
		for(int j=0; j<dep[v]; ++j)
		{
			dp[u][j+1]+=dp[v][j];
			if(dp[u][ans[u]]<dp[u][j+1]||(dp[u][ans[u]]==dp[u][j+1]&&j+1<ans[u]))
				ans[u]=j+1;
		}
	}
}
signed main()
{
	read(n);
	for(int i=1; i<n; ++i)
	{
		int u,v;
		read(u,v);
		add_edge(u,v);
		add_edge(v,u);
	}
	dfs1(1,0);
	dp[1]=now,now+=dep[1];
	dfs2(1,0);
	for(int i=1; i<=n; ++i)
		printf("%d\n",ans[i]);
	return 0;
}


