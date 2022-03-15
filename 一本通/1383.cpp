#include<cstdio>
using namespace std;
bool f[1000][1000];
int a[1000],n,m,sum;
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&m);
		while(m)
		{
			f[i][m]=1;
			scanf("%d",&m);
		}
	}
	for(int k=1;k<=n;k++)
	  for(int i=1;i<=n;i++)
	    for(int j=1;j<=n;j++)
	      f[i][j]=f[i][j]||f[i][k]&&f[k][j];
	for(int i=1;i<=n;i++)
	  for(int j=1;j<=n;j++)
	    if(f[i][j])
	      a[j]=i;
	for(int i=1;i<=n;i++)
	  if(a[i]==0)
	    sum++;
	printf("%d\n",sum);
}
