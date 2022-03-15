#include<cstdio>
#define  re register
using namespace std;
const int N=1e5+5;
int n;
double dp[N],len[N];
int main()
{
	scanf("%d",&n);
	for(re int i=1; i<=n; ++i)
	{
		static double p;
		scanf("%lf",&p);
		len[i]=(len[i-1]+1.0)*p;
		dp[i]=dp[i-1]+(2*len[i-1]+1)*p;
	}
	printf("%.15lf\n",dp[n]);
	return 0;
}
