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
int n,q,a[N],x,y,k;
long long sum[N<<2];
inline void build(int k,int l,int r)
{
	if(l==r)
	{
		sum[k]=a[l];
		return;
	}
	int mid=l+r>>1;
	build(k<<1,l,mid);
	build(k<<1|1,mid+1,r);
	sum[k]=sum[k<<1]+sum[k<<1|1];
}
inline void change(int k,int l,int r,int x,int v)
{
	if(r<x||l>x)
		return;
	if(l==r&&l==x)
	{
		sum[k]+=v;
		return;
	}
	int mid=l+r>>1;
	change(k<<1,l,mid,x,v);
	change(k<<1|1,mid+1,r,x,v);
	sum[k]=sum[k<<1]+sum[k<<1|1];
}
inline long long query(int k,int l,int r,int x,int y)
{
	if(l>y||r<x)
		return 0;
	if(l>=x&&r<=y)
		return sum[k];
	int mid=l+r>>1;
	return query(k<<1,l,mid,x,y)+
	       query(k<<1|1,mid+1,r,x,y);
}
int main()
{
	n=read();
	q=read();
	for(re int i=1; i<=n; i++)
		a[i]=read();
	build(1,1,n);
	for(re int i=1; i<=q; i++)
	{
		k=read();
		x=read();
		y=read();
		if(k==1)
		change(1,1,n,x,y);
		else
		printf("%lld\n",query(1,1,n,x,y)); 
	}
	return 0;
}
