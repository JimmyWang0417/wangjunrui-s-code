#include<cstdio>
#include<cmath>
#include<cstring>
#define re register
using namespace std;
const int N=2e6+5;
int v[N],prime[N],l,r,x1,x2,t1,t2,b[N],n,m;
inline void primes(int n,int&m)
{
	m=0;
	for(re int i=2; i<=n; i++)
	{
		if(!v[i])
		{
			v[i]=i;
			prime[++m]=i;
		}
		for(re int j=1; j<=m&&prime[j]<=v[i]&&prime[j]<=n/i; j++)
			v[i*prime[j]]=prime[j];
	}
	return;
}
inline int max(int a,int b)
{
	return a>b?a:b;
}
bool vis[N];
int main()
{
	primes(46341,n);
	while(scanf("%d%d",&l,&r)==2)
	{
		memset(vis,true,sizeof(vis));
		if(l==1)
			vis[0]=0;
		for(re int i=1; i<=n; i++)
		{
			for(re int j=l/prime[i]; j<=r/prime[i]; j++)
				if(j>1&&j>=l/(double)prime[i])
					vis[prime[i]*j-l]=0;
		}
		m=0;
		for(re int i=0; i<=r-l; i++)
			if(vis[i])
				b[++m]=i+l;
		t1=0x7fffffff;
		t2=0;
		for(re int i=1,j; i<m; i++)
		{
			j=b[i+1]-b[i];
			if(j<t1)
			{
				t1=j;
				x1=i;
			}
			if(j>t2)
			{
				t2=j;
				x2=i;
			}
		}
		if(!t2)
			printf("There are no adjacent primes.\n");
		else
			printf("%d,%d are closest, %d,%d are most distant.\n",b[x1],b[x1+1],b[x2],b[x2+1]);
	}
	return 0;
}
