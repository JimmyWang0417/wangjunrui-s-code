#include <cstdio>
#include <cstring>
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
const int N=1e5+5,INF=0x7fffffff;
int n;
struct Edge
{
	int next,to;
} edge[N<<1];
int w[N];
int head[N],num_edge;
inline void add_edge(int from,int to)
{
	edge[++num_edge].next=head[from];
	edge[num_edge].to=to;
	head[from]=num_edge;
}
int size[N],dep[N],son[N],fa[N],ww[N];
int pos[N];
inline void dfs1(int u,int _fa)
{
	fa[u]=_fa;
	dep[u]=dep[_fa]+1;
	size[u]=1;
	son[u]=0;
	for(re int i=head[u]; i; i=edge[i].next)
	{
		int &v=edge[i].to;
		if(v==_fa)
			continue;
		ww[v]=w[(i+1)>>1];
		pos[(i+1)>>1]=v;
		dfs1(v,u);
		size[u]+=size[v];
		if(size[v]>size[son[u]])
			son[u]=v;
	}
}
int top[N],dfn[N],rk[N],dfstime;
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
	int max;
} tree[N*4];
#define lc (rt<<1)
#define rc (rt<<1|1)
inline void build(int rt,int l,int r)
{
	if(l==r)
	{
		tree[rt].max=ww[rk[l]];
		return;
	}
	int mid=(l+r)>>1;
	build(lc,l,mid);
	build(rc,mid+1,r);
	tree[rt].max=max(tree[lc].max,tree[rc].max);
}
inline void change(int rt,int l,int r,int poss,int val)
{
	if(l==r)
	{
		tree[rt].max=val;
		return;
	}
	int mid=(l+r)>>1;
	if(poss<=mid)
		change(lc,l,mid,poss,val);
	else
		change(rc,mid+1,r,poss,val);
	tree[rt].max=max(tree[lc].max,tree[rc].max);
}
inline int query(int rt,int l,int r,int x,int y)
{
	if(r<x||l>y)
		return ~INF;
	if(x<=l&&r<=y)
		return tree[rt].max;
	int mid=(l+r)>>1;
	return max(query(lc,l,mid,x,y),query(rc,mid+1,r,x,y));
}
inline int query(int x,int y)
{
	int ans=~INF;
	while(top[x]!=top[y])
	{
		if(dep[top[x]]<dep[top[y]])
			swap(x,y);
		ans=max(ans,query(1,1,n,dfn[top[x]],dfn[x]));
		x=fa[top[x]];
	}
	if(dep[x]>dep[y])
		swap(x,y);
	ans=max(ans,query(1,1,n,dfn[x]+1,dfn[y]));
	return ans;
}
inline void work()
{
	read(n);
	for(re int i=1; i<n; ++i)
	{
		int u,v;
		read(u),read(v),read(w[i]);
		add_edge(u,v);
		add_edge(v,u);
	}
	dfs1(1,0);
	dfs2(1,1);
	build(1,1,n);
//	printf("%d\n",num_edge);
//	for(re int i=1; i<=n; ++i)
//		printf("%d %d %d %d %d %d\n",size[i],son[i],dep[i],top[i],fa[i],dfn[i]);
	while(1)
	{
		char str[15];
		scanf("%s",str);
		if(str[0]=='C')
		{
			int poss,val;
			read(poss),read(val);
			change(1,1,n,dfn[pos[poss]],val);
		}
		else if(str[0]=='Q')
		{
			int a,b;
			read(a),read(b);
			printf("%d\n",query(a,b));
		}
		else if(str[0]=='D')
			break;
	}
	memset(head+1,dfstime=num_edge=0,sizeof(int)*(n+1));
}
int main()
{
	int T;
	read(T);
	while(T--)
		work();
	return 0;
}
