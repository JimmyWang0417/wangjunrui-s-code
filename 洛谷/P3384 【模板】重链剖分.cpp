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
const int N=1e6+10;
#define M (N<<1)
struct Edge
{
	int next,to;
} edge[M];
int head[N],num_edge;
struct Tree
{
	int l,r,size,sum,lazy;
} tree[N];
int n,m,root,mod,cnt,rk[N],num[N];
inline void add_edge(int from,int to)
{
	edge[++num_edge].next=head[from];
	edge[num_edge].to=to;
	head[from]=num_edge;
}
int dep[N],fa[N],son[N],size[N],top[N],idx[N];
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
	return;
}
inline void dfs2(int u,int tp)
{
	idx[u]=++cnt;
	rk[cnt]=u;
	top[u]=tp;
	if(!son[u])
		return;
	dfs2(son[u],tp);
	for(re int i=head[u]; i; i=edge[i].next)
	{
		int &v=edge[i].to;
		if(idx[v])
			continue;
		dfs2(v,v);
	}
	return;
}
inline void pushdown(int k)
{
	if(!tree[k].lazy)
		return;
	tree[ls].sum=(tree[ls].sum+tree[k].lazy*tree[ls].size%mod)%mod;
	tree[rs].sum=(tree[rs].sum+tree[k].lazy*tree[rs].size%mod)%mod;
	tree[ls].lazy=(tree[ls].lazy+tree[k].lazy)%mod;
	tree[rs].lazy=(tree[rs].lazy+tree[k].lazy)%mod;
	tree[k].lazy=0;
	return;
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
	tree[k].sum=(tree[ls].sum+tree[rs].sum)%mod;
	return;
}
inline void update1(int k,int l,int r,int val)
{
	if(l<=tree[k].l&&tree[k].r<=r)
	{
		tree[k].sum=(tree[k].sum+tree[k].size*val%mod)%mod;
		tree[k].lazy=(tree[k].lazy+val)%mod;
		return;
	}
	pushdown(k);
	int mid=(tree[k].l+tree[k].r)>>1;
	if(l<=mid)
		update1(ls,l,r,val);
	if(mid<r)
		update1(rs,l,r,val);
	tree[k].sum=(tree[ls].sum+tree[rs].sum)%mod;
	return;
}
inline void update2(int x,int y,int val)
{
	while(top[x]!=top[y])
	{
		if(dep[top[x]]<dep[top[y]])
			swap(x,y);
		update1(1,idx[top[x]],idx[x],val);
		x=fa[top[x]];
	}
	if(dep[x]>dep[y])
		swap(x,y);
	update1(1,idx[x],idx[y],val);
	return;
}
inline int ask1(int k,int l,int r)
{
	int ans=0;
	if(l<=tree[k].l&&tree[k].r<=r)
		return tree[k].sum;
	pushdown(k);
	int mid=(tree[k].l+tree[k].r)>>1;
	if(l<=mid)
		ans=(ans+ask1(ls,l,r))%mod;
	if(mid<r)
		ans=(ans+ask1(rs,l,r))%mod;
	return ans;
}
inline int ask2(int x,int y)
{
	int ans=0;
	while(top[x]!=top[y])
	{
		if(dep[top[x]]<dep[top[y]])
			swap(x,y);
		ans=(ans+ask1(1,idx[top[x]],idx[x]))%mod;
		x=fa[top[x]];
	}
	if(dep[x]>dep[y])
		swap(x,y);
	ans=(ans+ask1(1,idx[x],idx[y]))%mod;
	return ans;
}
int main()
{
	read(n),read(m),read(root),read(mod);
	for(re int i=1; i<=n; ++i)
		read(num[i]);
	for(re int i=1,x,y; i<=n-1; ++i)
	{
		read(x),read(y);
		add_edge(x,y);
		add_edge(y,x);
	}
	dfs1(root,0);
	dfs2(root,root);
	build(1,1,n);
	for(re int i=1,x,y,z,opt; i<=m; ++i)
	{
		read(opt);
		if(opt==1)
		{
			read(x),read(y),read(z);
			update2(x,y,z%mod);
		}
		else if(opt==2)
		{
			read(x),read(y);
			printf("%d\n",ask2(x,y));
		}
		else if(opt==3)
		{
			read(x),read(y);
			update1(1,idx[x],idx[x]+size[x]-1,y%mod);
		}
		else if(opt==4)
		{
			read(x);
			printf("%d\n",ask1(1,idx[x],idx[x]+size[x]-1));
		}
	}
	return 0;
}
