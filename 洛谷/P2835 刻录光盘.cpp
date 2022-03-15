#include <cstdio>
#include <algorithm>
#define re register
using namespace std;
const int N=205;
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
int dfstime,dfn[N],low[N],belong[N],sta[N],top,color;
inline void Tarjan(int u)
{
	sta[++top]=u;
	dfn[u]=low[u]=++dfstime;
	for(re int i=head[u]; i; i=edge[i].next)
	{
		int &v=edge[i].to;
		if(!dfn[v])
		{
			Tarjan(v);
			low[u]=min(low[u],low[v]);
		}
		else if(!belong[v])
			low[u]=min(low[u],dfn[v]);
	}
	if(low[u]==dfn[u])
	{
		++color;
		while(sta[top]!=u)
			belong[sta[top--]]=color;
		belong[sta[top--]]=color;
	}
}
int n,in[N];
int main()
{
	scanf("%d",&n);
	for(re int i=1; i<=n; ++i)
	{
		int v;
		while(scanf("%d",&v)!=EOF&&v)
			add_edge(i,v);
	}
	for(re int i=1; i<=n; ++i)
		if(!dfn[i])
			Tarjan(i);
	for(re int u=1; u<=n; ++u)
		for(re int e=head[u]; e; e=edge[e].next)
		{
			int &v=edge[e].to;
			if(belong[u]==belong[v])
				continue;
			++in[belong[v]];
		}
	int ans=0;
	for(re int i=1; i<=color; ++i)
		if(!in[i])
			++ans;
	printf("%d\n",ans);
	return 0;
}
