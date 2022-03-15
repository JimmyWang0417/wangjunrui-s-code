#include<cstdio>
#include<cmath>
#define re register
#define ll long long
using namespace std;
template<typename T>
inline void read(T&x)
{
	x=0;
	char s=getchar();
	bool f=false;
	while(!(s>='0'&&s<='9'))
	{
		if(s=='-')
			f=true;
		s=getchar();
	}
	while(s>='0'&&s<='9')
	{
		x=(x<<1)+(x<<3)+s-'0';
		s=getchar();
	}
	if(f)
		x=(~x)+1;
	return;
}
namespace quick
{
	template<typename T1,typename T2,typename T3>
	inline T1 quickpow(T1 a,T2 b,T3 n)
	{
		T1 res=1;
		while(b)
		{
			if(b&1)
				res=res*a%n;
			a=a*a%n;
			b>>=1;
		}
		return res;
	}
}
namespace Exlucus
{
	inline void exgcd(ll a,ll b,ll &d,ll &x,ll &y)
	{
		if(!b)
		{
			x=1;
			y=0;
			d=a;
			return;
		}
		exgcd(b,a%b,d,y,x);
		y-=a/b*x;
		return;
	}
	inline ll fac(ll n,ll pi,ll pk)
	{
		if(!n)
			return 1;
		ll res=1;
		for(re ll i=2; i<=pk; ++i)
			if(i%pi)
				(res*=i)%=pk;
		res=quick::quickpow(res,n/pk,pk);
		for(re ll i=2; i<=n%pk; ++i)
			if(i%pi)
				(res*=i)%=pk;
		return res*fac(n/pi,pi,pk)%pk;
	}
	inline ll inv(ll n,ll mod)
	{
		ll x,y,d;
		exgcd(n,mod,d,x,y);
		return (x%mod+mod)%mod;
	}
	inline ll CRT(ll b,ll mod,ll p)
	{
		return b*inv(p/mod,mod)%p*(p/mod)%p;
	}
	inline ll C(ll n,ll m,ll pi,ll pk)
	{
		ll up=fac(n,pi,pk),d1=fac(m,pi,pk),d2=fac(n-m,pi,pk),k=0;
		for(re ll i=n; i; i/=pi)
			k+=i/pi;
		for(re ll i=m; i; i/=pi)
			k-=i/pi;
		for(re ll i=n-m; i; i/=pi)
			k-=i/pi;
		return up*inv(d1,pk)%pk*inv(d2,pk)%pk*quick::quickpow(pi,k,pk)%pk;
	}
	inline ll exlucus(ll n,ll m,ll p)
	{
		ll res=0,tmp=p,pk;
		int lim=sqrt(p)+5;
		for(re int i=2; i<=lim; i++)
			if(tmp%i==0)
			{
				pk=1;
				while(tmp%i==0)
				{
					pk*=i;
					tmp/=i;
				}
				(res+=CRT(C(n,m,i,pk),pk,p))%=p;
			}
		if(tmp>1)
			(res+=CRT(C(n,m,tmp,tmp),tmp,p))%=p;
		return res;
	}
}
int main()
{
	ll n,m,p;
	read(n);
	read(m);
	read(p);
	printf("%lld\n",Exlucus::exlucus(n,m,p));
	return 0;
}
