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
inline void clear(T*array,int l,int r,int val)
{
	memset(&array[l],val,sizeof(T)*(r-l+1));
}
using namespace std;
const int N=2005;
const int mod=1e9+7;
int n,a[N];
ll dp[N][N];
int b[N];
signed main()
{
	read(n);
	for(int i=1; i<=n; ++i)
	{
		read(a[i]);
		if(a[i]!=-1)
			b[a[i]]=true;
	}
	dp[0][0]=1;
	for(int i=1; i<=n; ++i)
		dp[i][0]=dp[i-1][0]*i%mod;
	for(int j=1; j<=n; ++j)
	{
		for(int i=j; i<=n; ++i)
			dp[i][j]=(dp[i][j-1]-dp[i-1][j-1])%mod;
	}
	int x=0,y=0;
	for(int i=1; i<=n; ++i)
	{
		if(a[i]==-1)
		{
			++x;
			if(!b[i])
				++y;
		}
	}
	printf("%lld\n",(dp[x][y]+mod)%mod);
	return 0;
}


