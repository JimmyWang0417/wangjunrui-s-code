#include <cstdio>
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
int n;
struct Tree
{
	int l,r;
	int size;
	ll ans;
} tree[N*40];
int cnt,root[N];
int c[N];
#define lc(x) tree[x].l
#define rc(x) tree[x].r
inline void pushup(int rt)
{
	if(tree[lc(rt)].size<tree[rc(rt)].size)
	{
		tree[rt].size=tree[rc(rt)].size;
		tree[rt].ans=tree[rc(rt)].ans;
	}
	else if(tree[lc(rt)].size>tree[rc(rt)].size)
	{
		tree[rt].size=tree[lc(rt)].size;
		tree[rt].ans=tree[lc(rt)].ans;
	}
	else
	{
		tree[rt].size=tree[lc(rt)].size;
		tree[rt].ans=tree[lc(rt)].ans+tree[rc(rt)].ans;
	}
}
inline int merge(int x,int y,int l,int r)
{
	if(!x||!y)
		return x|y;
	if(l==r)
	{
		tree[x].size+=tree[y].size;
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
		rt=++cnt;
	if(l==r)
	{
		tree[rt].size+=val;
		tree[rt].ans=l;
		return;
	}
	int mid=(l+r)>>1;
	if(pos<=mid)
		update(lc(rt),l,mid,pos,val);
	else
		update(rc(rt),mid+1,r,pos,val);
	pushup(rt);
}
ll ans[N];
inline void dfs(int u,int fa)
{
	for(re int i=head[u]; i; i=edge[i].next)
	{
		int &v=edge[i].to;
		if(v==fa)
			continue;
		dfs(v,u);
		root[u]=merge(root[u],root[v],1,100000);
	}
	update(root[u],1,100000,c[u],1);
	ans[u]=tree[root[u]].ans;
}
int main()
{
	read(n);
	for(re int i=1; i<=n; ++i)
		read(c[i]);
	for(re int i=1; i<n; ++i)
	{
		int u,v;
		read(u),read(v);
		add_edge(u,v);
		add_edge(v,u);
	}
	dfs(1,0);
	for(re int i=1; i<=n; ++i)
		printf("%lld ",ans[i]);
	putchar('\n');
	return 0;
}
