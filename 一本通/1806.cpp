#include<cstdio>
#include<cctype>
#include<cmath>
#include<map>
#define re register
#define ll long long
using namespace std;
namespace IO
{
	const int SIZE=1<<25;
	char ibuf[SIZE],*iS,*iT;
#define gc() (iS==iT?(iT=(iS=ibuf)+fread(ibuf,1,SIZE,stdin),iS==iT?EOF:*iS++):*iS++)
	template<typename T>
	inline void read(T & x)
	{
		x=0;
		bool b=false;
		char ch=gc();
		while(!isdigit(ch)&&ch^'-')
			ch=gc();
		if(ch=='-')
		{
			b=true;
			ch=gc();
		}
		while(isdigit(ch))
		{
			x=(x<<1)+(x<<3)+(ch^'0');
			ch=gc();
		}
		if(b)
			x=~x+1;
		return;
	}
#undef gc
	char Out[1<<30],*fe=Out,ch[25];
	int num=0;
	template<typename T>
	inline void write(T x)
	{
		if(!x)
			*fe++='0';
		if(x<0)
		{
			*fe++='-';
			x=-x;
		}
		while(x)
		{
			ch[++num]=x%10+'0';
			x/=10;
		}
		while(num)
			*fe++=ch[num--];
		*fe++='\n';
	}
	inline void write_str(char *s)
	{
		for(re int i=0; s[i]; i++)
			*fe++=s[i];
		*fe++='\n';
	}
	inline void flush()
	{
		fwrite(Out,1,fe-Out,stdout);
		fe=Out;
	}
}
using namespace IO;
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
			d=a;
			x=1;
			y=0;
			return;
		}
		exgcd(b,a%b,d,y,x);
		y-=a/b*x;
		return;
	}
	inline ll fac(ll n,ll pi,ll pk)
	{
		if(!n)
			return 1ll;
		ll res=1ll;
		for(re int i=2; i<=pk; ++i)
			if(i%pi)
				res=res*i%pk;
		res=quick::quickpow(res,n/pk,pk);
		for(re int i=2; i<=n%pk; ++i)
			if(i%pi)
				res=res*i%pk;
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
		for(re int i=2; i<=lim; ++i)
			if(tmp%i==0)
			{
				pk=1;
				while(tmp%i==0)
				{
					pk*=i;
					tmp/=i;
				}
				res=(res+CRT(C(n,m,i,pk),pk,p))%p;
			}
		if(tmp>1)
			res=(res+CRT(C(n,m,tmp,tmp),tmp,p))%p;
		return res;
	}
}
namespace ExBSGS
{
#define mul(a,b,p) (1ll*a*b%p)
	template<typename T>
	inline T gcd(T a,T b)
	{
		return b?gcd(b,a%b):a;
	}
	map<ll,ll>Hash;
	inline ll exBSGS(ll a,ll b,ll p)
	{
		a%=p;
		b%=p;
		if(b==1)
			return 0;
		if(!b&&!a)
			return 1;
		if(!a)
			return -1;
		if(!b)
		{
			ll res=0,d;
			while((d=gcd(a,p))!=1)
			{
				++res;
				p/=d;
				if(p==1)
					return res;
			}
			return -1;
		}
		ll res=0,A=a,B=b,P=p,C=1,d;
		while((d=gcd(A,P))!=1)
		{
			if(B%d)
				return -1;
			P/=d;
			B/=d;
			C=mul(C,A/d,P);
			++res;
			if(C==B)
				return res;
		}
		Hash.clear();
		ll f=1,t=sqrt(P)+1;
		for(re int i=0; i<t; ++i)
		{
			Hash[mul(f,B,P)]=i;
			f=mul(f,A,P);
		}
		int tf=f;
		f=mul(f,C,P);
		for(re int i=1; i<=t; ++i)
		{
			if(Hash.find(f)!=Hash.end())
				return res+i*t-Hash[f];
			f=mul(f,tf,P);
		}
		return -1;
	}
#undef mul
}
using namespace Exlucus;
using namespace quick;
using namespace ExBSGS;
int main()
{
	re ll y,z,p,T;
	int type;
	for(read(T); T; T--)
	{
		IO::read(type);
		IO::read(y);
		IO::read(z);
		IO::read(p);
		if(type==1)
			IO::write(quick::quickpow(y,z,p));
		else if(type==3)
			IO::write(Exlucus::exlucus(z,y,p));
		else if(type==2)
		{
			ll ans=ExBSGS::exBSGS(y,z,p);
			if(~ans)
				IO::write(ans);
			else
				IO::write_str("Math Error");
		}
	}
	IO::flush();
	return 0;
}
