#include<cstdio>
#include<climits>
#include<cstring>
#include<algorithm>
#define re register
#define calc(x1,y1,x2,y2) (sum[x2][y2]-sum[x1-1][y2]-sum[x2][y1-1]+sum[x1-1][y1-1])
using namespace std;
const int INF=(INT_MAX>>1);
const int N=25;
int kase,n,m,k,sum[N][N],dp[N][N][N][N],vis[N][N][N][N];
int mp[N][N];
inline int DP(int x1,int y1,int x2,int y2)
{
	int val=calc(x1,y1,x2,y2);
	if(val==1)
		return 0;
	if(val==0)
		return INF;
	if(vis[x1][y1][x2][y2]==kase)
		return dp[x1][y1][x2][y2];
	int &ans=dp[x1][y1][x2][y2];
	vis[x1][y1][x2][y2]=kase;
	ans=INF;
	for(re int i=x1; i<x2; ++i)
		ans=min(ans,DP(x1,y1,i,y2)+DP(i+1,y1,x2,y2)+y2-y1+1);
	for(re int i=y1; i<y2; ++i)
		ans=min(ans,DP(x1,y1,x2,i)+DP(x1,i+1,x2,y2)+x2-x1+1);
	return ans;
}
int main()
{
	freopen("ans.in","r",stdin);
	freopen("ans.out","w",stdout);
	while(scanf("%d%d%d",&n,&m,&k)!=EOF)
	{
		memset(mp,0,sizeof(mp));
		for(re int i=1; i<=k; ++i)
		{
			int x,y;
			scanf("%d%d",&x,&y);
			++mp[x][y];
		}
		for(re int i=1; i<=n; ++i)
			for(re int j=1; j<=m; ++j)
				sum[i][j]=sum[i][j-1]+sum[i-1][j]-sum[i-1][j-1]+mp[i][j];
		++kase;
		printf("Case %d: %d\n",kase,DP(1,1,n,m));
	}
}
