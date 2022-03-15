
// Problem : P3205 [HNOI2010]合唱队
// Contest : Luogu
// URL : https://www.luogu.com.cn/problem/P3205
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
const int N=1005,mod=19650827;
int n,a[N],dp[N][N][2];
signed main()
{
	read(n);
	for(re int i=1;i<=n;++i)
		read(a[i]);
	for(re int i=1;i<=n;++i)
		dp[i][i][0]=1;
	for(re int len=2;len<=n;++len)
	{
		for(re int i=1;i+len-1<=n;++i)
		{
			int j=i+len-1;
			if(a[i]<a[i+1])
				(dp[i][j][0]+=dp[i+1][j][0])%=mod;
			if(a[i]<a[j])
				(dp[i][j][0]+=dp[i+1][j][1])%=mod;
			if(a[j]>a[j-1])
				(dp[i][j][1]+=dp[i][j-1][1])%=mod;
			if(a[j]>a[i])
				(dp[i][j][1]+=dp[i][j-1][0])%=mod;
		}
	}
	printf("%d\n",(dp[1][n][0]+dp[1][n][1])%mod);
	return 0;
}

