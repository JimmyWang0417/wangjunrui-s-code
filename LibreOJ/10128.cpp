#include<cstdio>
#include<cmath>
#define re register
using namespace std;
const int N=1e5+5;
struct node
{
	bool b;
	long long sum;
} sum[N<<2];
int n,m;long long a[N];
inline void build(int root,int l,int r)
{
	if(l==r)
	{
		sum[root].sum=a[l];
		return;
	}
	int mid=l+r>>1;
	build(root<<1,l,mid);
	build(root<<1|1,mid+1,r);
	sum[root].sum=sum[root<<1].sum+sum[root<<1|1].sum;
}
inline void update(int root,int l,int r,int x,int y)
{
	if(sum[root].b||l>y||r<x)
		return;
	if(l==r)
	{
		sum[root].sum=floor(sqrt(sum[root].sum));
		if(sum[root].sum==1||sum[root].sum==0)
			sum[root].b=true;
		return;
	}
	int mid=l+r>>1;
	update(root<<1,l,mid,x,y);
	update(root<<1|1,mid+1,r,x,y);
	sum[root].b=sum[root<<1].b&&sum[root<<1|1].b;
	sum[root].sum=sum[root<<1].sum+sum[root<<1|1].sum;
}
inline long long query(int root,int l,int r,int x,int y)
{
	if(l>y||r<x)
		return 0;
	if(l>=x&&r<=y)
		return sum[root].sum;
	int mid=l+r>>1;
	return query(root<<1,l,mid,x,y)+
	       query(root<<1|1,mid+1,r,x,y);
}
int main()
{
	scanf("%d",&n);
	for(re int i=1; i<=n; i++)
		scanf("%lld",&a[i]);
	build(1,1,n);
	scanf("%d",&m);
	for(re int i=1,k,x,y,z; i<=m; i++)
	{
		scanf("%d%d%d",&k,&x,&y);
		if(x>y)
		{
			z=x;
			x=y;
			y=z;
		}
		if(k==1)
			printf("%lld\n",query(1,1,n,x,y));
		else
			update(1,1,n,x,y);
	}
	return 0;
}

