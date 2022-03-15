#include <iostream>
#include <cstdio>
#include <cstring>
#define lowbit(x) ((x)&(-(x)))
#define re register
#define ll long long
#define ull unsigned long long
#define rep(i,a,b) for(re int i=a;i<=b;++i)
#define per(i,a,b) for(re int i=a;i>=b;--i)
template<typename T>
inline void clear(T*a,int l,int r,int val)
{
	memset(&a[l],val,sizeof(T)*(r-l+1));
}
const int N=2e6+5;
struct Edge
{
	int next,to;
} edge[N];
int head[N],num_edge;
inline void add_edge(int from,int to)
{
	edge[++num_edge].next=head[from];
	edge[num_edge].to=to;
	head[from]=num_edge;
}
using std::min;
using std::cin;
int n,m;
int dfn[N],low[N],dfstime;
int belong[N],color;
int st[N],top;
inline void tarjan(int u)
{
	st[++top]=u;
	dfn[u]=low[u]=++dfstime;
	for(re int i=head[u]; i; i=edge[i].next)
	{
		int &v=edge[i].to;
		if(!dfn[v])
		{
			tarjan(v);
			low[u]=min(low[u],low[v]);
		}
		else if(!belong[v])
			low[u]=min(low[u],dfn[v]);
	}
	if(low[u]==dfn[u])
	{
		belong[u]=++color;
		while(st[top]!=u)
			belong[st[top--]]=color;
		--top;
	}
}
inline void work()
{
	memset(dfn,0,sizeof(dfn));
    memset(belong,0,sizeof(belong));
    memset(head,dfstime=color=top=num_edge=0,sizeof(head));
	for(re int i=0; i<m; ++i)
	{
		int u,v;
		char a,b;
		cin>>u>>a>>v>>b;
		u=u<<1|(a=='h');
		v=v<<1|(b=='h');
		add_edge(u,v^1);
		add_edge(v,u^1);
	}
	add_edge(0,1);
	for(re int i=0; i<2*n; ++i)
		if(!dfn[i])
			tarjan(i);
	for(re int i=0; i<n; ++i)
		if(belong[i<<1]==belong[i<<1|1])
		{
			printf("bad luck\n");
			return;
		}
	for(re int i=1; i<n; ++i)
		printf("%d%c ",i,(belong[i<<1]>belong[i<<1|1]?'w':'h'));
	putchar('\n');
}
signed main()
{
	std::ios::sync_with_stdio(false);
	while(cin>>n>>m&&(n||m))
		work();
	return 0;
}


