
// Problem : P1220 关路灯 
// Contest : Luogu
// URL : https://www.luogu.com.cn/problem/P1220
// Memory Limit : 125 MB
// Time Limit : 1000 ms
// Powered by CP Editor (https://github.com/cpeditor/cpeditor)

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
const int N=55;
int n,c;
int a[N],w[N];
ll sum[N],dp[N][N][2];
#define calc(l,r) (sum[n]-(sum[r]-sum[(l)-1]))
using std::min;
signed main()
{
	read(n,c);
	for(re int i=1; i<=n; ++i)
	{
		read(a[i],w[i]);
		sum[i]=sum[i-1]+w[i];
	}
	memset(dp,0x3f,sizeof(dp));
	dp[c][c][0]=dp[c][c][1]=0;
	for(re int len=2;len<=n;++len)
	{
		for(re int i=1;i+len-1<=n;++i)
		{
			int j=i+len-1;
			dp[i][j][0]=min(dp[i+1][j][0]+(a[i+1]-a[i])*calc(i+1,j),dp[i+1][j][1]+(a[j]-a[i])*calc(i+1,j));
			dp[i][j][1]=min(dp[i][j-1][0]+(a[j]-a[i])*calc(i,j-1),dp[i][j-1][1]+(a[j]-a[j-1])*calc(i,j-1));
		}
	}
	printf("%lld\n",min(dp[1][n][0],dp[1][n][1]));
	return 0;
}
