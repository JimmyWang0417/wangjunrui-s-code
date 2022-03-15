#include<cstdio>
#define min(x,y) ((x)<(y)?(x):(y))
#define re register
using namespace std;
int n,k;
long long c[5005][105];
int main()
{
	scanf("%d%d",&n,&k);
	for(re int i=c[0][0]=1; i<=5000; ++i)
		for(re int j=c[i][0]=1; j<=min(i,20); ++j)
			c[i][j]=c[i-1][j]+c[i-1][j-1];
	if(n==1)
	{
		for(re int i=1; i<=k; ++i)
			putchar('1');
		putchar('\n');
		return 0;
	}
	if(k==1)
	{
		putchar('1');
		for(re int i=1; i<n; ++i)
			putchar('0');
		putchar('\n');
		return 0;
	}
	int len=k;
	while(c[len+1][k]<=n)
		++len;
	--k;
	for(re int i=k; i<len; ++i)
		n-=c[i][k];
	putchar('1');
	for(re int i=len-1; i>=0; --i)
	{
		if(!k||c[i][k]>=n)
			putchar('0');
		else
		{
			n-=c[i][k];
			--k;
			putchar('1');
		}
	}
	putchar('\n');
	return 0;
}
