#include <cstdio>
#include <algorithm>
#define ll long long
#define re register
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
const int N=55;
int n,p,a[N],sum;
long long dp[N][N];
double fac[N]= {1.0},ans;
int main()
{
	read(n);
	for(re int i=1; i<=n; ++i)
	{
		read(a[i]);
		sum+=a[i];
		fac[i]=fac[i-1]*i;
	}
	read(p);
	if(sum<=p)
	{
		printf("%lf\n",(double)n);
		return 0;
	}
	dp[0][0]=1;
	for(re int i=1; i<=n; ++i)
		for(re int j=i; j>=1; --j)
			for(re int k=p; k>=a[i]; --k)
				dp[j][k]+=dp[j-1][k-a[i]];
	for(re int i=1; i<=n; ++i)
	{
		for(re int j=0; j<=p; ++j)
			printf("%lld ",dp[i][j]);
		putchar('\n');
	}
	for(re int i=1; i<=n; ++i)
		for(re int j=0; j<=p; ++j)
			ans+=(double)dp[i][j]*fac[i]*fac[n-i];
	printf("%lf\n",ans/fac[n]);
	return 0;
}
