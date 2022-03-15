#include <queue>
#include <cstdio>
#include <vector>
#include <algorithm>
#define re register
#define ll long long
using namespace std;
template<typename T>
inline void read(T&x)
{
	x=0;
	char s=(char)getchar();
	bool flag=false;
	while(!(s>='0'&&s<='9'))
	{
		if(s=='-')
			flag=true;
		s=(char)getchar();
	}
	while(s>='0'&&s<='9')
	{
		x=(x<<1)+(x<<3)+s-'0';
		s=(char)getchar();
	}
	if(flag)
		x=(~x)+1;
	return;
}
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
int size[N],son[N],dep[N],fa[N];
inline void dfs1(int u,int _fa)
{
	size[u]=1;
	fa[u]=_fa;
	dep[u]=dep[_fa]+1;
	for(re int i=head[u]; i; i=edge[i].next)
	{
		int &v=edge[i].to;
		if(v==_fa)
			continue;
		dfs1(v,u);
		size[u]+=size[v];
		if(size[v]>size[son[u]])
			son[u]=v;
	}
}
int top[N];
inline void dfs2(int u,int topf)
{
	top[u]=topf;
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
	while(top[x]^top[y])
	{
		if(dep[top[x]]<dep[top[y]])
			swap(x,y);
		x=fa[top[x]];
	}
	if(dep[x]>dep[y])
		swap(x,y);
	return x;
}
int n,m;
int tot;
struct Tree
{
	int l,r;
	int size,val;
} tree[N*40];
#define lc(x) tree[x].l
#define rc(x) tree[x].r
int root[N],treesize;
inline void pushup(int rt)
{
	if(tree[lc(rt)].size>=tree[rc(rt)].size)
	{
		tree[rt].size=tree[lc(rt)].size;
		tree[rt].val=tree[lc(rt)].val;
	}
	else
	{
		tree[rt].size=tree[rc(rt)].size;
		tree[rt].val=tree[rc(rt)].val;
	}
}
inline int merge(int x,int y,int l=1,int r=1e5)
{
	if(!x||!y)
		return x|y;
	if(l==r)
	{
		tree[x].size+=tree[y].size;
		tree[x].val=l;
		return x;
	}
	int mid=(l+r)>>1;
	lc(x)=merge(lc(x),lc(y),l,mid);
	rc(x)=merge(rc(x),rc(y),mid+1,r);
	pushup(x);
	return x;
}
inline void update(int &rt,int l,int r,int pos,int val)
{
	if(!rt)
		rt=++treesize;
	if(l==r)
	{
		tree[rt].size+=val;
		tree[rt].val=l;
		return;
	}
	int mid=(l+r)>>1;
	if(pos<=mid)
		update(lc(rt),l,mid,pos,val);
	else
		update(rc(rt),mid+1,r,pos,val);
	pushup(rt);
}
int dfn[N],dfstime,ans[N];
struct node
{
	int u,d,val;
	node(int _u=0,int _d=0,int _val=0):u(_u),d(_d),val(_val) {}
	inline bool operator > (const node&rhs)const
	{
		return dfn[u]>dfn[rhs.u];
	}
} q[N<<2];
inline void dfs3(int u)
{
	for(re int i=head[u]; i; i=edge[i].next)
	{
		int &v=edge[i].to;
		if(v==fa[u])
			continue;
		dfs3(v);
	}
	dfn[u]=++dfstime;
}
inline void dfs(int u,int _fa)
{
	for(re int i=head[u]; i; i=edge[i].next)
	{
		int &v=edge[i].to;
		if(v==_fa)
			continue;
		dfs(v,u);
		root[u]=merge(root[u],root[v]);
	}
	while(q[tot].u==u)
	{
		update(root[u],1,100000,q[tot].d,q[tot].val);
		--tot;
	}
	ans[u]=tree[root[u]].size?tree[root[u]].val:0;
}
int main()
{
	read(n),read(m);
	for(re int i=1; i<n; ++i)
	{
		int u,v;
		read(u),read(v);
		add_edge(u,v);
		add_edge(v,u);
	}
	dfs1(1,0);
	dfs2(1,1);
	dfs3(1);
	for(re int i=1; i<=m; ++i)
	{
		int x,y,d;
		read(x),read(y),read(d);
		int lca=LCA(x,y);
		q[++tot]=node(x,d,1);
		q[++tot]=node(y,d,1);
		q[++tot]=node(lca,d,-1);
		if(fa[lca])
			q[++tot]=node(fa[lca],d,-1);
	}
//	for(re int i=1; i<=n; ++i)
//		printf(" %d",dfn[i]);
//	putchar('\n');
	sort(q+1,q+1+tot,greater<node>());
	dfs(1,0);
	for(re int i=1; i<=n; ++i)
		printf("%d\n",ans[i]);
	return 0;
}
