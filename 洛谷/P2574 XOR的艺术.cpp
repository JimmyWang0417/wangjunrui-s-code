#include <cstdio>
#define ll long long
#define re register
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
const int N=2e5+5;
struct Tree
{
	int size;
	int sum;
	bool lazy;
	inline void update()
	{
		lazy^=1;
		sum=size-sum;
	}
} tree[N*4];
int n,m;
char str[N];
#define lc (rt<<1)
#define rc (rt<<1|1)
inline void pushup(int rt)
{
	tree[rt].sum=tree[lc].sum+tree[rc].sum;
}
inline void pushdown(int rt)
{
	if(!tree[rt].lazy)
		return;
	tree[lc].update();
	tree[rc].update();
	tree[rt].lazy=false;
}
inline void build(int rt,int l,int r)
{
	tree[rt].size=r-l+1;
	if(l==r)
	{
		tree[rt].sum=(str[l]=='1');
		return;
	}
	int mid=(l+r)>>1;
	build(lc,l,mid);
	build(rc,mid+1,r);
	pushup(rt);
}
inline void update(int rt,int l,int r,int x,int y)
{
	if(r<x||l>y)
		return;
	if(x<=l&&r<=y)
	{
		tree[rt].update();
		return;
	}
	int mid=(l+r)>>1;
	pushdown(rt);
	update(lc,l,mid,x,y);
	update(rc,mid+1,r,x,y);
	pushup(rt);
}
inline int query(int rt,int l,int r,int x,int y)
{
	if(r<x||l>y)
		return 0;
	if(x<=l&&r<=y)
		return tree[rt].sum;
	int mid=(l+r)>>1;
	pushdown(rt);
	return query(lc,l,mid,x,y)+query(rc,mid+1,r,x,y);
}
int main()
{
	read(n),read(m);
	scanf("%s",str+1);
	build(1,1,n);
//	printf("%d\n",tree[1].sum);
	while(m--)
	{
		int opt,l,r;
		read(opt),read(l),read(r);
		if(opt==0)
			update(1,1,n,l,r);
		else if(opt==1)
			printf("%d\n",query(1,1,n,l,r));
	}
	return 0; 
}
