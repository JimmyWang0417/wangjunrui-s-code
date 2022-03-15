#include<cstdio>
#define re register
using namespace std;
inline int read()
{
	char s=getchar();
	bool f=false;
	int x=0;
	while(!(s>='0'&&s<='9'))
	{
		if(s=='-')
			f=true;
		s=getchar();
	}
	while(s>='0'&&s<='9')
	{
		x=(x<<1)+(x<<3)+s-'0';
		s=getchar();
	}
	return f?-x:x;
}
const int N=1e5+5;
struct node
{
	long long sum,add,mul;
} sum[N<<2];
int n,m,a[N];
long long p;
inline void build(int root,int l,int r)
{
	sum[root].mul=1;
	if(l==r)
	{
		sum[root].sum=a[l]%p;
		return;
	}
	int mid=l+r>>1;
	build(root<<1,l,mid);
	build(root<<1|1,mid+1,r);
	sum[root].sum=(sum[root<<1].sum+sum[root<<1|1].sum)%p;
}
inline void pushdown(int root,int l,int r,int mid)
{
	sum[root<<1].sum=(sum[root<<1].sum*sum[root].mul+sum[root].add*(mid-l+1))%p;
	sum[root<<1|1].sum=(sum[root<<1|1].sum*sum[root].mul+sum[root].add*(r-mid))%p;
	sum[root<<1].mul=(sum[root<<1].mul*sum[root].mul)%p;
	sum[root<<1|1].mul=(sum[root<<1|1].mul*sum[root].mul)%p;
	sum[root<<1].add=(sum[root<<1].add*sum[root].mul+sum[root].add)%p;
	sum[root<<1|1].add=(sum[root<<1|1].add*sum[root].mul+sum[root].add)%p;
	sum[root].add=0;
	sum[root].mul=1;
}
inline void update1(int root,int l,int r,int x,int y,long long v)
{
	if(l>y||r<x)
		return;
	if(l>=x&&r<=y)
	{
		sum[root].sum=(sum[root].sum*v)%p;
		sum[root].mul=(sum[root].mul*v)%p;	
		sum[root].add=(sum[root].add*v)%p;
		return;
	}
	int mid=l+r>>1;
	pushdown(root,l,r,mid);
	update1(root<<1,l,mid,x,y,v);
	update1(root<<1|1,mid+1,r,x,y,v);
	sum[root].sum=sum[root<<1].sum+sum[root<<1|1].sum;
}
inline void update2(int root,int l,int r,int x,int y,long long v)
{
	if(l>y||r<x)
		return;
	if(l>=x&&r<=y)
	{
		sum[root].sum=(sum[root].sum+v*(long long)(r-l+1))%p;
		sum[root].add=(sum[root].add+v)%p;
		return;
	}
	int mid=l+r>>1;
	pushdown(root,l,r,mid);
	update2(root<<1,l,mid,x,y,v);
	update2(root<<1|1,mid+1,r,x,y,v);
	sum[root].sum=sum[root<<1].sum+sum[root<<1|1].sum;
}
inline long long query(int root,int l,int r,int x,int y)
{
	if(l>y||r<x)
		return 0;
	if(l>=x&&r<=y)
		return sum[root].sum;
	int mid=l+r>>1;
	pushdown(root,l,r,mid);
	return (query(root<<1,l,mid,x,y)+query(root<<1|1,mid+1,r,x,y))%p;
}
int main()
{
	n=read();
	m=read();
	p=read();
	for(re int i=1; i<=n; i++)
		a[i]=read();
	build(1,1,n);
	for(re int i=1,op,x,y,k; i<=m; i++)
	{
		op=read();
		x=read();
		y=read();
		if(op==1)
		{
			k=read();
			update1(1,1,n,x,y,k);
		}
		else if(op==2)
		{
			k=read();
			update2(1,1,n,x,y,k);
		}
		else
			printf("%lld\n",query(1,1,n,x,y));
	}
	return 0;
}

