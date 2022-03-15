#include <bitset>
#include <cstring>
#include <cstdio>
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
template<typename T>
inline void clear(T*a,int l,int r,int val)
{
	memset(&a[l],val,sizeof(T)*(r-l+1));
}
const int N=505;
int n;
struct Edge
{
	int next,to;
} edge[N*N];
int head[N],num_edge;
inline void add_edge(int from,int to)
{
	edge[++num_edge].next=head[from];
	edge[num_edge].to=to;
	head[from]=num_edge;
}
std::bitset<N>vis;
int belong[N];
int dep[N];
inline void dfs(int u,int fa)
{
	dep[u]=dep[fa]+1;
	for(re int i=head[u]; i; i=edge[i].next)
	{
		int &v=edge[i].to;
		if(dep[v])
			continue;
		dfs(v,u);
	}
}
inline bool find(int u)
{
	for(re int i=head[u]; i; i=edge[i].next)
	{
		int &v=edge[i].to;
		if(vis[v])
			continue;
		vis[v]=true;
		if(!belong[v]||find(belong[v]))
		{
			belong[v]=u;
			return true;
		}
	}
	return false;
}
inline void work()
{
	for(re int i=1; i<=n; ++i)
	{
		int u,v,m;
		read(u),read(m);
		++u;
		for(re int j=1; j<=m; ++j)
		{
			read(v);
			++v;
			add_edge(u,v);
		}
	}
	for(re int i=1; i<=n; ++i)
	{
		if(!dep[i])
			dfs(i,0);
	}
	int ans=0;
	for(re int i=1; i<=n; ++i)
	{
		vis.reset();
		if(dep[i]&1&&find(i))
			++ans;
	}
	printf("%d\n",n-ans);
	memset(head,num_edge=0,sizeof(head));
	memset(belong,0,sizeof(belong));
	memset(dep,0,sizeof(dep));
}
signed main()
{
	while(scanf("%d",&n)!=EOF)
		work();
	return 0;
}


