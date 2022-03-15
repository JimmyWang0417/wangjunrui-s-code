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
const int N=5005;
const int mod=998244353;
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
ll fac[N],inv[N];
#define C(n,m) (fac[n]*inv[m]%mod*inv[(n)-(m)]%mod)
int n,a,b,c;
signed main()
{
	read(a,b,c);
	n=max(a,max(b,c));
	fac[0]=1;
	for(int i=1; i<=n; ++i)
		fac[i]=fac[i-1]*i%mod;
	inv[n]=quickpow(fac[n],mod-2);
	for(int i=n-1; i>=0; --i)
		inv[i]=inv[i+1]*(i+1)%mod;
	ll ans1=0,ans2=0,ans3=0;
	for(int i=0; i<=a&&i<=b; ++i)
		(ans1+=C(a,i)*C(b,i)%mod*fac[i]%mod)%=mod;
	for(int i=0; i<=b&&i<=c; ++i)
		(ans2+=C(b,i)*C(c,i)%mod*fac[i]%mod)%=mod;
	for(int i=0; i<=a&&i<=c; ++i)
		(ans3+=C(a,i)*C(c,i)%mod*fac[i]%mod)%=mod;
	printf("%lld\n",ans1*ans2%mod*ans3%mod);
	return 0;
}


