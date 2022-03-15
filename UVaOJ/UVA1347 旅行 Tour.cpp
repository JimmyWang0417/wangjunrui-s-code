#include<cstdio>
#include<cmath>
#include<cstring>
#define re register
using namespace std;
const int N=1010;
double dp[N][N];
int n;
bool vis[N][N];
struct node
{
	int x,y;
} a[N];
inline double dist(int x,int y)
{
	return sqrt((a[x].x-a[y].x)*(a[x].x-a[y].x)+(a[x].y-a[y].y)*(a[x].y-a[y].y));
}
#define min(x,y) (x>y?y:x)
#define max(x,y) (x>y?x:y)
inline double DP(int x,int y)
{
	int maxx=max(x,y),minn=min(x,y);
	double&ans=dp[maxx][minn];
	if(vis[maxx][minn])
		return dp[maxx][minn];
	vis[maxx][minn]=true;
	ans=min(DP(maxx+1,minn)+dist(maxx,maxx+1),DP(maxx,maxx+1)+dist(minn,maxx+1));
	return ans;
}
int main()
{
	while(scanf("%d",&n)!=EOF)
	{
		for(re int i=1; i<=n; i++)
			scanf("%d%d",&a[i].x,&a[i].y);
		for(re int i=1; i<n; i++)
		{
			dp[n-1][i]=dist(n-1,n)+dist(i,n);
			vis[n-1][i]=true;
		}
		printf("%.2f\n",DP(1,1));
		memset(vis,false,sizeof(vis));
	}
}

