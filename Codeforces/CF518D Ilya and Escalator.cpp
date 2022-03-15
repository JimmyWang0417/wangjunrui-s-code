#include<cstdio>
#define re register
const int N=2005;
double dp[N][N];
int n,t;
double p;
int main()
{
	scanf("%d%lf%d",&n,&p,&t);
	dp[0][0]=1.0;
	for(re int i=0; i<t; ++i)
	{
		dp[i+1][n]+=dp[i][n];
		for(re int j=0; j<n; ++j)
			if(dp[i][j]>1e-10)
			{
				dp[i+1][j+1]+=dp[i][j]*p;
				dp[i+1][j]+=dp[i][j]*(1-p);
			}
	}
	double ans=0;
	for(re int i=1; i<=n; ++i)
		ans+=i*dp[t][i];
	printf("%.6lf",ans);
	return 0;
}
