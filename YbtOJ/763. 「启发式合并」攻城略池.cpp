#include <bits/stdc++.h>
#define lowbit(x) ((x)&(-(x)))
#define re register
#define ll long long
#define ull unsigned long long
#define rep(i,a,b) for(re int i=a;i<=b;++i)
#define per(i,a,b) for(re int i=a;i>=b;--i)
#define int ll
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
const int N=1e6+5;
int n;
int d[N];
struct Edge
{
	int next,to,dis;
} edge[N];
int head[N],num_edge;
inline void add_edge(int from,int to,int dis)
{
	edge[++num_edge].next=head[from];
	edge[num_edge].to=to;
	edge[num_edge].dis=dis;
	head[from]=num_edge;
}
struct Tree
{
	int l,r;
	int size;
	int sum;
} tree[N*40];
const int INF=0x3f3f3f3f;
int cnt,root[N];
#define lc(x) tree[x].l
#define rc(x) tree[x].r
inline void update(int &rt,int l,int r,int pos,int val)
{
	if(!rt)
		rt=++cnt;
	tree[rt].sum+=pos;
	tree[rt].size+=val;
	if(l==r)
		return;
	int mid=(l+r)>>1;
	if(pos<=mid)
		update(lc(rt),l,mid,pos,val);
	else
		update(rc(rt),mid+1,r,pos,val);
}
inline int merge(int x,int y)
{
	if(!x||!y)
		return x|y;
	tree[x].size+=tree[y].size;
	tree[x].sum+=tree[y].sum;
	lc(x)=merge(lc(x),lc(y));
	rc(x)=merge(rc(x),rc(y));
	return x;
}
inline int query(int rt,int l,int r,int D,int k,int b)
{
	if(l==r)
		return l;
	int mid=(l+r)>>1;
	if((tree[lc(rt)].size+k)*mid-b-tree[lc(rt)].sum>=D)
		return query(lc(rt),l,mid,D,k,b);
	else
		return query(rc(rt),mid+1,r,D,k+tree[lc(rt)].size,b+tree[lc(rt)].sum);
}
inline int query(int rt,int D,int dis)
{
	return query(rt,0,INF,D,0,0)-dis;
}
inline void update(int &rt,int k,int b)
{
	update(rt,0,INF,b,k);
}
int ans;
int dis[N];
inline void dfs(int u,int fa)
{
	for(int i=head[u]; i; i=edge[i].next)
	{
		int &v=edge[i].to;
		if(v==fa)
			continue;
		dis[v]=dis[u]+edge[i].dis;
		dfs(v,u);
		root[u]=merge(root[u],root[v]);
	}
	int tim=0;
	if(d[u])
		tim=query(root[u],d[u],dis[u]);
	ans=max(ans,tim);
	update(root[u],1,tim+dis[u]);
}
signed main()
{
	freopen("conquer.in","r",stdin);
	freopen("conquer.out","w",stdout);
	read(n);
	for(int i=1; i<=n; ++i)
		read(d[i]);
	for(int i=1; i<n; ++i)
	{
		int u,v,w;
		read(u,v,w);
		add_edge(u,v,w);
		add_edge(v,u,w);
	}
	dfs(1,0);
	printf("%lld\n",ans);
	return 0;
}

