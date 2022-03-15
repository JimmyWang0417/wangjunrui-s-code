#include<cstdio>
#include<cstring>
#include<cmath>
#define re register
using namespace std;
const int N=5e3+10,size=26,INF=0x3f3f3f3f;
char s[2][N];
int dp[N][N],len[2],color[N][N],begin[N][size+10],end[N][size+10];
inline void initialization()
{
	memset(begin,INF,sizeof(begin));
	memset(end,-1,sizeof(end));
	for(re int i=0; i<2; i++)
	{
		for(re char j='A'; j<='Z'; j++)
		{
			for(re int k=1; k<=len[i]; k++)
				if(s[i][k]==j)
				{
					if(begin[i][j-'A']==INF)
						begin[i][j-'A']=k;
					end[i][j-'A']=k;
				}
		}
	}
	/*for(re char i=0; i<='Z'-'A'; i++)
		printf("%d %d %d %d\n",begin[0][i],end[0][i],begin[1][i],end[1][i]);*/
	return;
}
#define min(x,y) ((x)<(y)?x:y)
inline void dynamic_programming()
{
	color[0][0]=dp[0][0]=0;
	for(re int i=0; i<=len[0]; i++)
		for(re int j=0; j<=len[1]; j++)
		{
			if(i||j)
				dp[i][j]=INF;
			if(i)
			{
				dp[i][j]=min(dp[i][j],(int)(dp[i-1][j]+color[i-1][j]));
#define ch s[0][i]
				color[i][j]=color[i-1][j];
				if(i==begin[0][ch-'A']&&j<begin[1][ch-'A'])
					color[i][j]++;
				if(i==end[0][ch-'A']&&j>=end[1][ch-'A'])
					color[i][j]--;
#undef ch
			}
			if(j)
			{
				dp[i][j]=min(dp[i][j],dp[i][j-1]+color[i][j-1]);
#define ch s[1][j]
				color[i][j]=color[i][j-1];
				if(i<begin[0][ch-'A']&&j==begin[1][ch-'A'])
					color[i][j]++;
				if(i>=end[0][ch-'A']&&j==end[1][ch-'A'])
					color[i][j]--;
#undef ch
			}
		}
}
int main()
{
	re int n;
	for(scanf("%d",&n); n; n--)
	{
		scanf("%s",s[0]+1);
		scanf("%s",s[1]+1);
		len[0]=strlen(s[0]+1);
		len[1]=strlen(s[1]+1);
		initialization();
		dynamic_programming();
		printf("%d\n",dp[len[0]][len[1]]);
	}
	return 0;
}

