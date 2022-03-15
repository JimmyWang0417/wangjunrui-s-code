#include <cstdio>
#include <algorithm>
#include <iostream>
#define re register
using namespace std;
const int N=1e5+5;
struct Edge
{
	int next,to;
} edge[N<<1];
int head[N],num_edge;
inline void add_edge(int from,int to)
{
	edge[++num_edge].next=head[from];
	edge[num_edge].to=to;
	head[from]=num_edge;
}
int dfn[N],top[N],fa[N],size[N],son[N],dfstime,dep[N];
inline void dfs1(int u,int fa_)
{
	fa[u]=fa_;
	size[u]=1;
	for(re int i=head[u]; i; i=edge[i].next)
	{
		int &v=edge[i].to;
		if(v==fa_)
			continue;
//		mindis[v]=min(mindis[u],(ll)edge[i].dis);
		dep[v]=dep[u]+1;
		dfs1(v,u);
		size[u]+=size[v];
		if(size[son[u]]<size[v])
			son[u]=v;
	}
}
inline void dfs2(int u,int topf)
{
	top[u]=topf;
	dfn[u]=++dfstime;
	if(!son[u])
		return;
	dfs2(son[u],topf);
	for(re int i=head[u]; i; i=edge[i].next)
	{
		int &v=edge[i].to;
		if(top[v])
			continue;
		dfs2(v,v);
	}
}
inline int LCA(int x,int y)
{
	while(top[x]!=top[y])
	{
		if(dep[top[x]]<dep[top[y]])
			swap(x,y);
		x=fa[top[x]];
	}
	if(dep[x]>dep[y])
		swap(x,y);
	return x;
}
inline bool check(int x,int y)
{
	return x<=y&&(x&1)==(y&1);
}
int n;
int main()
{
	ios::sync_with_stdio(false);
	cin>>n;
	for(re int i=1; i<n; ++i)
	{
		int u,v;
		cin>>u>>v;
		add_edge(u,v);
		add_edge(v,u);
	}
	dfs1(1,0);
	dfs2(1,1);
#define dist(x,y) (dep[x]+dep[y]-dep[LCA(x,y)]*2)
	int q;
	cin>>q;
	while(q--)
	{
		int x,y,a,b,k;
		cin>>a>>b>>x>>y>>k; 
//		printf(" %d %d %d ",dist(x,y),dist(x,a)+1+dist(b,y),dist(x,b)+1+dist(a,y));
		if(check(dist(x,y),k)||check(dist(x,a)+1+dist(b,y),k)||check(dist(x,b)+1+dist(a,y),k))
			printf("YES\n");
		else
			printf("NO\n");

	}
}
