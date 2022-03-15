#include<cstdio>
#include<algorithm>
#define re register
using namespace std;
const int INF=0x3f3f3f3f;
int ans,first,dp[20][110],nxt[20][110],n,m,a[20][110];
int main()
{
	while(scanf("%d%d",&m,&n)!=EOF)
	{
		ans=INF;
		first=0;
		for(re int i=0; i<m; i++)
			for(re int j=0; j<n; j++)
				scanf("%d",&a[i][j]);
		for(re int j=n-1; j>=0; j--)
			for(re int i=0; i<m; i++)
			{
				if(j==n-1)
					dp[i][j]=a[i][j];
				else
				{
					int rows[3]= {i,i-1,i+1};
					if(i==0)
						rows[1]=m-1;
					if(i==m-1)
						rows[2]=0;
					stable_sort(rows,rows+3);
					dp[i][j]=INF;
					for(re int k=0; k<3; k++)
					{
						int v=dp[rows[k]][j+1]+a[i][j];
						if(v<dp[i][j])
						{
							dp[i][j]=v;
							nxt[i][j]=rows[k];
						}
					}
				}
				if(j==0&&dp[i][j]<ans)
				{
					ans=dp[i][j];
					first=i;
				}
			}
		printf("%d",first+1);
		for(re int i=nxt[first][0],j=1; j<n; i=nxt[i][j],j++)
			printf(" %d",i+1);
		printf("\n%d\n",ans);
	}
	return 0;
}
