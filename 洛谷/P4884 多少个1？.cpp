#include <map>
#include <cmath>
#include <cstdio>
#include <algorithm>
#define re register
#define ll int
#define int __int128
using namespace std;
template <typename T>
inline void read(T &x)
{
	x=0;
	char s=(char)getchar();
	bool flag=false;
	while(s<'0'||s>'9')
	{
		if(s=='-')
			flag=true;
		s=(char)getchar();
	}
	while(s>='0'&&s<='9')
	{
		x=(x<<1)+(x<<3)+(s^'0');
		s=(char)getchar();
	}
	if(flag)
		x=~x+1;
	return;
}
inline ll quickpow(ll a,ll b,ll mod)
{
	ll res=1ll;
	while(b)
	{
		if(b&1)
			res=res*a%mod;
		a=a*a%mod;
		b>>=1;
	}
	return res;
}
map<ll,int>mp;
inline ll BSGS(ll a,ll n,ll mod)
{
	if(n==1)
		return 0ll;
	mp.clear();
	ll res=n;
	int m=(int)sqrt((long long)mod)+1;
	for(re int i=0; i<m; ++i)
	{
//		printf("%lld\n",res);
		mp[res]=i;
		res=res*a%mod;
	}
	ll x=quickpow(a,m,mod);
//	printf("%lld\n",x);
	res=1ll;
	for(re int i=1; i<=m+1; ++i)
	{
		res=res*x%mod;
//		printf("%lld\n",res);
		if(mp.count(res))
			return i*m-mp[res];
	}
	return -1;
}
signed main()
{
	ll m,k;
	read(k),read(m);
	k=(k*9+1)%m;
	printf("%lld\n",(long long)BSGS(10,k,m));
	return 0;
}
