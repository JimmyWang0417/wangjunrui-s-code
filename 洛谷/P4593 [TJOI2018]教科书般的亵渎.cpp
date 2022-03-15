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
const int N=55;
const int mod=1e9+7;
inline ll quickpow(ll a,int b)
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
ll pre[N],suf[N],fac[N];
inline ll lagrange(ll n,int k)
{
	pre[0]=suf[k+3]=1;
	for(int i=1; i<=k+2; ++i)
		pre[i]=pre[i-1]*((n-i)%mod)%mod;
	for(int i=k+2; i>=1; --i)
		suf[i]=suf[i+1]*((n-i)%mod)%mod;
	ll now=0,ans=0;
	for(int i=1; i<=k+2; ++i)
	{
		(now+=quickpow(i,k))%=mod;
		ll a=pre[i-1]*suf[i+1]%mod,b=fac[i-1]*fac[k+2-i]%mod*((k-i)&1?-1:1);
		(ans+=now*a%mod*quickpow(b,mod-2)%mod)%=mod;
	}
	return ans;
}
int m;
ll n,a[N];
inline void work()
{
	read(n,m);
	for(int i=1; i<=m; ++i)
		read(a[i]);
	sort(a+1,a+1+m);
	ll ans=0;
	for(int i=m; i>=0; --i)
	{
		ll minus=0;
		for(int j=i+1; j<=m; ++j)
			(minus+=quickpow(a[j]-a[i],m+1))%=mod;
		(ans+=lagrange((n-a[i])%mod,m+1)-minus)%=mod;
		(minus+=quickpow(a[i]%mod,m+1))%=mod;
	}
	printf("%lld\n",(ans+mod)%mod);
}
signed main()
{
	fac[0]=1;
	for(int i=1; i<=53; ++i)
		fac[i]=fac[i-1]*i%mod;

	int T;
	read(T);
	while(T--)
		work();
	return 0;
}


