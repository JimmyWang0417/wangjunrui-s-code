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
ll pool[N*10],*f[N],*g[N],ans;
int maxdep[N],son[N];
inline void dfs1(int u,int _fa)
{
	for(int i=head[u]; i; i=edge[i].next)
	{
		int &v=edge[i].to;
		if(v==_fa)
			continue;
		dfs1(v,u);
		if(maxdep[v]+1>maxdep[u])
		{
			maxdep[u]=maxdep[v]+1;
			son[u]=v;
		}
	}
}
ll *poolfail=pool+N;
inline void getmemory(int u)
{
	f[u]=poolfail,poolfail+=maxdep[u]<<1|1;
	g[u]=poolfail,poolfail+=maxdep[u]<<1|1;
}
inline void dfs2(int u,int _fa)
{
	if(son[u])
	{
		f[son[u]]=f[u]+1;
		g[son[u]]=g[u]-1;
		dfs2(son[u],u);
	}

	ans+=g[u][0];
	f[u][0]=1;
	for(int e=head[u]; e; e=edge[e].next)
	{
		int &v=edge[e].to;
		if(v==_fa||v==son[u])
			continue;
		getmemory(v);
		dfs2(v,u);
		for(int i=0; i<=maxdep[v]; ++i)
		{
			if(i)ans+=g[v][i]*f[u][i-1];
			ans+=f[v][i]*g[u][i+1];
		}
		for(int i=0; i<=maxdep[v]; ++i)
		{
			g[u][i+1]+=f[u][i+1]*f[v][i];
			f[u][i+1]+=f[v][i];
			if(i)
				g[u][i-1]+=g[v][i];
		}
	}
}
int n;
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
//	for(int i=1; i<=n; ++i)
//		printf("%d ",maxdep[i]);
//	putchar('\n');
	getmemory(1);
	dfs2(1,0);
	printf("%lld\n",ans);
	return 0;
}


