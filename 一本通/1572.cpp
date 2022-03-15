#include<cstdio>
#include<cstring>
#include<iostream>
using namespace std;
int n,dp[1000][1000];
char s[1000000];
int main()
{
	scanf("%s",s+1);
	n=strlen(s+1);
	memset(dp,0x3f3f3f3f,sizeof(dp));
	for(register int i=1; i<=n; i++)
		dp[i][i]=1;
	for(register int i=1; i<=n; i++)
		for(register int j=i+1; j<=n; j++)
			dp[j][i]=0;
	for(register int len=2; len<=n; len++)
		for(register int i=1,j; i<=n-len+1; i++)
		{
			j=i+len-1;
			if(s[i]=='('&&s[j]==')'||s[i]=='['&&s[j]==']')
				dp[i][j]=dp[i+1][j-1];
			for(register int k=i; k<j; k++)
				dp[i][j]=min(dp[i][j],dp[i][k]+dp[k+1][j]);
		}
	printf("%d\n",dp[1][n]);
}
