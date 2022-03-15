#include <cstdio>
#include <algorithm>
#define re register
using std::max;
template <typename T>
inline void read(T &x)
{
	x=0;
	char s=(char)getchar();
	bool flag=false;
	while(s<'0'||s>'9')
	{
		if(s=='-')
			flag=true;
		s=(char)getchar();
	}
	while(s>='0'&&s<='9')
	{
		x=(x<<1)+(x<<3)+(s^'0');
		s=(char)getchar();
	}
	if(flag)
		x=~x+1;
	return;
}
const int N=1e5+5,INF=0x7fffffff;
struct Tree
{
	int tag,add;
	bool flag;
	int nowmax,max;
} tree[N<<2];
#define lc (rt<<1)
#define rc (rt<<1|1)
int a[N],n,m;
inline void build(int rt,int l,int r)
{
	if(l==r)
	{
		tree[rt].nowmax=tree[rt].max=a[l];
		return;
	}
	int mid=(l+r)>>1;
	build(lc,l,mid);
	build(rc,mid+1,r);
	tree[rt].nowmax=max(tree[lc].nowmax,tree[rc].nowmax);
	tree[rt].max=max(tree[lc].max,tree[rc].max);
}
inline void add(int rt,int val)
{
	tree[rt].nowmax+=val;
	tree[rt].add+=val;
	tree[rt].max=max(tree[rt].max,tree[rt].nowmax);
}
inline void tag(int rt,int val)
{
	tree[rt].nowmax=tree[rt].tag=val;
	tree[rt].add=0;
	tree[rt].flag=true;
	tree[rt].max=max(tree[rt].max,tree[rt].nowmax);
}
inline void pushdown(int rt)
{
	if(tree[rt].flag)
	{
		tag(lc,tree[rt].tag);
		tag(rc,tree[rt].tag);
		tree[rt].flag=false;
	}
	if(tree[rt].add)
	{
		add(lc,tree[rt].add);
		add(rc,tree[rt].add);
		tree[rt].add=0;
	}
}
inline int query1(int rt,int l,int r,int x,int y)
{
	if(r<x||l>y)
		return ~INF;
	if(x<=l&&r<=y)
		return tree[rt].nowmax;
	pushdown(rt);
	int mid=(l+r)>>1;
	return max(query1(lc,l,mid,x,y),query1(rc,mid+1,r,x,y));
}
inline int query1(int x,int y)
{
	return query1(1,1,n,x,y);
}
inline int query2(int rt,int l,int r,int x,int y)
{
	if(r<x||l>y)
		return ~INF;
	if(x<=l&&r<=y)
		return tree[rt].max;
	pushdown(rt);
	int mid=(l+r)>>1;
	return max(query2(lc,l,mid,x,y),query2(rc,mid+1,r,x,y));
}
inline int query2(int x,int y)
{
	return query2(1,1,n,x,y);
}
inline void change1(int rt,int l,int r,int x,int y,int val)
{
	if(r<x||l>y)
		return;
	if(x<=l&&r<=y)
	{
		add(rt,val);
		return;
	}
	pushdown(rt);
	int mid=(l+r)>>1;
	change1(lc,l,mid,x,y,val);
	change1(rc,mid+1,r,x,y,val);
}
inline void change1(int x,int y,int val)
{
	change1(1,1,n,x,y,val);
}
inline void change2(int rt,int l,int r,int x,int y,int val)
{
	if(r<x||l>y)
		return;
	if(x<=l&&r<=y)
	{
		tag(rt,val);
		return;
	}
	pushdown(rt);
	int mid=(l+r)>>1;
	change2(lc,l,mid,x,y,val);
	change2(rc,mid+1,r,x,y,val);
}
inline void change2(int x,int y,int val)
{
	change2(1,1,n,x,y,val);
}
int main()
{
	read(n);
	for(re int i=1; i<=n; ++i)
		read(a[i]);
	build(1,1,n);
	read(m);
	while(m--)
	{
		char opt[4];
		scanf("%s",opt);
		if(opt[0]=='Q')
		{
			int x,y;
			read(x),read(y);
			printf("%d\n",query1(x,y));
		}
		else if(opt[0]=='A')
		{
			int x,y;
			read(x),read(y);
			printf("%d\n",query2(x,y));
		}
		else if(opt[0]=='P')
		{
			int x,y,z;
			read(x),read(y),read(z);
			change1(x,y,z);
		}
		else if(opt[0]=='C')
		{
			int x,y,z;
			read(x),read(y),read(z);
			change2(x,y,z);
		}
	}
	return 0;
}
