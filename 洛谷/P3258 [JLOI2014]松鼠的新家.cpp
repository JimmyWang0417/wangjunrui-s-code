#include <cstdio>
#include <algorithm>
#define re register
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
#define size sze
const int N=300000+5;
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
int top[N],dfn[N],dep[N],fa[N],size[N],son[N];
inline void dfs1(int u,int fa_)
{
	fa[u]=fa_;
	dep[u]=dep[fa_]+1;
	size[u]=1;
	for(re int i=head[u]; i; i=edge[i].next)
	{
		int &v=edge[i].to;
		if(v==fa_)
			continue;
		dfs1(v,u);
		size[u]+=size[v];
		if(size[v]>size[son[u]])
			son[u]=v;
	}
}
int dfstime;
inline void dfs2(int u,int topf)
{
//	printf(" %d",u);
	dfn[u]=++dfstime;
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
struct Tree
{
	int lazy;
	int sum;
} tree[N<<2];
#define lc (rt<<1)
#define rc (rt<<1|1)
inline void pushdown(int rt,int l,int mid,int r)
{
	if(!tree[rt].lazy)
		return;
	tree[lc].lazy+=tree[rt].lazy;
	tree[rc].lazy+=tree[rt].lazy;
	tree[lc].sum+=(mid-l+1)*tree[rt].lazy;
	tree[rc].sum+=(r-mid)*tree[rt].lazy;
	tree[rt].lazy=0;
}
inline void change(int rt,int l,int r,int x,int y,int val)
{
	if(x<=l&&r<=y)
	{
		tree[rt].lazy+=val;
		tree[rt].sum+=(r-l+1)*val;
		return;
	}
	int mid=(l+r)>>1;
	pushdown(rt,l,mid,r);
	if(x<=mid)
		change(lc,l,mid,x,y,val);
	if(mid<y)
		change(rc,mid+1,r,x,y,val);
	tree[rt].sum=tree[lc].sum+tree[rc].sum;
}
inline int query(int rt,int l,int r,int pos)
{
	if(l==r&&l==pos)
		return tree[rt].sum;
	int mid=(l+r)>>1;
	pushdown(rt,l,mid,r);
	if(pos<=mid)
		return query(lc,l,mid,pos);
	else
		return query(rc,mid+1,r,pos);
}
int n,a[N];
inline void update(int x,int y)
{
	while(top[x]!=top[y])
	{
		if(dep[top[x]]<dep[top[y]])
			swap(x,y);

		change(1,1,n,dfn[top[x]],dfn[x],1);
		x=fa[top[x]];
	}
	if(dep[x]>dep[y])
		swap(x,y);
	change(1,1,n,dfn[x],dfn[y],1);
}
int main()
{
	read(n);
	for(re int i=1; i<=n; ++i)
		read(a[i]);
	for(re int i=1; i<n; ++i)
	{
		int u,v;
		read(u),read(v);
		add_edge(u,v);
		add_edge(v,u);
	}
	dfs1(1,0);
	dfs2(1,1);
	for(re int i=1; i<n; ++i)
	{
		update(a[i],a[i+1]);
		change(1,1,n,dfn[a[i+1]],dfn[a[i+1]],-1);
	}
	for(re int i=1; i<=n; ++i)
		printf("%d\n",query(1,1,n,dfn[i]));
	return 0;
}
