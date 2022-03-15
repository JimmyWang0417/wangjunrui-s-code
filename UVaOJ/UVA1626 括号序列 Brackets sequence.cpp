#include<cstdio>
#include<cstring>
#include<iostream>
#include<string>
#define re register
#define ll long long
#define match(x,y) ((x=='['&&y==']')||(x=='('&&y==')'))
#define min(x,y) ((x)<(y)?(x):(y))
using namespace std;
const int N=5010;
int dp[N][N],n;
string s;
inline void DP()
{
	for(re int i=0; i<n; ++i)
	{
		dp[i+1][i]=0;
		dp[i][i]=1;
	}
	for(re int i=n-2; i>=0; i--)
		for(re int j=i+1; j<n; ++j)
		{
			dp[i][j]=n;
			if(match(s[i],s[j]))
				dp[i][j]=min(dp[i][j],dp[i+1][j-1]);
			for(re int k=i; k<j; ++k)
				dp[i][j]=min(dp[i][j],dp[i][k]+dp[k+1][j]);
		}
	//printf("%d\n",dp[0][n-1]);
}
inline void print(int i,int j)
{
	if(i>j)
		return;
	if(i==j)
	{
		printf(s[i]=='('||s[i]==')'?"()":"[]");
		return;
	}
	int ans=dp[i][j];
	if(match(s[i],s[j])&&ans==dp[i+1][j-1])
	{
		putchar(s[i]);
		print(i+1,j-1);
		putchar(s[j]);
		return;
	}
	for(re int k=i; k<j; ++k)
		if(ans==dp[i][k]+dp[k+1][j])
		{
			print(i,k);
			print(k+1,j);
			return;
		}
}
int main()
{
	//freopen("ans.out","w",stdout);
	re int T;
	scanf("%d",&T);
	getchar();
	while(T--)
	{
		getline(cin,s);
		getline(cin,s);
		n=s.size();
		if(!n)
		{
			printf("\n\n");
			continue;
		}
		DP();
		print(0,n-1);
		putchar('\n');
		if(T)
			putchar('\n');
	}
	return 0;
}
