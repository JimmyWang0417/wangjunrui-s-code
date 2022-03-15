#include<cstdio>
#include<algorithm>
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


#define re register
#define ll long long
#define lc (rt<<1)
#define rc (rt<<1|1)

const int N=1e5+5;
struct Tree
{
	ll sum,max,tagsum,tagmax;
} tree[N<<2];

inline void pushdown(int rt)
{
	tree[lc].max=max(tree[lc].max,tree[lc].sum+tree[rt].tagmax);
	tree[lc].sum+=tree[rt].tagsum;
	tree[lc].tagmax=max(tree[lc].tagmax,tree[lc].tagsum+tree[rt].tagmax);
	tree[lc].tagsum+=tree[rt].tagsum;
	tree[rc].max=max(tree[rc].max,tree[rc].sum+tree[rt].tagmax);
	tree[rc].sum+=tree[rt].tagsum;
	tree[rc].tagmax=max(tree[rc].tagmax,tree[rc].tagsum+tree[rt].tagmax);
	tree[rc].tagsum+=tree[rt].tagsum;
	tree[rt].tagmax=tree[rt].tagsum=0;
}

inline void change(int rt,int l,int r,int x,int y,int val)
{
	if(x<=l&&r<=y)
	{
		tree[rt].sum+=val;
		tree[rt].tagsum+=val;
		tree[rt].max=max(tree[rt].max,tree[rt].sum);
		tree[rt].tagmax=max(tree[rt].tagmax,tree[rt].tagsum);
		return;
	}
	int mid=(l+r)>>1;
	pushdown(rt);
	if(x<=mid)
		change(lc,l,mid,x,y,val);
	if(mid<y)
		change(rc,mid+1,r,x,y,val);
	tree[rt].sum=max(tree[lc].sum,tree[rc].sum);
	tree[rt].max=max(tree[lc].max,tree[rc].max);
	return;
}

inline ll query(int rt,int l,int r,int x,int y)
{
	if(x<=l&&r<=y)
		return tree[rt].max;
	int mid=(l+r)>>1;
	pushdown(rt);
	if(y<=mid)
		return query(lc,l,mid,x,y);
	if(mid<x)
		return query(rc,mid+1,r,x,y);
	return max(query(lc,l,mid,x,y),query(rc,mid+1,r,x,y));
}

int pos[N<<1],pre[N];
ll ans[N];

struct problem
{
	int x,y,id;
	inline bool operator < (const problem &rhs)const
	{
		return y<rhs.y;
	}
} q[N];

int n,m,a[N];
int main()
{
	read(n);
	for(re int i=1; i<=n; ++i)
	{
		read(a[i]);
		pre[i]=pos[a[i]+(int)1e5];
		pos[a[i]+(int)1e5]=i;
	}
	read(m);
	for(re int i=1; i<=m; ++i)
	{
		read(q[i].x);
		read(q[i].y);
		q[i].id=i;
	}
	stable_sort(q+1,q+1+m);
	for(re int i=1,j=1; i<=n; ++i)
	{
		change(1,1,n,pre[i]+1,i,a[i]);
		for(; j<=m&&q[j].y<=i; ++j)
			ans[q[j].id]=query(1,1,n,q[j].x,q[j].y);
	}
	for(re int i=1; i<=m; ++i)
		printf("%lld\n",ans[i]);
	return 0;
}
