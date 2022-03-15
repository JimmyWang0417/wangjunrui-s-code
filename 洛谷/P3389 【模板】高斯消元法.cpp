#include<cstdio>
#include<cmath>
#include<algorithm>
using namespace std;
#define re register
const int N=110;
double map[N][N],ans[N],eps=1e-13;
int n;
int main()
{
	scanf("%d",&n);
	for(re int i=1,x,j; i<=n; i++)
		for(re int j=1; j<=n+1; j++)
			scanf("%lf",&map[i][j]);
	for(re int i=1,r; i<=n; i++)
	{
		r=i;
		for(re int j=i+1; j<=n; j++)
			if(fabs(map[r][i])<fabs(map[j][i]))
				r=j;
		//printf("%.13lf\n",fabs(map[r][i])<eps);
		if(fabs(map[r][i])<eps)
		{
			puts("No Solution");
			return 0;
		}
		if(i!=r)
			swap(map[i],map[r]);
		double div=map[i][i];
		for(re int j=i; j<=n+1; j++)
			map[i][j]/=div;
		for(re int j=i+1; j<=n; j++)
		{
			div=map[j][i];
			for(re int k=i; k<=n+1; k++)
				map[j][k]-=map[i][k]*div;
		}
		/*for(re int i=1; i<=n; i++)
		{
			for(re int j=1; j<=n+1; j++)
				printf("%.13lf ",map[i][j]);
			putchar('\n');
		}
		putchar('\n');*/
	}
	ans[n]=map[n][n+1];
	for(re int i=n-1; i>=1; i--)
	{
		ans[i]=map[i][n+1];
		for(re int j=i+1; j<=n; j++)
			ans[i]-=(map[i][j]*ans[j]);
	}
	for(re int i=1; i<=n; i++)
		printf("%.2f\n",ans[i]);
	return 0;
}
