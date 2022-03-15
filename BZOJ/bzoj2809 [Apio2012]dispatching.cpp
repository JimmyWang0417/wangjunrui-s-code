#include <cstdio>
#include <algorithm>
#define re register
#define ll long long
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

const int N=1e5+5;
struct Edge
{
	int next,to;
	Edge() {}
	Edge(int ne,int t):next(ne),to(t) {}
} edge[N];
int head[N],num_edge;
inline void add_edge(int from,int to)
{
	edge[++num_edge]=Edge(head[from],to);
	head[from]=num_edge;
}

#define lc(x) tree[x].l
#define rc(x) tree[x].r
int root[N];
struct Tree
{
	int l,r;
	int size;
	int val,dist;
	ll sum;
} tree[N];
ll ans=-1ll;
inline void update(int now)
{
	tree[now].dist=tree[rc(now)].dist+1;
	tree[now].size=tree[lc(now)].size+tree[rc(now)].size+1;
	tree[now].sum=tree[lc(now)].sum+tree[rc(now)].sum+tree[now].val;
	return;
}
inline int merge(int x,int y)
{
	if(!x||!y)
		return x|y;
	if(tree[x].val<tree[y].val)
		swap(x,y);
	rc(x)=merge(rc(x),y);
	if(tree[lc(x)].dist<tree[rc(x)].dist)
		swap(lc(x),rc(x));
	update(x);
	return x;
}
int n,m,rt,l[N];
inline void dfs(int u)
{
	tree[root[u]=u].sum=tree[u].val;
	tree[u].size=1;
	for(re int i=head[u]; i; i=edge[i].next)
	{
		int &v=edge[i].to;
		dfs(v);
//		printf(" %d %d %d %lld\n",u,root[u],tree[root[u]].size,tree[root[u]].sum);
		root[u]=merge(root[u],root[v]);
	}
	while(tree[root[u]].sum>m)
		root[u]=merge(lc(root[u]),rc(root[u]));
//	printf(" %d %d %d %lld\n\n",u,root[u],tree[root[u]].size,tree[root[u]].sum);
	ans=max(ans,1ll*tree[root[u]].size*l[u]);
	return;
}

int main()
{
	tree[0].dist=-1;
	read(n),read(m);
	for(re int i=1; i<=n; ++i)
	{
		int fa;
		read(fa),read(tree[i].val),read(l[i]);
		if(!fa)
			rt=i;
		else
			add_edge(fa,i);
	}
	dfs(rt);
	printf("%lld\n",ans);
	return 0;
}
