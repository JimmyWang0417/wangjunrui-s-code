#include <bits/stdc++.h>
#define int ll
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
const int N=1e6+5;
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
int n,a[N];
int cnt[N];
ll dp[N];
ll power[N];
signed main()
{
	read(n);
	int maxx=0;
	for(int i=1; i<=n; ++i)
	{
		read(a[i]);
		++cnt[a[i]];
		maxx=max(maxx,a[i]);
	}
	power[0]=1;
	for(int i=1; i<=n; ++i)
		power[i]=power[i-1]*2%mod;
	ll ans=0;
	for(int i=maxx; i>=2; --i)
	{
		int res=cnt[i];
		for(int j=i+i; j<=maxx; j+=i)
		{
			res+=cnt[j];
			(dp[i]-=dp[j])%=mod;
		}
//		printf("%d %d\n",i,cnt[i]);
		(dp[i]+=res*power[res-1])%=mod;
		(ans+=dp[i]*i)%=mod;
	}
//	putchar('\n');
	printf("%lld\n",(ans+mod)%mod);
	return 0;
}


