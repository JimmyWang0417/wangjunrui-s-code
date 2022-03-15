#include<cstdio>
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
struct Tree
{
	int size;
	ll sum,tag;
} tree[N*4];
int a[N];
#define lc (rt<<1)
#define rc (rt<<1|1)
inline void pushup(int rt)
{
	tree[rt].sum=tree[lc].sum+tree[rc].sum;
}
inline void pushdown(int rt)
{
	if(!tree[rt].tag)
		return;
	tree[lc].sum+=1ll*tree[lc].size*tree[rt].tag;
	tree[rc].sum+=1ll*tree[rc].size*tree[rt].tag;
	tree[lc].tag+=tree[rt].tag;
	tree[rc].tag+=tree[rt].tag;
	tree[rt].tag=0;
}
inline void build(int rt,int l,int r)
{
	tree[rt].size=r-l+1;
	if(l==r)
	{
		tree[rt].sum=a[l];
		return;
	}
	int mid=(l+r)>>1;
	build(lc,l,mid);
	build(rc,mid+1,r);
	pushup(rt);
}
inline void update(int rt,int l,int r,int x,int y,ll val)
{
	if(r<x||l>y)
		return;
	if(x<=l&&r<=y)
	{
		tree[rt].sum+=1ll*tree[rt].size*val;
		tree[rt].tag+=val;
		return;
	}
	pushdown(rt);
	int mid=(l+r)>>1;
	update(lc,l,mid,x,y,val);
	update(rc,mid+1,r,x,y,val);
	pushup(rt);
}
inline ll query(int rt,int l,int r,int x,int y)
{
	if(r<x||l>y)
		return 0;
	if(x<=l&&r<=y)
		return tree[rt].sum;
	pushdown(rt);
	int mid=(l+r)>>1;
	return query(lc,l,mid,x,y)+query(rc,mid+1,r,x,y);
}
int main()
{
	int n,m;
	read(n),read(m);
	for(re int i=1; i<=n; ++i)
		read(a[i]);
	for(re int i=n; i>=1; --i)
		a[i]-=a[i-1];
	build(1,1,n);
	while(m--)
	{
		int opt;
		read(opt);
		if(opt==1)
		{
			int l,r,k,d;
			read(l),read(r),read(k),read(d);
			update(1,1,n,l,l,k);
			update(1,1,n,l+1,r,d);
			if(r!=n)
				update(1,1,n,r+1,r+1,-(k+1ll*(r-l)*d));
		}
		else if(opt==2)
		{
			int pos;
			read(pos);
			printf("%lld\n",query(1,1,n,1,pos));
		}
	}
	return 0;
}
