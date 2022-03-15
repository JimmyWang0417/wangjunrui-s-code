#include<cstdio>
#include<algorithm>
#include<cstring>
#define re register
using namespace std;
template<typename T>
inline void read(T&x)
{
	x=0;
	char s=getchar();
	bool f=false;
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
	if(f)
		x=(~x)+1;
}
const int N=1010;
int n,dp[N],sum[N];
struct node
{
	int v,k,c,l;
} a[N];
int main()
{
	while(read(n),n)
	{
		for(re int i=1; i<=n; i++)
		{
			read(a[i].v);
			read(a[i].k);
			read(a[i].c);
			read(a[i].l);
		}
		stable_sort(a+1,a+1+n,[](node a,node b)->bool
		{
			return a.v<b.v;
		});
		for(re int i=1; i<=n; i++)
			sum[i]=sum[i-1]+a[i].l;
		memset(dp,0x3f3f3f3f,sizeof(dp));
		dp[0]=0;
		for(re int i=1; i<=n; i++)
			for(re int j=0; j<i; j++)
				dp[i]=min(dp[i],dp[j]+(sum[i]-sum[j])*a[i].c+a[i].k);
		printf("%d\n",dp[n]);
	}
	return 0;
}

