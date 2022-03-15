#include<cstdio>
#define re register
const int N=200+5;
int n,m;
double dp[N][2],p[N];//当dp[i][0]表示首尾不同，dp[i][1]表示首尾相同
int main()
{
	scanf("%d%d",&n,&m);
	p[1]=1;
	for(re int i=2; i<=n+1; ++i)
		p[i]=p[i-1]/m;
	dp[0][1]=1.0;
	for(re int i=1; i<=n; ++i)
		for(re int j=0; j<i; ++j)
		{
			dp[i][1]+=(i-j)*p[i-j]*dp[j][0]*1/m;
			dp[i][0]+=(i-j)*p[i-j]*(dp[j][0]*(m-2)/m+dp[j][1]*(m-1)/m);
		}
	/*for(re int i=0; i<=n; ++i)
	{
		for(re int j=0; j<=i; ++j)
			printf("%lf ",dp[i][j]);
		putchar('\n');
	}*/

	double ans=p[n]*n;
	for(re int i=0; i<n; ++i)
		ans+=i*i*dp[n-i][0]*p[i];
	printf("%.5lf\n",ans);
}
