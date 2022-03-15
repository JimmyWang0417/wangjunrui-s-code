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
const int N=2e5+5;
int n,m,a[N];
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
int size[N],son[N],fa[N],dep[N];
int first[N],last[N],eulertime;
int lis[N];
inline void dfs1(int u,int _fa)
{
	dep[u]=dep[_fa]+1;
	fa[u]=_fa;
	size[u]=1;
	lis[first[u]=++eulertime]=u;
	for(int i=head[u]; i; i=edge[i].next)
	{
		int &v=edge[i].to;
		if(v==_fa)
			continue;
		dfs1(v,u);
		size[u]+=size[v];
		if(size[v]>size[son[u]])
			son[u]=v;
	}
	lis[last[u]=++eulertime]=u;
}
int dfn[N],rk[N],dfstime;
int top[N];
inline void dfs2(int u,int topf)
{
	top[u]=topf;
	dfn[u]=++dfstime;
	rk[dfstime]=u;
//	printf("%d=%d\n",u,dfstime);
	if(!son[u])
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
struct node
{
	int lcolor,rcolor,sum;
	node(int _lc=-1,int _rc=-1,int _sum=0):lcolor(_lc),rcolor(_rc),sum(_sum) {};
	inline void operator =(const int &val)
	{
		lcolor=rcolor=val;
		sum=1;
	}
	inline node friend operator +(const node &rhsa,const node &rhsb)
	{
		return node(rhsa.lcolor!=-1?rhsa.lcolor:rhsb.lcolor,
		            rhsb.rcolor!=-1?rhsb.rcolor:rhsa.rcolor,
		            rhsa.sum+rhsb.sum-(rhsa.rcolor==rhsb.lcolor));
	}
	inline void reverse()
	{
		swap(lcolor,rcolor);
	}
};
struct Tree
{
	node val;
} tree[N*4];
#define lc (rt<<1)
#define rc (rt<<1|1)
inline void pushup(int rt)
{
	tree[rt].val=tree[lc].val+tree[rc].val;
}
inline void build(int rt,int l,int r)
{
	if(l==r)
	{
		tree[rt].val=a[rk[l]];
		return;
	}
	int mid=(l+r)>>1;
	build(lc,l,mid);
	build(rc,mid+1,r);
	pushup(rt);
}
inline void update(int rt,int l,int r,int pos,int val)
{
	if(l==r)
	{
		tree[rt].val=val;
		return;
	}
	int mid=(l+r)>>1;
	if(pos<=mid)
		update(lc,l,mid,pos,val);
	else
		update(rc,mid+1,r,pos,val);
	pushup(rt);
}
inline node query(int rt,int l,int r,int x,int y)
{
	if(r<x||l>y)
		return node();
	if(x<=l&&r<=y)
		return tree[rt].val;
	int mid=(l+r)>>1;
	return query(lc,l,mid,x,y)+query(rc,mid+1,r,x,y);
}
inline int LCA(int x,int y)
{
	while(top[x]!=top[y])
	{
		if(dep[top[x]]<dep[top[y]])
			swap(x,y);
		x=fa[top[x]];
	}
	if(dep[x]>dep[y])
		swap(x,y);
	return x;
}
inline int query(int x,int y)
{
	node ansx,ansy;
	while(top[x]!=top[y])
	{
		if(dep[top[x]]<dep[top[y]])
		{
			swap(x,y);
			swap(ansx,ansy);
		}
		ansx=query(1,1,n,dfn[top[x]],dfn[x])+ansx;
		x=fa[top[x]];
	}
	if(dep[x]>dep[y])
		swap(x,y);
	ansx.reverse();
	return (ansx+query(1,1,n,dfn[x],dfn[y])+ansy).sum;
}
int block,belong[N];
struct Change
{
	int pos,val;
} c[N];
int cm;
struct Query
{
	int l,r,lca,t,id;
	inline bool operator <(const Query &rhs)const
	{
		return belong[l]==belong[rhs.l]?(belong[r]==belong[rhs.r]?t<rhs.t:r<rhs.r):l<rhs.l;
	}
} q[N];
int qm;
int ans,answer[N];
bool vis[N];
int valcnt[N],cnt[N];
inline void add(int val)
{
	--valcnt[cnt[val]];
	++valcnt[++cnt[val]];
	ans=max(ans,cnt[val]);
}
inline void del(int val)
{
	--valcnt[cnt[val]];
	++valcnt[--cnt[val]];
	if(!valcnt[ans])
		--ans;
}
inline void update(int u)
{
	vis[u]?del(a[u]):add(a[u]);
	vis[u]^=1;
}
signed main()
{
	freopen("cw.in","r",stdin);
	freopen("cw.out","w",stdout);
	read(n,m);
	for(int i=1; i<=n; ++i)
		read(a[i]);
	for(int i=1; i<n; ++i)
	{
		int x,y;
		read(x,y);
		add_edge(x,y);
		add_edge(y,x);
	}
	dfs1(1,0);
//	for(int i=1; i<=n; ++i)
//		printf("%d ",son[i]);
//	putchar('\n');
	dfs2(1,1);
	build(1,1,n);
//	for(int i=1; i<=n; ++i)
//		printf("%d ",a[rk[i]]);
//	putchar('\n');
//	printf("%d\n",tree[1].val.sum);
	for(int i=1; i<=m; ++i)
	{
		int opt;
		read(opt);
		if(opt==1)
		{
			++cm;
			read(c[cm].pos,c[cm].val);
			update(1,1,n,dfn[c[cm].pos],c[cm].val);
		}
		else if(opt==2)
		{
			int x,y;
			read(x,y);
			answer[i-cm]=query(x,y);
		}
		else if(opt==3)
		{
			int x,y;
			read(x,y);
			if(first[x]>first[y])
				swap(x,y);
			int lca=LCA(x,y);
			++qm;
			if(x==lca)
			{
				q[qm].l=first[x];
				q[qm].r=first[y];
			}
			else
			{
				q[qm].l=last[x];
				q[qm].r=first[y];
				q[qm].lca=lca;
			}
			q[qm].t=cm;
			q[qm].id=i-cm;
		}
	}
	block=(int)pow(eulertime,2.0/3.0);
	for(int i=1; i<=eulertime; ++i)
		belong[i]=(i-1)/block+1;
	sort(q+1,q+1+qm);
	int l=1,r=0,t=0;
	for(int i=1; i<=qm; ++i)
	{
		const int ql=q[i].l,qr=q[i].r,qt=q[i].t,lca=q[i].lca;
		while(ql<l)
			update(lis[--l]);
		while(r<qr)
			update(lis[++r]);
		while(l<ql)
			update(lis[l++]);
		while(qr<r)
			update(lis[r--]);
		if(lca)
			update(lca);
		while(qt>t)
		{
			++t;
			if(vis[c[t].pos])
			{
				del(a[c[t].pos]);
				add(c[t].val);
			}
			swap(a[c[t].pos],c[t].val);
		}
		while(qt<t)
		{
			if(vis[c[t].pos])
			{
				del(a[c[t].pos]);
				add(c[t].val);
			}
			swap(a[c[t].pos],c[t].val);
			--t;
		}
		answer[q[i].id]=ans;
		if(lca)
			update(lca);
	}
	for(int i=1; i<=m-cm; ++i)
		printf("%d\n",answer[i]);
	return 0;
}


