#include<cstdio>
#include<cctype>
#include<algorithm>
#include<cstring>
#define re register
using namespace std;
template <typename T>
inline void read(T& x)
{
	x = 0;
	char s = getchar();
	bool f = false;
	while (!(s >= '0' && s <= '9'))
	{
		if (s == '-')
			f = true;
		s = getchar();
	}
	while (s >= '0' && s <= '9')
	{
		x = (x << 1) + (x << 3) + s - '0';
		s = getchar();
	}
	if (f)
		x = (~x) + 1;
}
const int N=1010,INF=0x3f3f3f3f;
int l,n,a[N],dp[101][101];
int main()
{
	while(read(l),l)
	{
		read(n);
		memset(dp,INF,sizeof(dp));
		for(re int i=1; i<=n; i++)
		{
			read(a[i]);
			dp[i][i+1]=0;
		}
		a[++n]=l;
		dp[0][1]=0;
#define j (i+len)
		for(re int len=2; len<=n; len++)
			for(re int i=0; i+len<=n; i++)
			{
				for(re int k=i+1; k<j; k++)
					dp[i][j]=min(dp[i][j],dp[i][k]+dp[k][j]+a[j]-a[i]);
			}
#undef j
		printf("The minimum cutting is %d.\n",dp[0][n]);
	}
	return 0;
}

