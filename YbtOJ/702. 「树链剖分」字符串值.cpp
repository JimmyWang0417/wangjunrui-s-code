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
const int N=6e5+5;
const int mod=1e9+7;
struct SAM
{
	int fa,len,ch[26];
} point[N];
int tot=1,las=1;
inline int insert(int c)
{
	int p=las,np=las=++tot;
	point[np].len=point[p].len+1;
	for(; p&&!point[p].ch[c]; p=point[p].fa)
		point[p].ch[c]=np;
	if(!p)
		point[np].fa=1;
	else
	{
		int q=point[p].ch[c];
		if(point[q].len==point[p].len+1)
			point[np].fa=q;
		else
		{
			int nq=++tot;
			point[nq]=point[q];
			point[nq].len=point[p].len+1;
			point[q].fa=point[np].fa=nq;
			for(; p&&point[p].ch[c]==q; p=point[p].fa)
				point[p].ch[c]=nq;
		}
	}
	return np;
}
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
int id[N];
int n;
char str[N];
#define size sze
int size[N],son[N];
int fa[N];
inline void dfs1(int u)
{
	size[u]=1;
	for(int i=head[u]; i; i=edge[i].next)
	{
		int &v=edge[i].to;
		fa[v]=u;
		dfs1(v);
		size[u]+=size[v];
		if(size[v]>size[son[u]])
			son[u]=v;
	}
}
int top[N],dfn[N],rk[N],dfstime;
inline void dfs2(int u,int topf)
{
	dfn[u]=++dfstime;
	rk[dfstime]=u;
	top[u]=topf;
	if(!head[u])
		return;
	dfs2(son[u],topf);
	for(int i=head[u]; i; i=edge[i].next)
	{
		int &v=edge[i].to;
		if(top[v])
			continue;
		dfs2(v,v);
	}
}
#define times(x,y) (int)((ll)(x)*(y)%mod)
inline void add(int &x,int y)
{
	x+=y;
	if(x>=mod)
		x-=mod;
}
struct Tree
{
	int sum,ans;
	int tag;
	inline void update(int val)
	{
		add(ans,times(val,sum));
		add(tag,val);
	}
} tree[N*4];
#define lc (rt<<1)
#define rc (rt<<1|1)
inline void pushup(int rt)
{
	tree[rt].sum=(tree[lc].sum+tree[rc].sum)%mod;
	tree[rt].ans=(tree[lc].ans+tree[rc].ans)%mod;
}
inline void pushdown(int rt)
{
	if(tree[rt].tag)
	{
		tree[lc].update(tree[rt].tag);
		tree[rc].update(tree[rt].tag);
		tree[rt].tag=0;
	}
}
inline void build(int rt,int l,int r)
{
	if(l==r)
	{
		tree[rt].sum=point[rk[l]].len-point[point[rk[l]].fa].len;
		return;
	}
	int mid=(l+r)>>1;
	build(lc,l,mid);
	build(rc,mid+1,r);
	pushup(rt);
}
inline void update(int rt,int l,int r,int x,int y,int val)
{
	if(r<x||l>y)
		return;
	if(x<=l&&r<=y)
		return tree[rt].update(val);
	pushdown(rt);
	int mid=(l+r)>>1;
	update(lc,l,mid,x,y,val);
	update(rc,mid+1,r,x,y,val);
	pushup(rt);
}
inline int query(int rt,int l,int r,int x,int y)
{
	if(r<x||l>y)
		return 0;
	if(x<=l&&r<=y)
		return tree[rt].ans;
	pushdown(rt);
	int mid=(l+r)>>1;
	return (query(lc,l,mid,x,y)+query(rc,mid+1,r,x,y))%mod;
}
inline void update(int x,int val)
{
	while(top[x]!=1)
	{
		update(1,1,tot,dfn[top[x]],dfn[x],val);
		x=fa[top[x]];
	}
	update(1,1,tot,1,dfn[x],val);
}
inline int query(int x)
{
	int ans=0;
	while(top[x]!=1)
	{
		add(ans,query(1,1,tot,dfn[top[x]],dfn[x]));
		x=fa[top[x]];
	}
	add(ans,query(1,1,tot,1,dfn[x]));
	return ans;
}
int pre[N];
signed main()
{
	freopen("string.in","r",stdin);
	freopen("string.out","w",stdout);
	read(n);
	scanf("%s",str+1);
	for(int i=1; i<=n; ++i)
		id[i]=insert(str[i]-'a');
	for(int i=2; i<=tot; ++i)
		add_edge(point[i].fa,i);
//	for(int i=1; i<=tot; ++i)
//		printf("%d ",point[i].fa);
//	putchar('\n');
	dfs1(1);
	dfs2(1,1);
	build(1,1,tot);
	for(int i=1; i<=n; ++i)
	{
		pre[i]=(pre[i-1]+query(id[i]))%mod;
		update(id[i],1);
	}
	int ans=0;
	for(int i=1; i<=n; ++i)
	{
		add(ans,pre[i]);
		printf("%d\n",ans);
	}
	return 0;
}


