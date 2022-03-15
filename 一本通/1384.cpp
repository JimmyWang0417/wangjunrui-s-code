#include<cstdio>
using namespace std;
int a[100][100],b[100][100],n,m,x,y,sum;
int main()
{
	scanf("%d%d",&n,&m);
	for(register int i=1; i<=m; i++)
	{
		scanf("%d%d",&x,&y);
		a[x][y]=b[y][x]=true;
	}
	for(register int k=1; k<=n; k++)
		for(register int i=1; i<=n; i++)
			for(register int j=1; j<=n; j++)
			{
				a[i][j]=a[i][j]||a[i][k]&&a[k][j];
				b[i][j]=b[i][j]||b[i][k]&&b[k][j];
			}
	for(register int i=1; i<=n; i++)
	{
		int ans=0;
		for(register int j=1; j<=n; j++)
			if(a[i][j])
				ans++;
		if(ans>=(n+1)>>1)
		{
			sum++;
			continue;
		}
		ans=0;
		for(register int j=1; j<=n; j++)
			if(b[i][j])
				ans++;
		if(ans>=(n+1)>>1)
			sum++;
	}
	printf("%d\n",sum);
}
