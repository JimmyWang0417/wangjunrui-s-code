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
const int N=1005,MAX=20000,mod=998244353;
int dp[N][MAX*2+4],n,a[N],ans;
#define calc(x) ((x)+MAX)
signed main()
{
	read(n);
	for(re int i=1; i<=n; ++i)
		read(a[i]);
	for(re int i=2; i<=n; ++i)
		for(re int j=1; j<i; ++j)
		{
			dp[i][calc(a[i]-a[j])]+=dp[j][calc(a[i]-a[j])]+1;
			dp[i][calc(a[i]-a[j])]%=mod;
			
			ans+=dp[j][calc(a[i]-a[j])]+1;
			ans%=mod;
		}
	printf("%d\n",ans+n);
	return 0;
}


