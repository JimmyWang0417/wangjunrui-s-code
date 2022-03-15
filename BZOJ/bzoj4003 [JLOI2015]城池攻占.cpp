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
const int N=300000+5;
struct Tree
{
	int dist;
	int l,r,size;
	ll val,add,mul;
} tree[N];
#define lc(x) tree[x].l
#define rc(x) tree[x].r
int root[N];
inline void pushup(int rt)
{
	if(tree[lc(rt)].dist<tree[rc(rt)].dist)
		swap(lc(rt),rc(rt));
	tree[rt].dist=tree[rc(rt)].dist+1;
}
inline void pushdown(int rt)
{
	if(tree[rt].add==0&&tree[rt].mul==1)
		return;
	if(lc(rt))
	{
		tree[lc(rt)].val=tree[lc(rt)].val*tree[rt].mul+tree[rt].add;
		tree[lc(rt)].add=tree[lc(rt)].add*tree[rt].mul+tree[rt].add;
		tree[lc(rt)].mul*=tree[rt].mul;
	}
	if(rc(rt))
	{
		tree[rc(rt)].val=tree[rc(rt)].val*tree[rt].mul+tree[rt].add;
		tree[rc(rt)].add=tree[rc(rt)].add*tree[rt].mul+tree[rt].add;
		tree[rc(rt)].mul*=tree[rt].mul;
	}
	tree[rt].add=0,tree[rt].mul=1;
}
inline int merge(int x,int y)
{
	if(!x||!y)
		return x|y;
	if(tree[x].val>tree[y].val)
		swap(x,y);
	pushdown(x);
	rc(x)=merge(rc(x),y);
	pushup(x);
	return x;
}
int flag[N],ans1[N],ans2[N],c[N],dep[N];
ll value[N],h[N];
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
inline void dfs(int u)
{
	for(re int i=head[u]; i; i=edge[i].next)
	{
		int &v=edge[i].to;
		dep[v]=dep[u]+1;
		dfs(v);
		root[u]=merge(root[u],root[v]);
	}
	while(root[u]&&tree[root[u]].val<h[u])
	{
		pushdown(root[u]);
		++ans1[u],ans2[root[u]]=dep[c[root[u]]]-dep[u];
		root[u]=merge(lc(root[u]),rc(root[u]));
	}
	const int &rt=root[u];
	if(flag[u]==0)
	{
		tree[rt].val+=value[u];
		tree[rt].add+=value[u];
	}
	else if(flag[u]==1)
	{
		tree[rt].val*=value[u];
		tree[rt].add*=value[u];
		tree[rt].mul*=value[u];
	}
	return;
}
int n,m;
int main()
{
	dep[1]=1;
	read(n),read(m);
	for(re int i=1; i<=n; ++i)
		read(h[i]);
	for(re int i=2; i<=n; ++i)
	{
		int fa;
		read(fa),read(flag[i]),read(value[i]);
		add_edge(fa,i);
	}
	for(re int i=1; i<=m; ++i)
	{
		tree[i].mul=1;
		read(tree[i].val),read(c[i]);
		root[c[i]]=merge(root[c[i]],i);
	}
	dfs(1);
	while(root[1])
	{
		pushdown(root[1]);
		ans2[root[1]]=dep[c[root[1]]];
		root[1]=merge(lc(root[1]),rc(root[1]));
	}
	for(re int i=1; i<=n; ++i)
		printf("%d\n",ans1[i]);
	for(re int i=1; i<=m; ++i)
		printf("%d\n",ans2[i]);
	return 0;
}
