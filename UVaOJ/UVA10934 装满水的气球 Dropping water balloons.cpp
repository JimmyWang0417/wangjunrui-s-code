#include<cstdio>
#define re register
using namespace std;
long long dp[105][70],n;
int k;
inline void solve()
{
	for(re int i=1; i<=63; ++i)
		if(dp[k][i]>=n)
		{
			printf("%d\n",i);
			return;
		}
	printf("More than 63 trials needed.\n");
	return;
}
int main()
{
	for(re int i=1; i<=100; ++i)
		for(re int j=1; j<=63; ++j)
			dp[i][j]=dp[i-1][j-1]+1+dp[i][j-1];
	while(scanf("%d%lld",&k,&n)!=EOF&&k&&n)
		solve();
	return 0;
}
