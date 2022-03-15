#include<cstdio>
#include<cstring>
#define re register
#define min(x,y) ((x)<(y)?(x):(y))
#define abs(x) ((x)>0?(x):-(x))
using namespace std;
template<typename T>
inline void read(T&x)
{
	x=0;
	char s=getchar();
	bool f=false;
	while(!(s>='0'&&s<='9'))
	{
		if(s=='-')
			f=true;
		s=getchar();
	}
	while(s>='0'&&s<='9')
	{
		x=(x<<1)+(x<<3)+s-'0';
		s=getchar();
	}
	if(f)
		x=(~x)+1;
}
const int N=505;
int a[N],sum[N][N],n,m;
int dp[N][N];
int main()
{
	read(n);
	read(m);
	for(re int i=2; i<=n; ++i)
	{
		read(a[i]);
		a[i]+=a[i-1];
	}
	for(re int i=1; i<=n; ++i)
		for(re int j=i; j<=n; ++j)
		{
			int mid=i+j>>1;
			for(re int k=i; k<=j; ++k)
				sum[i][j]+=abs(a[mid]-a[k]);
		}
	memset(dp,0x3f3f3f3f,sizeof(dp));
	dp[0][0]=0;
	for(re int i=1; i<=n; ++i)
		for(re int j=1; j<=min(m,i); ++j)
		{
			for(re int k=j-1; k<=i-1; ++k)
				dp[i][j]=min(dp[i][j],dp[k][j-1]+sum[k+1][i]);
		}
	printf("%d\n",dp[n][m]);
	return 0;
}
