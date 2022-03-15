#include<cstdio>
#include<algorithm>
#define re register
#define lc (rt<<1)
#define rc (rt<<1|1)
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
const int N=5e4+5;
struct Tree
{
	int froml,fromr,ans,sum;
} tree[N<<2];
int n,m,a[N];
inline void pushup(int rt)
{
	tree[rt].froml=max(tree[lc].froml,tree[lc].sum+tree[rc].froml);
	tree[rt].fromr=max(tree[rc].fromr,tree[lc].fromr+tree[rc].sum);
	tree[rt].ans=max(max(tree[lc].ans,tree[rc].ans),tree[lc].fromr+tree[rc].froml);
	tree[rt].sum=tree[lc].sum+tree[rc].sum;
}
inline void build(int rt,int l,int r)
{
	if(l==r)
	{
		tree[rt].froml=tree[rt].fromr=tree[rt].ans=tree[rt].sum=a[l];
		return;
	}
	int mid=(l+r)>>1;
	build(lc,l,mid);
	build(rc,mid+1,r);
	pushup(rt);
}
inline Tree query(int rt,int l,int r,int x,int y)
{
	if(x<=l&&r<=y)
		return tree[rt];
	int mid=(l+r)>>1;
	if(y<=mid)
		return query(lc,l,mid,x,y);
	if(mid<x)
		return query(rc,mid+1,r,x,y);
	Tree L=query(lc,l,mid,x,y),R=query(rc,mid+1,r,x,y),ans;
	ans.froml=max(L.froml,L.sum+R.froml);
	ans.fromr=max(R.fromr,L.fromr+R.sum);
	ans.ans=max(max(L.ans,R.ans),L.fromr+R.froml);
	ans.sum=L.sum+R.sum;
	return ans;
}
int main()
{
	read(n);
	for(re int i=1; i<=n; ++i)
		read(a[i]);
	build(1,1,n);
	read(m);
	for(re int i=1; i<=m; ++i)
	{
		int x,y;
		read(x),read(y);
		printf("%d\n",query(1,1,n,x,y).ans);
	}
	return 0;
}
