#include <cstdio>
#include <algorithm>
#define ll long long
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
const int N=5e5+5;
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
int top[N],dfn[N],dfstime;
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
int n;
struct Tree
{
	int tag;
	inline void change(int val)
	{
		tag=val;
	}
} tree[N*4];
#define lc (rt<<1)
#define rc (rt<<1|1)
inline void pushdown(int rt)
{
	if(tree[rt].tag==-1)
		return;
	tree[lc].change(tree[rt].tag);
	tree[rc].change(tree[rt].tag);
	tree[rt].tag=-1;
}
inline void change(int rt,int l,int r,int x,int y,int val)
{
	if(r<x||l>y)
		return;
	if(x<=l&&r<=y)
	{
		tree[rt].change(val);
		return;
	}
	int mid=(l+r)>>1;
	pushdown(rt);
	change(lc,l,mid,x,y,val);
	change(rc,mid+1,r,x,y,val);
}
inline int query(int rt,int l,int r,int pos)
{
	if(l==r)
		return tree[rt].tag;
	int mid=(l+r)>>1;
	pushdown(rt);
	if(pos<=mid)
		return query(lc,l,mid,pos);
	else
		return query(rc,mid+1,r,pos);
}
inline void update(int x,int y,int val)
{
	while(top[x]!=top[y])
	{
		if(dep[top[x]]<dep[top[y]])
			swap(x,y);
		change(1,1,n,dfn[top[x]],dfn[x],val);
//		printf(" %d %d\n",top[x],x);
		x=fa[top[x]];
	}
	if(dep[x]>dep[y])
		swap(x,y);
//	for(re int i=1; i<=n*2; ++i)
//		printf(" %d %d\n",tree[i].ans,tree[i].tag);
//	putchar('\n');
	change(1,1,n,dfn[x],dfn[y],val);
//	printf(" %d %d\n",x,y); 
}
int main()
{
	read(n);
	for(re int i=1; i<n; ++i)
	{
		int u,v;
		read(u),read(v);
		add_edge(u,v);
		add_edge(v,u);
	}
	dfs1(1,0);
	dfs2(1,1);
	int q;
	read(q);
	while(q--)
	{
		int opt,x;
		read(opt),read(x);
		if(opt==1)
			change(1,1,n,dfn[x],dfn[x]+size[x]-1,1);
		else if(opt==2)
			update(1,x,0);
		else if(opt==3)
			printf("%d\n",query(1,1,n,dfn[x]));
//		for(re int i=1; i<=n*2; ++i)
//			printf(" %d %d\n",tree[i].ans,tree[i].tag);
//		putchar('\n');
	}
	return 0;
}
