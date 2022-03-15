#include<cstdio>
#define re register
const int N=300000+5;
int n;
double dp[N],len[N];
char str[N];
int main()
{
	scanf("%d%s",&n,str+1);
	for(re int i=1; i<=n; ++i)
		if(str[i]=='o')
		{
			dp[i]=dp[i-1]+2*len[i-1]+1;
			len[i]=len[i-1]+1;
		}
		else if(str[i]=='x')
		{
			dp[i]=dp[i-1];
			len[i]=0;
		}
		else if(str[i]=='?')
		{
			dp[i]=dp[i-1]+(2*len[i-1]+1)/2.0;
			len[i]=(len[i-1]+1)/2.0;
		}
	printf("%.4lf\n",dp[n]);
	return 0;
}
