#include<cstdio>
#include<algorithm>
#define re register
using namespace std;

#define lc (rt<<1)
#define rc (rt<<1|1)

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

const int N=50000+5;
struct Tree
{
	int froml,fromr,ans,sum;
} tree[N<<2];
int a[N],n,m;
inline void pushup(int rt)
{
	tree[rt].sum=tree[lc].sum+tree[rc].sum;
	tree[rt].froml=max(tree[lc].froml,tree[lc].sum+tree[rc].froml);
	tree[rt].fromr=max(tree[rc].fromr,tree[lc].fromr+tree[rc].sum);
	tree[rt].ans=max(max(tree[lc].ans,tree[rc].ans),tree[lc].fromr+tree[rc].froml);
}
inline void build(int rt,int l,int r)
{
	if(l==r)
	{
		tree[rt].sum=tree[rt].froml=tree[rt].fromr=tree[rt].ans=a[l];
		return;
	}
	int mid=(l+r)>>1;
	build(lc,l,mid);
	build(rc,mid+1,r);
	pushup(rt);
}
inline void change(int rt,int l,int r,int pos,int val)
{
	if(l==r)
	{
		tree[rt].sum=tree[rt].froml=tree[rt].fromr=tree[rt].ans=val;
		return;
	}
	int mid=(l+r)>>1;
	if(pos<=mid)
		change(lc,l,mid,pos,val);
	else
		change(rc,mid+1,r,pos,val);
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
	ans.sum=L.sum+R.sum;
	ans.froml=max(L.froml,L.sum+R.froml);
	ans.fromr=max(R.fromr,L.fromr+R.sum);
	ans.ans=max(max(L.ans,R.ans),L.fromr+R.froml);
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
		int opt,x,y;
		read(opt),read(x),read(y);
		if(opt==0)
			change(1,1,n,x,y);
		else
			printf("%d\n",query(1,1,n,x,y).ans);
	}
	return 0;
}
