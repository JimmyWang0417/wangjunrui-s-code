#include<cstdio>
#define re register
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
}
const int N=1e5+10;
int n,m,p,t;
long long fac[N];
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
#define C(n,m) (n>m?0:fac[m]*quickpow(fac[n],p-2,p)%p*quickpow(fac[m-n],p-2,p)%p)
inline long long lucas(long long n,long long m)
{
	if(!m)
		return 1ll;
	return C(n%p,m%p)*lucas(n/p,m/p)%p;
}
int main()
{
	read(t);
	while(t--)
	{
		read(n);
		read(m);
		read(p);
		fac[0]=1ll;
		for(re int i=1; i<=p; i++)
			fac[i]=fac[i-1]*i%p;
		printf("%lld\n",lucas(n,m+n));
	}

	return 0;
}

