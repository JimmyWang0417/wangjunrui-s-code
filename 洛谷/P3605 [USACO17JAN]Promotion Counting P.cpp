#include <cstdio>
#include <algorithm>
#define ll long long
#define re register
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
} edge[N];
int head[N],num_edge;
inline void add_edge(int from,int to)
{
	edge[++num_edge].next=head[from];
	edge[num_edge].to=to;
	head[from]=num_edge;
}
struct Tree
{
	int l,r;
	int size;
} tree[N*40];
#define lc(x) tree[x].l
#define rc(x) tree[x].r
int cnt;
int p[N],tot,a[N],n;
int root[N],ans[N];
inline void update(int &rt,int l,int r,int pos,int val)
{
	if(!rt)
		rt=++cnt;
	tree[rt].size+=val;
	if(l==r)
		return;
	int mid=(l+r)>>1;
	if(pos<=mid)
		update(lc(rt),l,mid,pos,val);
	else
		update(rc(rt),mid+1,r,pos,val);
}
inline int merge(int x,int y,int l=1,int r=tot)
{
	if(!x||!y)
		return x|y;
	tree[x].size+=tree[y].size;
	if(l==r)
		return x;
	lc(x)=merge(lc(x),lc(y));
	rc(x)=merge(rc(x),rc(y));
	return x;
}
inline int query(int &rt,int l,int r,int x,int y)
{
	if(l>y||r<x)
		return 0;
	if(x<=l&&r<=y)
		return tree[rt].size;
	int mid=(l+r)>>1;
	return query(lc(rt),l,mid,x,y)+query(rc(rt),mid+1,r,x,y);
}
inline void dfs(int u)
{
	for(re int i=head[u]; i; i=edge[i].next)
	{
		int &v=edge[i].to;
		dfs(v);
		root[u]=merge(root[u],root[v]);
	}
	if(a[u]!=tot)
		ans[u]=query(root[u],1,tot,a[u]+1,tot);
	update(root[u],1,tot,a[u],1);
}
int main()
{
	read(n);
	for(re int i=1; i<=n; ++i)
	{
		read(a[i]);
		p[i]=a[i];
	}
	std::sort(p+1,p+1+n);
	tot=std::unique(p+1,p+1+n)-1-p;
	for(re int i=2; i<=n; ++i)
	{
		int fa;
		read(fa);
		add_edge(fa,i);
	}
	for(re int i=1; i<=n; ++i)
		a[i]=std::lower_bound(p+1,p+1+tot,a[i])-p;
	dfs(1);
	for(re int i=1; i<=n; ++i)
		printf("%d\n",ans[i]);
	return 0;
}
