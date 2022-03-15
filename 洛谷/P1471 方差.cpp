#include <cmath>
#include <cstdio>
#include <iostream>
#define re register
#define ld long double
using namespace std;
const int N=1e5+5;
struct Tree
{
	int size;
	ld sum1,sum2,tag;
} tree[N*4];
ld a[N];
#define lc (rt<<1)
#define rc (rt<<1|1)
inline void pushup(int rt)
{
	tree[rt].sum1=tree[lc].sum1+tree[rc].sum1;
	tree[rt].sum2=tree[lc].sum2+tree[rc].sum2;
}
inline void pushdown(int rt)
{
	if(fabs(tree[rt].tag)<1e-18)
		return;
	tree[lc].sum2+=2.0*tree[rt].tag*tree[lc].sum1+tree[lc].size*tree[rt].tag*tree[rt].tag;
	tree[rc].sum2+=2.0*tree[rt].tag*tree[rc].sum1+tree[rc].size*tree[rt].tag*tree[rt].tag;
	tree[lc].sum1+=tree[rt].tag*tree[lc].size;
	tree[rc].sum1+=tree[rt].tag*tree[rc].size;
	tree[lc].tag+=tree[rt].tag;
	tree[rc].tag+=tree[rt].tag;
	tree[rt].tag=0.0;
}
inline void build(int rt,int l,int r)
{
	tree[rt].size=r-l+1;
	if(l==r)
	{
		tree[rt].sum1=a[l];
		tree[rt].sum2=a[l]*a[l];
		return;
	}
	int mid=(l+r)>>1;
	build(lc,l,mid);
	build(rc,mid+1,r);
	pushup(rt);
}
inline void update(int rt,int l,int r,int x,int y,ld val)
{
	if(r<x||l>y)
		return;
	if(x<=l&&r<=y)
	{
		tree[rt].sum2+=2.0*val*tree[rt].sum1+tree[rt].size*val*val;
		tree[rt].sum1+=val*tree[rt].size;
		tree[rt].tag+=val;
		return;
	}
	int mid=(l+r)>>1;
	pushdown(rt);
	update(lc,l,mid,x,y,val);
	update(rc,mid+1,r,x,y,val);
	pushup(rt);
}
inline ld query1(int rt,int l,int r,int x,int y)
{
	if(r<x||l>y)
		return 0.0;
	if(x<=l&&r<=y)
		return tree[rt].sum1;
	int mid=(l+r)>>1;
	pushdown(rt);
	return query1(lc,l,mid,x,y)+query1(rc,mid+1,r,x,y);
}
inline ld query2(int rt,int l,int r,int x,int y)
{
	if(r<x||l>y)
		return 0.0;
	if(x<=l&&r<=y)
		return tree[rt].sum2;
	int mid=(l+r)>>1;
	pushdown(rt);
	return query2(lc,l,mid,x,y)+query2(rc,mid+1,r,x,y);
}
int main()
{
	ios::sync_with_stdio(false);
	int n,m;
	cin>>n>>m;
	for(re int i=1; i<=n; ++i)
		cin>>a[i];
	build(1,1,n);
	while(m--)
	{
		int opt,x,y;
		ld val;
		cin>>opt>>x>>y;
		if(opt==1)
		{
			cin>>val;
			update(1,1,n,x,y,val);
		}
		else if(opt==2)
			printf("%.4LF\n",query1(1,1,n,x,y)/(y-x+1));
		else if(opt==3)
		{
			int len=y-x+1;
			ld ans1=query1(1,1,n,x,y)/len,ans2=query2(1,1,n,x,y)/len;
			printf("%.4LF\n",ans2-ans1*ans1);
		}
	}
	return 0;
}
