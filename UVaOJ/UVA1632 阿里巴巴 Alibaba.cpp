#include <bits/stdc++.h>
#define lowbit(x) ((x)&(-(x)))
#define re register
#define ll long long
#define ull unsigned long long
#define rep(i,a,b) for(re int i=a;i<=b;++i)
#define per(i,a,b) for(re int i=a;i>=b;--i)
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
template<typename T,typename ...T1>
inline void read(T&x,T1&...x1)
{
	read(x);
	read(x1...);
}
template<typename T>
inline void clear(T*a,int l,int r,int val)
{
	memset(&a[l],val,sizeof(T)*(r-l+1));
}
const int N=10005,INF=0x3f3f3f3f;
int dp[N][N][2];
int a[N],t[N],n;
using std::min;
signed main()
{
	while(scanf("%d",&n)!=EOF)
	{
		for(re int i=1; i<=n; ++i)
			read(a[i],t[i]);
		for(re int len=2; len<=n; ++len)
			for(re int i=1; i+len-1<=n; ++i)
			{
				int j=i+len-1;
				dp[i][j][0]=min(dp[i+1][j][0]+a[i+1]-a[i],dp[i+1][j][1]+a[j]-a[i]);
				if(dp[i][j][0]>=t[i])
					dp[i][j][0]=INF;
				dp[i][j][1]=min(dp[i][j-1][0]+a[j]-a[i],dp[i][j-1][1]+a[j]-a[j-1]);
				if(dp[i][j][1]>=t[j])
					dp[i][j][1]=INF;
			}
		int ans=min(dp[1][n][0],dp[1][n][1]);
		if(ans==INF)
			printf("No solution\n");
		else
			printf("%d\n",ans);
	}
	return 0;
}


