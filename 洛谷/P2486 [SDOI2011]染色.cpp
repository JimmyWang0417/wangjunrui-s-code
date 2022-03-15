#include <cstdio>
#include <algorithm>
#define re register
#define ll long long
using namespace std;
template <typename T>
inline void read(T &x)
{
	x=0;
	char s=(char)getchar();
	bool flag=false;
	while(s<'0'||s>'9')
	{
		if(s=='-')
			flag=true;
		s=(char)getchar();
	}
	while(s>='0'&&s<='9')
	{
		x=(x<<1)+(x<<3)+(s^'0');
		s=(char)getchar();
	}
	if(flag)
		x=~x+1;
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
int size[N],son[N],dep[N],top[N],dfn[N],rk[N],fa[N];
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
struct Point
{
	int pre,suf,sum;
	Point(int pr=0,int su=0,int s=0):pre(pr),suf(su),sum(s) {}
	inline Point operator + (const Point &rhs)const
	{
		return Point(pre,rhs.suf,sum+rhs.sum-(suf==rhs.pre?1:0));
	}
};
struct Tree
{
	int lazy;
	Point point;
} tree[N<<2];
#define lc (rt<<1)
#define rc (rt<<1|1)
inline void pushup(int rt)
{
	tree[rt].point=tree[lc].point+tree[rc].point;
	return;
}
inline void pushdown(int rt)
{
	if(!tree[rt].lazy)
		return;
	tree[lc].point.suf=tree[lc].point.pre=tree[lc].lazy=tree[rt].lazy;
	tree[rc].point.suf=tree[rc].point.pre=tree[rc].lazy=tree[rt].lazy;
	tree[lc].point.sum=tree[rc].point.sum=1;
	tree[rt].lazy=0;
	return;
}
int color[N];
inline void build(int rt,int l,int r)
{
	if(l==r)
	{
		tree[rt].point.sum=1;
		tree[rt].point.suf=tree[rt].point.pre=color[rk[l]];
		return;
	}
	int mid=(l+r)>>1;
	build(lc,l,mid);
	build(rc,mid+1,r);
	pushup(rt);
}
inline void change(int rt,int l,int r,int x,int y,int col)
{
	if(x<=l&&r<=y)
	{
		tree[rt].lazy=tree[rt].point.suf=tree[rt].point.pre=col;
		tree[rt].point.sum=1;
		return;
	}
	pushdown(rt);
	int mid=(l+r)>>1;
	if(x<=mid)
		change(lc,l,mid,x,y,col);
	if(mid<y)
		change(rc,mid+1,r,x,y,col);
	pushup(rt);
}
inline Point query(int rt,int l,int r,int x,int y)
{
	if(x<=l&&r<=y)
		return tree[rt].point;
	int mid=(l+r)>>1;
	pushdown(rt);
	if(y<=mid)
		return query(lc,l,mid,x,y);
	if(mid<x)
		return query(rc,mid+1,r,x,y);
	return query(lc,l,mid,x,y)+query(rc,mid+1,r,x,y);
}
int n;
inline void change(int x,int y,int col)
{
	while(top[x]!=top[y])
	{
		if(dep[top[x]]<dep[top[y]])
			swap(x,y);
		change(1,1,n,dfn[top[x]],dfn[x],col);
		x=fa[top[x]];
	}
	if(dep[x]>dep[y])
		swap(x,y);
	change(1,1,n,dfn[x],dfn[y],col);
}
inline Point query(int x,int y)
{
	Point left=Point(),right=Point();
	while(top[x]!=top[y])
	{
		if(dep[top[x]]<dep[top[y]])
		{
			swap(x,y);
			swap(left,right);
		}
		left=query(1,1,n,dfn[top[x]],dfn[x])+left;
		x=fa[top[x]];
//		printf(" %d",left.sum);
	}
	if(dep[x]>dep[y])
	{
		swap(x,y);
		swap(left,right);
	}
	swap(left.pre,left.suf);
//	putchar('\n');
	return (left+query(1,1,n,dfn[x],dfn[y])+right);
}
int m;
char str[5];
int main()
{
	read(n),read(m);
	for(re int i=1; i<=n; ++i)
		read(color[i]);
	for(re int i=1; i<n; ++i)
	{
		int u,v;
		read(u),read(v);
		add_edge(u,v);
		add_edge(v,u);
	}
	dfs1(1,0);
	dfs2(1,1);
	build(1,1,n);
//
	while(m--)
	{
//		printf(" %d\n",query(1,1,n,1,n).sum);
		scanf("%s",str);
		int a,b,c;
		read(a),read(b);
		if(str[0]=='C')
		{
			read(c);
			change(a,b,c);
		}
		else if(str[0]=='Q')
			printf("%d\n",query(a,b).sum);
	}
	return 0;
}
