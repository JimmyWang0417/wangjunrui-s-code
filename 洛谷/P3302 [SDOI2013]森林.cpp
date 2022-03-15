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
inline void clear(T*a,int l,int r,int val)
{
	memset(&a[l],val,sizeof(T)*(r-l+1));
}
const int N=8e4+5;
struct Edge
{
	int next,to;
} edge[N*100];
int head[N],num_edge;
inline void add_edge(int from,int to)
{
	edge[++num_edge].next=head[from];
	edge[num_edge].to=to;
	head[from]=num_edge;
}
const int MAX=1e9;
struct Tree
{
	int l,r,size;
} tree[N*400];
int root[N],cnt;
#define lc(x) tree[x].l
#define rc(x) tree[x].r
#define size(x) tree[x].size
inline void update(int pre,int &rt,int l,int r,int pos)
{
	rt=++cnt;
	tree[rt]=tree[pre];
	++tree[rt].size;
	if(l==r)
		return;
	int mid=(l+r)>>1;
	if(pos<=mid)
		update(lc(pre),lc(rt),l,mid,pos);
	else
		update(rc(pre),rc(rt),mid+1,r,pos);
}
inline int query(int add1,int add2,int mul1,int mul2,int l,int r,int rk)
{
	if(l==r)
		return l;
	int mid=(l+r)>>1,sum=size(lc(add1))+size(lc(add2))-size(lc(mul1))-size(lc(mul2));
	if(rk<=sum)
		return query(lc(add1),lc(add2),lc(mul1),lc(mul2),l,mid,rk);
	else
		return query(rc(add1),rc(add2),rc(mul1),rc(mul2),mid+1,r,rk-sum);
}
#undef lc
#undef rc
#undef size
#define size sze
int a[N];
int size[N],fa[N],f[N][25],dep[N];
inline void dfs(int u,int _fa,int rt)
{
	dep[u]=dep[_fa]+1;
	f[u][0]=fa[u]=_fa;
	update(root[_fa],root[u],0,MAX,a[u]);
	++size[rt];
	for(re int i=0; i<20; ++i)
		f[u][i+1]=f[f[u][i]][i];
	for(re int i=head[u]; i; i=edge[i].next)
	{
		int &v=edge[i].to;
		if(v==_fa)
			continue;
		dfs(v,u,rt);
	}
}
inline int getlca(int u,int v)
{
	if(dep[u]<dep[v])
		std::swap(u,v);
	for(re int i=20; i>=0; --i)
		if(dep[f[u][i]]>=dep[v])
			u=f[u][i];
	if(u==v)
		return u;
	for(re int i=20; i>=0; --i)
		if(f[u][i]!=f[v][i])
		{
			u=f[u][i];
			v=f[v][i];
		}
	return f[u][0];
}
inline int find(int x)
{
	return !fa[x]?x:fa[x]=find(fa[x]);
}
signed main()
{
	int tasecase;
	read(tasecase);
	int n,m,t;
	read(n,m,t);
	for(re int i=1; i<=n; ++i)
		read(a[i]);
	for(re int i=1; i<=m; ++i)
	{
		int u,v;
		read(u,v);
		add_edge(u,v);
		add_edge(v,u);
	}
	for(re int i=1; i<=n; ++i)
		if(!dep[i])
			dfs(i,0,i);
	int lastans=0;
	for(re int i=1; i<=t; ++i)
	{
		char opt[3];
		scanf("%s",opt);
		if(opt[0]=='Q')
		{
			int x,y,k;
			read(x,y,k);
			x^=lastans,y^=lastans,k^=lastans;
			int lca=getlca(x,y);
//			printf("%d %d %d\n",x,y,lca);
			printf("%d\n",lastans=query(root[x],root[y],root[lca],root[f[lca][0]],0,MAX,k));
		}
		else if(opt[0]=='L')
		{
			int x,y;
			read(x,y);
			x^=lastans,y^=lastans;
			add_edge(x,y),add_edge(y,x);
			if(size[find(x)]>size[find(y)])
				std::swap(x,y);
			dfs(x,y,find(y));
		}
	}
	return 0;
}


