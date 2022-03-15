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
const int N=205;
const int mod=998244353;
inline ll quickpow(ll a,int b)
{
	ll res=1;
	while(b)
	{
		if(b&1)
			(res*=a)%=mod;
		(a*=a)%=mod;
		b>>=1;
	}
	return res;
}
ll fac[N],inv[N];
inline ll C(int n,int m)
{
	if(n<m||m<0)
		return 0;
	return fac[n]*inv[m]%mod*inv[n-m]%mod;
}
int n,a[N],b[N];
ll dp[N][N][N];
ll g[N][N];
signed main()
{
	freopen("black.in","r",stdin);
	freopen("black.out","w",stdout);
	fac[0]=1;
	for(int i=1; i<=200; ++i)
		fac[i]=fac[i-1]*i%mod;
	inv[200]=quickpow(fac[200],mod-2);
	for(int i=200; i>=1; --i)
		inv[i-1]=inv[i]*i%mod;
//	printf("%lld\n",C(5,3));
	for(int i=0; i<=100; ++i)
		dp[0][i][i]=1;
	for(int i=0; i<100; ++i)
		for(int j=0; j<=100; ++j)
			for(int s=0; s<128; ++s)
				if(dp[i][j][s])
					for(int x=0; x+j<128; ++x)
						(dp[i+1][j+x][x+(x>=s)]+=dp[i][j][s])%=mod;
	read(n);
	for(int i=1; i<=n; ++i)
		read(a[i]);
	for(int i=1; i<=n; ++i)
		read(b[i]);
	g[0][0]=1;
	for(int i=1; i<=n; ++i)
	{
		for(int s=0; s<128; ++s)
		{
			ll p=dp[a[i]][b[i]][s]*quickpow(C(a[i]+b[i],a[i]),mod-2)%mod;
			for(int t=0; t<128; ++t)
				(g[i][s^t]+=p*g[i-1][t]%mod)%=mod;
		}
	}
	printf("%lld\n",(1-g[n][0]+mod)%mod);
	return 0;
}


