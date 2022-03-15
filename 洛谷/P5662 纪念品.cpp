#include<cstdio>
#include<cstring>
#define max(x,y) ((x)>(y)?(x):(y))
#define re register
using namespace std;
const int T=1005,N=1005,M=1e6+10;
int price[T][N],dp[M];
int t,n,m;
inline int solve(int day,int nowm)
{
	memset(dp,0,sizeof(dp));
	for(re int i=1; i<=n; ++i)
		for(re int j=price[day][i]; j<=nowm; ++j)
			dp[j]=max(dp[j],dp[j-price[day][i]]+price[day+1][i]-price[day][i]);
	return dp[nowm]+nowm;
}
int main()
{
	scanf("%d%d%d",&t,&n,&m);
	for(re int i=1; i<=t; ++i)
		for(re int j=1; j<=n; ++j)
			scanf("%d",&price[i][j]);
	for(re int day=1; day<t; ++day)
		m=solve(day,m);
	printf("%d\n",m);
	return 0;
}
