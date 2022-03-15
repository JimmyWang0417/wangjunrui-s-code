#include <cstdio>
#include <algorithm>
#define re register
#define ll long long
#define int ll
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
	int next,to,flag;
} edge[N<<1];
int head[N],num_edge;
inline void add_edge(int from,int to,int flag)
{
	edge[++num_edge].next=head[from];
	edge[num_edge].to=to;
	edge[num_edge].flag=flag;
	head[from]=num_edge;
}
struct Tree
{
	ll sum;
	int size,l,r;
} tree[N*100];
int cnt,root[N<<1];
#define lc(x) tree[x].l
#define rc(x) tree[x].r
inline void update(int pre,int &rt,int l,int r,int pos,int val)
{
	rt=++cnt;
	tree[rt]=tree[pre];
	tree[rt].size+=val;
	tree[rt].sum+=pos*val;
	if(l==r)
		return;
	int mid=(l+r)>>1;
	if(pos<=mid)
		update(lc(pre),lc(rt),l,mid,pos,val);
	else
		update(rc(pre),rc(rt),mid+1,r,pos,val);
}
inline ll query(int rt,int l,int r,int rk)
{
	if(l==r)
		return rk*l;
	int mid=(l+r)>>1;
	if(rk<=tree[lc(rt)].size)
		return query(lc(rt),l,mid,rk);
	else return tree[lc(rt)].sum+query(rc(rt),mid+1,r,rk-tree[lc(rt)].size);
}
signed main()
{
	int m,n;
	read(m),read(n);
	for(re int i=1; i<=m; ++i)
	{
		int l,r,v;
		read(l),read(r),read(v);
		add_edge(l,v,1);
		if(r<n)
			add_edge(r+1,v,-1);
	}
	for(re int i=1; i<=n; ++i)
	{
		root[i]=++cnt;
		tree[root[i]]=tree[root[i-1]];
		for(re int e=head[i]; e; e=edge[e].next)
			update(root[i],root[i],1,1e8,edge[e].to,edge[e].flag);
	}
	ll lastans=1;
	for(re int i=1; i<=n; ++i)
	{
		int x,a,b,c;
		read(x),read(a),read(b),read(c);
		int k=1+(a*lastans+b)%c;
		if(tree[root[x]].size<=k)
			printf("%lld\n",lastans=tree[root[x]].sum);
		else
			printf("%lld\n",lastans=query(root[x],1,1e8,k));
	}
	return 0;
}
