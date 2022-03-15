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
const int mod=1e9+7;
const int inv2=(mod+1)/2;
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
inline ll f(int x)
{
	if(x==0)
		return 0;
	if(x&1)
		return (11*quickpow(3,x/2)-7)%mod;
	else
		return (19*quickpow(3,x/2-1)-7)%mod;
}
inline ll g(int x)
{
	return (f(x)+f((x+1)>>1))*inv2%mod;
}
int n;
signed main()
{
	int l,r;
	read(l,r);
	printf("%lld\n",(g(r)-g(l-1)+mod)%mod);
	return 0;
}


