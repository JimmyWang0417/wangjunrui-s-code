#include<cstdio>
#include<cmath>
#include<algorithm>
#define ll long long
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
const int N=1e5+5;
struct Tree
{
	ll sum;
	bool flag;
} tree[N<<2];
int n,m;
ll a[N];
inline void build(int rt,int l,int r)
{
	if(l==r)
	{
		tree[rt].sum=a[l];
		tree[rt].flag=(a[l]==1ll||a[l]==0ll);
		return;
	}
	int mid=(l+r)>>1;
	build(lc,l,mid);
	build(rc,mid+1,r);
	tree[rt].sum=tree[lc].sum+tree[rc].sum;
	tree[rt].flag=(tree[lc].flag&&tree[rc].flag);
}
inline void change(int rt,int l,int r,int x,int y)
{
	if(r<x||l>y||l>r||tree[rt].flag)
		return;
	if(l==r)
	{
		tree[rt].sum=(ll)sqrt(tree[rt].sum);
		tree[rt].flag=(tree[rt].sum==1ll);
		return;
	}
	int mid=(l+r)>>1;
	change(lc,l,mid,x,y);
	change(rc,mid+1,r,x,y);
	tree[rt].sum=tree[lc].sum+tree[rc].sum;
	tree[rt].flag=(tree[lc].flag&&tree[rc].flag);
}
inline ll query(int rt,int l,int r,int x,int y)
{
	if(r<x||l>y)
		return 0ll;
//	printf("%d %d %lld %lld\n",l,r,tree[rt].sum,tree[rt].max);
	if(x<=l&&r<=y)
		return tree[rt].sum;
	int mid=(l+r)>>1;
//	ll ans=0;
	return query(lc,l,mid,x,y)+query(rc,mid+1,r,x,y);
}
int main()
{
	int kase=0;
	while(scanf("%d",&n)!=EOF)
	{
		if(kase++)
			putchar('\n');
		printf("Case #%d:\n",kase);
		for(re int i=1; i<=n; ++i)
			scanf("%lld",&a[i]);
		build(1,1,n);
		scanf("%d",&m);
		while(m--)
		{
			int opt,x,y;
			scanf("%d%d%d",&opt,&x,&y);
			if(x>y)
				swap(x,y);
			if(opt==0)
				change(1,1,n,x,y);
			else
				printf("%lld\n",query(1,1,n,x,y));
//		for(re int i=1; i<=n; ++i)
//			printf("%lld ",a[i]);
//		putchar('\n');
//			for(re int i=1; i<=(n<<2); ++i)
//				printf("%lld ",tree[i].sum);
		}
	}
}
