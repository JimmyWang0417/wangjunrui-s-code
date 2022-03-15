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
const int N=1e5+5;
struct Edge
{
	int next,to,dis;
} edge[N<<1];
int head[N],num_edge;
inline void add_edge(int from,int to,int dis)
{
	edge[++num_edge].next=head[from];
	edge[num_edge].to=to;
	edge[num_edge].dis=dis;
	head[from]=num_edge;
}
int top[N],dep[N],fa[N],size[N],son[N],dfn[N],rk[N];
int value[N];
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
		value[v]=edge[i].dis;
		dfs1(v,u);
		size[u]+=size[v];
		if(size[v]>size[son[u]])
			son[u]=v;
	}
}
int dfstime;
inline void dfs2(int u,int topf)
{
	top[u]=topf;
	dfn[u]=++dfstime;
	rk[dfstime]=u;
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
	int lazy,max,add;
} tree[N<<2];
#define lc (rt<<1)
#define rc (rt<<1|1)
inline void pushdown(int rt)
{
	if(tree[rt].lazy>=0)
	{
		tree[lc].lazy=tree[rc].lazy=tree[lc].max=tree[rc].max=tree[rt].lazy;
		tree[lc].add=tree[rc].add=0;
		tree[rt].lazy=-1;
	}
	if(tree[rt].add)
	{
		tree[lc].add+=tree[rt].add;
		tree[rc].add+=tree[rt].add;
		tree[lc].max+=tree[rt].add;
		tree[rc].max+=tree[rt].add;
		tree[rt].add=0;
	}
}
inline void pushup(int rt)
{
	tree[rt].max=max(tree[lc].max,tree[rc].max);
	return;
}
inline void build(int rt,int l,int r)
{
	tree[rt].lazy=-1;
	if(l==r)
	{
		tree[rt].max=value[rk[l]];
		return;
	}
	int mid=(l+r)>>1;
	build(lc,l,mid);
	build(rc,mid+1,r);
	pushup(rt);
}
inline void change1(int rt,int l,int r,int x,int y,int val)
{
	if(r<x||l>y)
		return;
	if(x<=l&&r<=y)
	{
		tree[rt].add=0;
		tree[rt].max=tree[rt].lazy=val;
		return;
	}
	pushdown(rt);
	int mid=(l+r)>>1;
	change1(lc,l,mid,x,y,val);
	change1(rc,mid+1,r,x,y,val);
	pushup(rt);
}
inline void change2(int rt,int l,int r,int x,int y,int val)
{
	if(r<x||l>y)
		return;
	if(x<=l&&r<=y)
	{
		tree[rt].add+=val;
		tree[rt].max+=val;
		return;
	}
	pushdown(rt);
	int mid=(l+r)>>1;
	change2(lc,l,mid,x,y,val);
	change2(rc,mid+1,r,x,y,val);
	pushup(rt);
}
inline int query(int rt,int l,int r,int x,int y)
{
	if(r<x||l>y)
		return ~0x3f3f3f3f;
	if(x<=l&&r<=y)
		return tree[rt].max;
	pushdown(rt);
	int mid=(l+r)>>1;
	return max(query(lc,l,mid,x,y),query(rc,mid+1,r,x,y));
}
int n;
inline void update1(int x,int y,int val)
{
	while(top[x]!=top[y])
	{
		if(dep[top[x]]<dep[top[y]])
			swap(x,y);
		change1(1,1,n,dfn[top[x]],dfn[x],val);
		x=fa[top[x]];
	}
	if(dep[x]>dep[y])
		swap(x,y);
	change1(1,1,n,dfn[x]+1,dfn[y],val);
}
inline void update2(int x,int y,int val)
{
	while(top[x]!=top[y])
	{
		if(dep[top[x]]<dep[top[y]])
			swap(x,y);
		change2(1,1,n,dfn[top[x]],dfn[x],val);
		x=fa[top[x]];
	}
	if(dep[x]>dep[y])
		swap(x,y);
	change2(1,1,n,dfn[x]+1,dfn[y],val);
}
inline int ask(int x,int y)
{
	int res=~0x3f3f3f3f;
	while(top[x]!=top[y])
	{
		if(dep[top[x]]<dep[top[y]])
			swap(x,y);
		res=max(res,query(1,1,n,dfn[top[x]],dfn[x]));
		x=fa[top[x]];
	}
	if(dep[x]>dep[y])
		swap(x,y);
	res=max(res,query(1,1,n,dfn[x]+1,dfn[y]));
	return res;
}
char str[10];
int main()
{
	read(n);
	for(re int i=1; i<n; ++i)
	{
		int u,v,w;
		read(u),read(v),read(w);
		add_edge(u,v,w);
		add_edge(v,u,w);
	}
	dfs1(1,0);
	dfs2(1,1);
	build(1,1,n);
	while(1)
	{
		scanf("%s",str);
		if(str[0]=='S')
			return 0;
//		printf("%s %d %d\n",str,uu,vv);
		if(str[0]=='C')
		{
			if(str[1]=='h')
			{
				int k,w;
				read(k),read(w);
				int x, y;
				x=edge[k*2].to, y=edge[k*2-1].to;
				if(fa[y]==x)
					swap(x,y);
				change1(1,1,n,dfn[x],dfn[x],w);
			}
			else
			{
				int u,v,w;
				read(u),read(v),read(w);
				update1(u,v,w);
			}
		}
		else if(str[0]=='A')
		{
			int u,v,w;
			read(u),read(v),read(w);
			update2(u,v,w);
		}
		else if(str[0]=='M')
		{
			int u,v;
			read(u),read(v);
			printf("%d\n",ask(u,v));
		}

	}
	return 0;
}
