#include<cstdio>
#include<cstring>
#include<algorithm>
#define re register
#define int long long
#define rep(i,a,b) for(re int i=a;i<=b;++i)
using namespace std;
template<typename T>
inline void read(T&x)
{
	x=0;
	char s=(char)getchar();
	bool f=false;
	while(!(s>='0'&&s<='9'))
	{
		if(s=='-')
			f=true;
		s=(char)getchar();
	}
	while(s>='0'&&s<='9')
	{
		x=(x<<1)+(x<<3)+s-'0';
		s=(char)getchar();
	}
	if(f)
		x=(~x)+1;
}
const int N = 2e3 + 10;
int n , h , l , r ;
int a[N] , dp[N][N] ;
signed main()
{
	read(n),read(h),read(l),read(r);
	int ans = 0 ;
	rep(i , 1 , n)  read(a[i]);
	memset(dp , -1 , sizeof(dp)) ;
	dp[0][0] = 0 ;
	rep(i , 1 , n)
	rep(j , 0 , h - 1)
	{
		if(dp[i - 1][j] == -1)  continue ;
		int now = (j + a[i] - 1) % h ;
		dp[i][now] = max(dp[i][now] , dp[i - 1][j] + (l <= now && now <= r)) ;
		now = (j + a[i]) % h ;
		dp[i][now] = max(dp[i][now] , dp[i - 1][j] + (l <= now && now <= r)) ;
	}
	rep(i , 0 , h - 1)  ans = max(ans , dp[n][i]) ;
	printf("%lld\n",ans);
	return 0 ;
}


