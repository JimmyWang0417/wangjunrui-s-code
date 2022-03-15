#include <cstdio>
#include <algorithm>
#define re register
#define ll long long
#define lc (root<<1)
#define rc (root<<1|1)
using namespace std;
template<typename T>
inline void read(T&x)
{
	x=0;
	char s=(char)getchar();
	bool flag=false;
	while(!(s>='0'&&s<='9'))
	{
		if(s=='-')
			flag=true;
		s=(char)getchar();
	}
	while(s>='0'&&s<='9')
	{
		x=(x<<1)+(x<<3)+s-'0';
		s=(char)getchar();
	}
	if(flag)
		x=(~x)+1;
	return;
}
const int N=2e5+5;
struct Tree
{
	ll minn,lazy;
} tree[N<<2];
ll sum[N];
inline void build(int root,int l,int r)
{
	if(l==r)
	{
		tree[root].minn=sum[l];
		tree[root].lazy=0;
		return;
	}
	int mid=(l+r)>>1;
	build(lc,l,mid);
	build(rc,mid+1,r);
	tree[root].minn=min(tree[lc].minn,tree[rc].minn);
	return;
}
inline void pushdown(int root)
{
	if(!tree[root].lazy)
		return;
	tree[lc].minn+=tree[root].lazy;
	tree[rc].minn+=tree[root].lazy;
	tree[lc].lazy+=tree[root].lazy;
	tree[rc].lazy+=tree[root].lazy;
	tree[root].lazy=0;
	return;
}
inline void change(int root,int l,int r,int x,int y,int val)
{
	if(r<x||l>y)
		return;
	if(x<=l&&r<=y)
	{
		tree[root].minn+=val;
		tree[root].lazy+=val;
		return;
	}
	int mid=(l+r)>>1;
	pushdown(root);
	change(lc,l,mid,x,y,val);
	change(rc,mid+1,r,x,y,val);
	tree[root].minn=min(tree[lc].minn,tree[rc].minn);
	return;
}
int n,p[N],a[N],pos[N];
ll ans;
int main()
{
	read(n);
	for(re int i=1; i<=n; ++i)
	{
		read(p[i]);
		pos[p[i]]=i;
	}
	for(re int i=1; i<=n; ++i)
	{
		read(a[i]);
		sum[i]=sum[i-1]+a[i];
	}
	build(1,1,n-1);
	ans=tree[1].minn;
	for(re int i=1; i<=n; ++i)
	{
		change(1,1,n-1,1,pos[i]-1,a[pos[i]]);
		change(1,1,n-1,pos[i],n-1,-a[pos[i]]);
//		printf("%d\n",ans);
		ans=min(ans,tree[1].minn);
	}
	printf("%lld\n",ans);
	return 0;
}
