#include<cstdio>
#include<cctype>
#define re register
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
	char Out[1<<10],*fe=Out,ch[25];
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
const long long N=10000100,mod=10000019;
long long n,k,t;
bool op;
long long fac[N],inv[N];
inline long long quickpow(long long a,long long b,long long n)
{
	long long res=1;
	while(b)
	{
		if(b&1)
			res=res*a%n;
		a=a*a%n;
		b>>=1;
	}
	return res%n;
}
inline long long Lucas
(long long m,long long n)
{
	if ( m<n ) return 0;
	else if ( m>=mod || n>=mod ) return Lucas(m/mod,n/mod)*Lucas(m%mod,n%mod)%mod;
	else return fac[m]*inv[n]%mod*inv[m-n]%mod;
}
using namespace IO;
int main()
{
	read(op);
	read(n);
	read(k);
	inv[0]=inv[1]=fac[0]=fac[1]=1;
	for(re int i=2; i<mod; i++)
	{
		fac[i]=fac[i-1]*i%mod;
		inv[i]=(mod-mod/i)*inv[mod%i]%mod;
	}
	for(re int i=2; i<mod; i++)
		inv[i]=inv[i]*inv[i-1]%mod;
	printf("%lld\n",Lucas(n+k-1,n));
	return 0;
}

