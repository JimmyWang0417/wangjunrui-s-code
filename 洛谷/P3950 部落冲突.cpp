#include <bits/stdc++.h>
#define lowbit(x) ((x)&(-(x)))
#define re register
#define ll long long
#define ull unsigned long long
#define rep(i,a,b) for(re int i=a;i<=b;++i)
#define per(i,a,b) for(re int i=a;i>=b;--i)
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
template<typename T,typename ...T1>
inline void read(T&x,T1&...x1)
{
	read(x);
	read(x1...);
}
template<typename T>
inline void clear(T*array,int l,int r,int val)
{
	memset(&array[l],val,sizeof(T)*(r-l+1));
}
using namespace std;
const int N=3e5+5;
int n,m;
struct Edge
{
	int next,to;
} edge[N*2];
int head[N],num_edge;
inline void add_edge(int from,int to)
{
	edge[++num_edge].next=head[from];
	edge[num_edge].to=to;
	head[from]=num_edge;
}
int size[N],son[N];
int dep[N],fa[N];
int dfn[N],dfstime;
int top[N];
inline void dfs1(int u,int _fa)
{
	fa[u]=_fa;
	dep[u]=dep[_fa]+1;
	size[u]=1;
	for(int i=head[u]; i; i=edge[i].next)
	{
		int &v=edge[i].to;
		if(v==_fa)
			continue;
		dfs1(v,u);
		size[u]+=size[v];
		if(size[son[u]]<size[v])
			son[u]=v;
	}
}
inline void dfs2(int u,int topf)
{
	dfn[u]=++dfstime;
	top[u]=topf;
	if(son[u])
		dfs2(son[u],topf);
	for(int i=head[u]; i; i=edge[i].next)
	{
		int &v=edge[i].to;
		if(top[v])
			continue;
		dfs2(v,v);
	}
}
struct Tree
{
	int sum;
} tree[N*4];
#define lc (rt<<1)
#define rc (rt<<1|1)
inline void build(int rt,int l,int r)
{
	tree[rt].sum=r-l+1;
	if(l==r)
		return;
	int mid=(l+r)>>1;
	build(lc,l,mid);
	build(rc,mid+1,r);
}
inline void update(int rt,int l,int r,int pos,int val)
{
	tree[rt].sum+=val;
	if(l==r)
		return;
	int mid=(l+r)>>1;
	if(pos<=mid)
		update(lc,l,mid,pos,val);
	else
		update(rc,mid+1,r,pos,val);
}
inline int query(int rt,int l,int r,int x,int y)
{
	if(r<x||l>y)
		return 0;
	if(x<=l&&r<=y)
		return tree[rt].sum;
	int mid=(l+r)>>1;
	return query(lc,l,mid,x,y)+query(rc,mid+1,r,x,y);
}
inline bool query(int x,int y)
{
	int len=0,res=0;
	while(top[x]!=top[y])
	{
		if(dep[top[x]]<dep[top[y]])
			swap(x,y);
		len+=dep[x]-dep[fa[top[x]]];
		res+=query(1,1,n,dfn[top[x]],dfn[x]);
		x=fa[top[x]];
	}
	if(dep[x]>=dep[y])
		swap(x,y);
	len+=dep[y]-dep[x];
	res+=query(1,1,n,dfn[x]+1,dfn[y]);
	return len==res;
}
int a[N];
signed main()
{
	read(n,m);
	for(int i=1; i<n; ++i)
	{
		int u,v;
		read(u,v);
		add_edge(u,v);
		add_edge(v,u);
	}
	dfs1(1,0);
	dfs2(1,1);
	build(1,1,n);
	int cnt=0;
	for(int i=1; i<=m; ++i)
	{
		char opt[10];
		scanf("%s",opt);
		if(opt[0]=='Q')
		{
			int x,y;
			read(x,y);
			puts(query(x,y)?"Yes":"No");
		}
		else if(opt[0]=='C')
		{
			++cnt;
			int &x=a[cnt],y;
			read(x,y);
			if(dep[x]<dep[y])
				swap(x,y);
			update(1,1,n,dfn[x],-1);
		}
		else if(opt[0]=='U')
		{
			int x;
			read(x);
			update(1,1,n,dfn[a[x]],1);
		}
	}
	return 0;
}


