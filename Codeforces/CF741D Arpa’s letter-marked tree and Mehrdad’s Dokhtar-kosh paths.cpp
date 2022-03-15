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
inline void clear(T*a,int l,int r,int val)
{
	memset(&a[l],val,sizeof(T)*(r-l+1));
}
const int N=5e5+5;
struct Edge
{
	int next,to,dis;
} edge[N];
int head[N],num_edge;
inline void add_edge(int from,int to,int dis)
{
	edge[++num_edge].next=head[from];
	edge[num_edge].to=to;
	edge[num_edge].dis=dis;
	head[from]=num_edge;
}
int sze[N],son[N];
int dfn[N],rk[N],dfstime;
int dis[N],dep[N];
inline void dfs1(int u)
{
	rk[dfn[u]=++dfstime]=u;
	sze[u]=1;
	for(re int i=head[u]; i; i=edge[i].next)
	{
		int &v=edge[i].to;
		dis[v]=dis[u]^edge[i].dis;
		dep[v]=dep[u]+1;
		dfs1(v);
		sze[u]+=sze[v];
		if(sze[v]>sze[son[u]])
			son[u]=v;
	}
}
int ans[N];
using std::max;
int vis[(1<<22)+5];
inline void dfs2(int u,bool opt)
{
	for(re int i=head[u]; i; i=edge[i].next)
	{
		int &v=edge[i].to;
		if(v==son[u])
			continue;
		dfs2(v,false);
		ans[u]=max(ans[u],ans[v]);
	}
	if(son[u])
	{
		dfs2(son[u],true);
		ans[u]=max(ans[u],ans[son[u]]);
	}
	if(vis[dis[u]])
		ans[u]=max(ans[u],vis[dis[u]]-dep[u]);
	for(re int i=0; i<22; ++i)
		if(vis[dis[u]^(1<<i)])
			ans[u]=max(ans[u],vis[dis[u]^(1<<i)]-dep[u]);
	vis[dis[u]]=max(vis[dis[u]],dep[u]);
	for(re int i=head[u]; i; i=edge[i].next)
	{
		int &x=edge[i].to;
		if(x==son[u])
			continue;
		for(re int j=0; j<sze[x]; ++j)
		{
			int &v=rk[dfn[x]+j];
			if(vis[dis[v]])
				ans[u]=max(ans[u],vis[dis[v]]+dep[v]-dep[u]*2);
			for(re int k=0; k<22; ++k)
				if(vis[dis[v]^(1<<k)])
					ans[u]=max(ans[u],vis[dis[v]^(1<<k)]+dep[v]-dep[u]*2);
		}
		for(re int j=0; j<sze[x]; ++j)
		{
			int &v=rk[dfn[x]+j];
			vis[dis[v]]=max(vis[dis[v]],dep[v]);
		}
	}
	if(!opt)
		for(re int i=0; i<sze[u]; ++i)
			vis[dis[rk[i+dfn[u]]]]=0;
}
using std::cin;
signed main()
{
	int n;
	std::ios::sync_with_stdio(false);
	cin>>n;
	for(re int i=2; i<=n; ++i)
	{
		int fa;
		char c;
		cin>>fa>>c;
		add_edge(fa,i,1<<(c-'a'));
	}
	dfs1(1);
	dfs2(1,false);
	for(re int i=1; i<=n; ++i)
		printf("%d ",ans[i]);
	putchar('\n');
	return 0;
}


