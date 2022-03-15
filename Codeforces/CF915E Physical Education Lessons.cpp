#include <cstdio>
#include <algorithm>
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
const int N=3e5+5;
struct Tree
{
	int l,r;
	int sum;
	int tag;
	inline void change(int val,int _l,int _r)
	{
		tag=val;
		sum=(_r-_l+1)*val;
	}
} tree[N*50];
#define lc(x) tree[x].l
#define rc(x) tree[x].r
int cnt,root;
inline void pushdown(int rt,int l,int mid,int r)
{
	if(tree[rt].tag!=-1)
	{
		if(!lc(rt))
			lc(rt)=++cnt;
		if(!rc(rt))
			rc(rt)=++cnt;
		tree[lc(rt)].change(tree[rt].tag,l,mid);
		tree[rc(rt)].change(tree[rt].tag,mid+1,r);
		tree[rt].tag=-1;
	}
}
inline void pushup(int rt)
{
	tree[rt].sum=tree[lc(rt)].sum+tree[rc(rt)].sum;
}
inline void update(int &rt,int l,int r,int x,int y,int val)
{
	if(r<x||l>y)
		return;
	if(!rt)
		rt=++cnt;
	if(x<=l&&r<=y)
	{
		tree[rt].change(val,l,r);
		return;
	}
	int mid=(l+r)>>1;
	pushdown(rt,l,mid,r);
	update(lc(rt),l,mid,x,y,val);
	update(rc(rt),mid+1,r,x,y,val);
	pushup(rt);
}
int n,q;
int main()
{
	read(n),read(q);
	update(root,1,n,1,n,1);
	while(q--)
	{
		int l,r,opt;
		read(l),read(r),read(opt);
		if(opt==1)
			update(root,1,n,l,r,0);
		else if(opt==2)
			update(root,1,n,l,r,1);
		printf("%d\n",tree[root].sum);
	}
	return 0;
}
