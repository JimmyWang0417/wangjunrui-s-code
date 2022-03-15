#include <cstdio>
#include <algorithm>
#define re register
using namespace std;
template <typename T>
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
const int N=20000+5,INF=1e9;

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
	int lazy,minn;
} tree[N<<2];
int dp[N],n,k;
#define lc (rt<<1)
#define rc (rt<<1|1)
inline void build(int rt,int l,int r)
{
		tree[rt].lazy=0;
	if(l==r)
	{
		tree[rt].minn=dp[l];
		return;
	}
	int mid=(l+r)>>1;
	build(lc,l,mid);
	build(rc,mid+1,r);
	tree[rt].minn=min(tree[lc].minn,tree[rc].minn);
}
inline void pushdown(int rt)
{
	if(!tree[rt].lazy)
		return;
	tree[lc].lazy+=tree[rt].lazy;
	tree[rc].lazy+=tree[rt].lazy;
	tree[lc].minn+=tree[rt].lazy;
	tree[rc].minn+=tree[rt].lazy;
	tree[rt].lazy=0;
}
inline void change(int rt,int l,int r,int x,int y,int val)
{
	if(x<=l&&r<=y)
	{
		tree[rt].minn+=val;
		tree[rt].lazy+=val;
		return;
	}
	pushdown(rt);
	int mid=(l+r)>>1;
	if(x<=mid)
		change(lc,l,mid,x,y,val);
	if(mid<y)
		change(rc,mid+1,r,x,y,val);
	tree[rt].minn=min(tree[lc].minn,tree[rc].minn);
}
inline int query(int rt,int l,int r,int x,int y)
{
	if(x<=l&&r<=y)
		return tree[rt].minn;
	pushdown(rt);
	int mid=(l+r)>>1;
	int res=INF;
	if(x<=mid)
		res=query(lc,l,mid,x,y);
	if(mid<y)
		res=min(res,query(rc,mid+1,r,x,y));
	return res;
}
int d[N],c[N],s[N],w[N],st[N],ed[N];
int main()
{
	read(n),read(k);
	for(re int i=2; i<=n; ++i)
		read(d[i]);
	for(re int i=1; i<=n; ++i)
		read(c[i]);
	for(re int i=1; i<=n; ++i)
		read(s[i]);
	for(re int i=1; i<=n; ++i)
		read(w[i]);
	++n,++k;
	d[n]=INF;
	w[n]=INF;
	for(re int i=1; i<=n; ++i)
	{
		st[i]=lower_bound(d+1,d+1+n,d[i]-s[i])-d;
		ed[i]=upper_bound(d+1,d+1+n,d[i]+s[i])-d-1;
		add_edge(ed[i],i);
	}
	int res=0;
	for(re int i=1; i<=n; ++i)
	{
		dp[i]=res+c[i];
		for(re int e=head[i]; e; e=edge[e].next)
		{
			int &v=edge[e].to;
			res+=w[v];
		}
	}
	int ans=dp[n];
	for(re int nowk=2; nowk<=k; ++nowk)
	{
		build(1,1,n);
		for(re int i=1; i<=n; ++i)
		{
			if(nowk>i)
				dp[i]=c[i];
			else
				dp[i]=c[i]+query(1,1,n,nowk-1,i-1);
			for(re int e=head[i]; e; e=edge[e].next)
			{
				int &v=edge[e].to;
				if(st[v]-1>=1)
					change(1,1,n,1,st[v]-1,w[v]);
			}
		}
		ans=min(ans,dp[n]);
	}
	printf("%d\n",ans);
	return 0;
}
