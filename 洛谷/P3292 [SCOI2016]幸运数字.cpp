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
const int N=2e4+5,M=4e5+5;
struct node
{
	ll d[62];
	node()
	{
		memset(d,0,sizeof(d));
	}
	inline void insert(ll val)
	{
		for(int i=60; i>=0; --i)
		{
			if((val>>i)&1)
			{
				if(!d[i])
				{
					d[i]=val;
					break;
				}
				else
					val^=d[i];
			}
		}
	}
	inline void operator +=(node rhs)
	{
		for(int i=60; i>=0; --i)
			if(rhs.d[i])
				insert(rhs.d[i]);
	}
	inline ll calc()
	{
		ll ans=0;
		for(int i=60; i>=0; --i)
			if(d[i])
				ans=std::max(ans,ans^d[i]);
		return ans;
	}
} f[N][20];
int n,q;
ll a[N];
struct Edge
{
	int next,to;
} edge[M];
int head[N],num_edge;
inline void add_edge(int from,int to)
{
	edge[++num_edge].next=head[from];
	edge[num_edge].to=to;
	head[from]=num_edge;
}
int dep[N];
int fa[N][20];
int Log[N];
inline void dfs(int u,int _fa)
{
	dep[u]=dep[_fa]+1;
	f[u][0].insert(a[u]);
	fa[u][0]=_fa;
	for(int i=0; i<Log[dep[u]]; ++i)
	{
		f[u][i+1]=f[u][i];
		f[u][i+1]+=f[fa[u][i]][i];
		fa[u][i+1]=fa[fa[u][i]][i];
	}
	for(int i=head[u]; i; i=edge[i].next)
	{
		int &v=edge[i].to;
		if(v==_fa)
			continue;
		dfs(v,u);
	}
}
inline int getfa(int u,int k_th)
{
	for(int i=Log[k_th]; i>=0; --i)
		if((k_th>>i)&1)
			u=fa[u][i];
	return u;
}
inline int getlca(int u,int v)
{
	if(dep[u]<dep[v])
		std::swap(u,v);
	for(int i=Log[dep[u]]; i>=0; --i)
		if(dep[fa[u][i]]>=dep[v])
			u=fa[u][i];
	if(u==v)
		return u;
	for(int i=Log[dep[u]]; i>=0; --i)
		if(fa[u][i]!=fa[v][i])
		{
			u=fa[u][i];
			v=fa[v][i];
		}
	return fa[u][0];
}
signed main()
{
	read(n,q);
	Log[0]=-1;
	for(int i=1; i<=n; ++i)
	{
		read(a[i]);
		Log[i]=Log[i>>1]+1;
	}
	for(int i=1; i<n; ++i)
	{
		int u,v;
		read(u,v);
		add_edge(u,v);
		add_edge(v,u);
	}
	dfs(1,0);
	for(int i=1; i<=q; ++i)
	{
		int u,v;
		read(u,v);
		int lca=getlca(u,v);
		node ans;
		int x=Log[dep[u]-dep[lca]];
		if(x<0)
			ans.insert(a[u]);
		else
		{
			ans=f[u][x];
			ans+=f[getfa(u,(dep[u]-dep[lca])-(1<<x))][x];
		}
		x=Log[dep[v]-dep[lca]];
		if(x<0)
			ans.insert(a[v]);
		else
		{
			ans+=f[v][x];
			ans+=f[getfa(v,(dep[v]-dep[lca])-(1<<x))][x];
		}
		ans.insert(a[lca]);
		printf("%lld\n",ans.calc());
	}
	return 0;
}
