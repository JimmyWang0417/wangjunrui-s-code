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
const int N=1e6+5,M=105,mod=905229641;
inline ll quickpow(ll a,ll b)
{
	ll res=1;
	while(b)
	{
		if(b&1)
			res=res*a%mod;
		a=a*a%mod;
		b>>=1;
	}
	return res;
}
ll fac[N],inv[N];
inline ll C(ll n,int m)
{
	ll res=inv[m];
	for(ll i=n-m+1; i<=n; ++i)
		res=res*(i%mod)%mod;
	return res;
}
ll n;
int m,dp[M][M*M];
signed main()
{
	freopen("totono.in","r",stdin);
	freopen("totono.out","w",stdout);
	read(n,m);
	dp[0][0]=1;
	for(int now=0; now<m; ++now)
	{
		for(int i=m; i>=1; --i)
			for(int j=m*(m-1)/2; j>=now; --j)
			{
				(dp[i][j]+=dp[i-1][j-now])%=mod;
			}
	}
//	for(int i=1; i<=m; ++i)
//	{
//		for(int j=0; j<=m*(m-1)/2; ++j)
//			printf("%d ",dp[i][j]);
//		putchar('\n');
//	}
	fac[0]=1;
	for(int i=1; i<=1e6; ++i)
		fac[i]=fac[i-1]*i%mod;
	inv[1000000]=quickpow(fac[1000000],mod-2);
	for(int i=1e6-1; i>=0; --i)
		inv[i]=inv[i+1]*(i+1)%mod;
//	for(int i=1; i<=m; ++i)
//		printf("%lld ",fac[i]*inv[i]%mod);
	int ans=0;
	for(int i=1; i<=m; ++i)
	{
		for(int j=n%m; j<=m*(m-1)/2&&j<=n; j+=m)
		{
//			printf("%d %d %d %d\n",j,(n-j)/m+i-1,i-1,C((n-j)/m+i-1,i-1));
			(ans+=C((n-j)/m+i-1,i-1)*dp[i][j]%mod*fac[i]%mod)%=mod;
		}
	}
	printf("%d\n",ans);
	return 0;
}

