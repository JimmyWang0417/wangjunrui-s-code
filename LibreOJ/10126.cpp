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
const int N=1e6+5;
struct node
{
	long long v,add;
} sum[N<<2];
int n,q,a[N];
inline void build(int root,int l,int r)
{
	if(l==r)
	{
		sum[root].v=a[l];
		return;
	}
	int mid=l+r>>1;
	build(root<<1,l,mid);
	build(root<<1|1,mid+1,r);
	sum[root].v=sum[root<<1].v+sum[root<<1|1].v;
}
inline void pushdown(int root,int l,int r,int mid)
{
	sum[root<<1].v+=(mid-l+1)*sum[root].add;
	sum[root<<1|1].v+=(r-mid)*sum[root].add;
	sum[root<<1].add+=sum[root].add;
	sum[root<<1|1].add+=sum[root].add;
	sum[root].add=0;
}
inline void update(int root,int l,int r,int x,int y,int v)
{
	if(r<x||l>y)
		return;
	if(l>=x&&r<=y)
	{
		sum[root].v+=(r-l+1)*(long long)v;
		sum[root].add+=v;
		return;
	}
	int mid=l+r>>1;
	pushdown(root,l,r,mid);
	update(root<<1,l,mid,x,y,v);
	update(root<<1|1,mid+1,r,x,y,v);
	sum[root].v=sum[root<<1].v+sum[root<<1|1].v;
}
inline long long query(int root,int l,int r,int x,int y)
{
	if(r<x||l>y)
		return 0;
	if(l>=x&&r<=y)
		return sum[root].v;
	int mid=l+r>>1;
	pushdown(root,l,r,mid);
	return query(root<<1,l,mid,x,y)+
	       query(root<<1|1,mid+1,r,x,y);
}
int main()
{
	n=read();
	q=read();
	for(re int i=1; i<=n; i++)
		a[i]=read();
	build(1,1,n);
	for(re int i=1,k,a,b,c;i<=q;i++)
	{
		k=read();
		if(k==1)
		{
			a=read();
			b=read();
			c=read();
			update(1,1,n,a,b,c); 
		}
		else
		{
			a=read();
			b=read();
			printf("%lld\n",query(1,1,n,a,b)); 
		}
	}
	return 0;
}

