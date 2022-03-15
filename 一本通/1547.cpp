#include<cstdio>
using namespace std;
unsigned long long sum[1000000];
int n,m;
inline void modify(int k,int l,int r,int p,int v)
{
	if(r<p||l>p)return;
	if(l==r&&r==p)
	{
		sum[k]+=v;
		return;
	}
	int mid=(l+r)/2;
	modify(k*2,l,mid,p,v);
	modify(k*2+1,mid+1,r,p,v);
	sum[k]=sum[k*2]+sum[k*2+1];
}
inline long long change(int k,int l,int r,int a,int b)
{
	if(r<a||l>b)
		return 0;
	if(l>=a&&r<=b)
		return sum[k];
	int mid=(l+r)/2;
	return change(k*2,l,mid,a,b)+change(k*2+1,mid+1,r,a,b);
}
int main()
{
	scanf("%d%d",&n,&m);
	for(register int i=1; i<=m; i++)
	{
		int k,a,b;
		scanf("%d%d%d",&k,&a,&b);
		if(k==0)
			modify(1,1,n,a,b);
		else
			printf("%lld\n",change(1,1,n,a,b));
	}
}
