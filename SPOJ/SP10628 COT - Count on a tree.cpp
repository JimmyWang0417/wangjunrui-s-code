#include <cstdio>
#include <algorithm>
#define re register
#define ll long long
using namespace std;
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
struct Tree
{
	int size,l,r;
} tree[N*100];
#define lc(x) tree[x].l
#define rc(x) tree[x].r
int cnt,root[N];
int c[N];
inline void update(int pre,int &rt,int l,int r,int pos,int val)
{
	rt=++cnt;
	tree[rt]=tree[pre];
	tree[rt].size+=val;
	if(l==r)
		return;
	int mid=(l+r)>>1;
	if(pos<=mid)
		update(lc(pre),lc(rt),l,mid,pos,val);
	else
		update(rc(pre),rc(rt),mid+1,r,pos,val);
}
inline int query(int u,int v,int lca,int falca,int l,int r,int rk)
{
	int sum=tree[lc(u)].size+tree[lc(v)].size-tree[lc(lca)].size-tree[lc(falca)].size;
	if(l==r)
		return l;
	int mid=(l+r)>>1;
	if(rk<=sum)
		return query(lc(u),lc(v),lc(lca),lc(falca),l,mid,rk);
	else
		return query(rc(u),rc(v),rc(lca),rc(falca),mid+1,r,rk-sum);
}
int dfn[N],top[N],fa[N],size[N],son[N],dfstime,dep[N];
inline void dfs1(int u,int fa_)
{
	fa[u]=fa_;
	update(root[fa_],root[u],1,1e5,c[u],1);
	size[u]=1;
	for(re int i=head[u]; i; i=edge[i].next)
	{
		int &v=edge[i].to;
		if(v==fa_)
			continue;
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
int p[N];
int main()
{
	int n,m;
	read(n),read(m);
	for(re int i=1; i<=n; ++i)
	{
		read(c[i]);
		p[i]=c[i];
	}
	sort(p+1,p+1+n);
	int tot=unique(p+1,p+1+n)-1-p;
	for(re int i=1; i<=n; ++i)
		c[i]=lower_bound(p+1,p+1+tot,c[i])-p;
	for(re int i=1; i<n; ++i)
	{
		int u,v;
		read(u),read(v);
		add_edge(u,v);
		add_edge(v,u);
	}
	dfs1(1,0);
	dfs2(1,1);
//	for(re int i=1; i<=n; ++i)
//		printf("%d ",tree[root[i]].size);
//	putchar('\n');
	while(m--)
	{
		int u,v,rk;
		read(u),read(v),read(rk);
//		printf(" %d %d %d\n",u,v,rk);
		int lca=LCA(u,v);
		printf("%d\n",p[query(root[u],root[v],root[lca],root[fa[lca]],1,1e5,rk)]);
	}
	return 0;
}
