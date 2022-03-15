#include<cstdio>
#include<algorithm>
using namespace std;
#define ll long long
#define re register
#define ls (k<<1)
#define rs (k<<1|1)
template<typename T>
inline void read(T&x)
{
	x=0;
	char s=getchar();
	bool f=false;
	while(!(s>='0'&&s<='9'))
	{
		if(s=='-')
			f=true;
		s=getchar();
	}
	while(s>='0'&&s<='9')
	{
		x=(x<<1)+(x<<3)+s-'0';
		s=getchar();
	}
	if(f)
		x=(~x)+1;
	return;
}
const int N=1e5+10;
#define M (N<<1)
struct Edge
{
	int next,to;
} edge[M];
int num_edge,head[N];
int n,m,cnt,rk[N],id[N],dep[N],fa[N],top[N],son[N],size[N],num[N];
ll res;
struct Tree
{
	int l,r,size;
	ll lazy,sum;
} tree[N<<2];
inline void add_edge(int from,int to)
{
	edge[++num_edge].next=head[from];
	edge[num_edge].to=to;
	head[from]=num_edge;
}
inline void dfs1(int u,int f)
{
	dep[u]=dep[f]+1;
	fa[u]=f;
	size[u]=1;
	for(re int i=head[u]; i; i=edge[i].next)
	{
		int &v=edge[i].to;
		if(v==f)
			continue;
		dfs1(v,u);
		size[u]+=size[v];
		if(size[v]>size[son[u]])
			son[u]=v;
	}
}
inline void dfs2(int u,int tp)
{
	id[u]=++cnt;
	rk[cnt]=u;
	top[u]=tp;
	if(!son[u])
		return;
	dfs2(son[u],tp);
	for(re int i=head[u]; i; i=edge[i].next)
	{
		int &v=edge[i].to;
		if(id[v])
			continue;
		dfs2(v,v);
	}
	return;
}
inline void pushup(int k)
{
	tree[k].sum=tree[ls].sum+tree[rs].sum;
}
inline void pushdown(int k)
{
	if(!tree[k].lazy)
		return;
	tree[ls].lazy+=tree[k].lazy;
	tree[rs].lazy+=tree[k].lazy;
	tree[ls].sum+=tree[k].lazy*tree[ls].size;
	tree[rs].sum+=tree[k].lazy*tree[rs].size;
	tree[k].lazy=0;
}
inline void build(int k,int l,int r)
{
	tree[k].l=l;
	tree[k].r=r;
	tree[k].size=r-l+1;
	if(l==r)
	{
		tree[k].sum=num[rk[l]];
		return;
	}
	int mid=l+r>>1;
	build(ls,l,mid);
	build(rs,mid+1,r);
	pushup(k);
	return;
}
inline void update(int k,int l,int r,int val)
{
	if(l<=tree[k].l&&tree[k].r<=r)
	{
		tree[k].sum+=(ll)val*tree[k].size;
		tree[k].lazy+=val;
		return;
	}
	pushdown(k);
	int mid=(tree[k].l+tree[k].r)>>1;
	if(l<=mid)
		update(ls,l,r,val);
	if(mid<r)
		update(rs,l,r,val);
	pushup(k);
	return;
}
inline void query(int k,int l,int r)
{
	if(l<=tree[k].l&&tree[k].r<=r)
	{
		res+=tree[k].sum;
		return;
	}
	pushdown(k);
	int mid=(tree[k].l+tree[k].r)>>1;
	if(l<=mid)
		query(ls,l,r);
	if(mid<r)
		query(rs,l,r);
}
inline ll ask(int x,int y)
{
	ll ans=0ll;
	while(top[x]!=top[y])
	{
		if(dep[top[x]]<dep[top[y]])
			swap(x,y);
		res=0;
		query(1,id[top[x]],id[x]);
		ans+=res;
		x=fa[top[x]];
	}
	if(dep[x]>dep[y])
		swap(x,y);
	res=0;
	query(1,id[x],id[y]);
	ans+=res;
	return ans;
}
int main()
{
	read(n),read(m);
	for(re int i=1; i<=n; ++i)
		read(num[i]);
	for(re int i=1,x,y; i<n; ++i)
	{
		read(x),read(y);
		add_edge(x,y);
		add_edge(y,x);
	}
	dfs1(1,0);
	dfs2(1,1);
	build(1,1,n);
	for(re int i=1,opt,x,y; i<=m; ++i)
	{
		read(opt);
		if(opt==1)
		{
			read(x),read(y);
			update(1,id[x],id[x],y);
		}
		else if(opt==2)
		{
			read(x),read(y);
			update(1,id[x],id[x]+size[x]-1,y);
		}
		else if(opt==3)
		{
			read(x);
			printf("%lld\n",ask(1,x));
		}
	}
	return 0;
}
