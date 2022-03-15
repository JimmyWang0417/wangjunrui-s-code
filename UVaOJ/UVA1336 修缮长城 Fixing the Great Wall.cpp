#include<cstdio>
#include<cmath>
#include<algorithm>
#include<cassert>
#define re register
#define ll long long
using namespace std;
int n,v,x;
const int MAXN=1005;
const double INF=1e30;
struct node
{
	double x,c,d;
	inline bool operator < (const node &rec)const
	{
		return x<rec.x;
	}
} point[MAXN];
double dp[MAXN][MAXN][2],sum_d[MAXN],sum_c;
int vis[MAXN][MAXN][2],kase;
inline double cost(double x1,double x2,int i,int j)
{
	assert(i<=j);
	return (sum_d[n]-(i>=0&&j>=0?sum_d[j]-sum_d[i-1]:0))*fabs(x1-x2)/v;
}
inline double dfs(int i,int j,bool p)
{
	if(i==1&&j==n)
		return 0.0;
	double &ans=dp[i][j][p];
	if(vis[i][j][p]==kase)
		return ans;
	vis[i][j][p]=kase;
	ans=INF;
	double x=(p==false?point[i].x:point[j].x);
	if(i>1)
		ans=min(ans,dfs(i-1,j,0)+cost(x,point[i-1].x,i,j));
	if(j<n)
		ans=min(ans,dfs(i,j+1,1)+cost(x,point[j+1].x,i,j));
	return ans;
}
int main()
{
	while(scanf("%d%d%d",&n,&v,&x)!=EOF)
	{
		sum_c=0.0;
		++kase;
		if(n==0&&v==0&&x==0)
			return 0;
		for(re int i=1; i<=n; ++i)
		{
			scanf("%lf%lf%lf",&point[i].x,&point[i].c,&point[i].d);
			sum_c+=point[i].c;
		}
		stable_sort(point+1,point+1+n);
		sum_d[0]=0;
		for(re int i=1; i<=n; ++i)
			sum_d[i]=sum_d[i-1]+point[i].d;
		double ans=INF;
		point[0].x=-INF;
		point[n+1].x=INF;
		for(re int i=1; i<=n+1; ++i)
			if(x>point[i-1].x&&x<point[i].x)
			{
				if(i>1)
					ans=min(ans,dfs(i-1,i-1,0)+cost(x,point[i-1].x,-1,-1));
				if(i<=n)
					ans=min(ans,dfs(i,i,0)+cost(x,point[i].x,-1,-1));
			}
		printf("%.0lf\n",floor(ans+sum_c));
	}
	return 0;
}
