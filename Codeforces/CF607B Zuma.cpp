
// Problem : B. Zuma
// Contest : Codeforces - Codeforces Round #336 (Div. 1)
// URL : https://codeforces.com/problemset/problem/607/B
// Memory Limit : 512 MB
// Time Limit : 2000 ms
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
const int N=505;
int dp[N][N],n,a[N];
using std::min;
signed main()
{
	read(n);
	for(re int i=1;i<=n;++i)
		read(a[i]);
	memset(dp,0x3f,sizeof(dp));
	for(re int i=1;i<=n;++i)
		dp[i][i]=1;
	for(re int i=1;i<n;++i)
		dp[i][i+1]=1+(a[i]!=a[i+1]);
	for(re int len=3;len<=n;++len)
	{
		for(re int i=1;i+len-1<=n;++i)
		{
			int j=i+len-1;
			if(a[i]==a[j])
				dp[i][j]=min(dp[i][j],dp[i+1][j-1]);
			for(re int k=i;k<j;++k)
				dp[i][j]=min(dp[i][j],dp[i][k]+dp[k+1][j]);
		}
	}
	// for(re int i=1;i<=n;++i)
	// {
		// for(re int j=i;j<=n;++j)
			// printf(" %d",dp[i][j]);
		// putchar('\n');
	// }
	printf("%d\n",dp[1][n]);
	return 0;
}

