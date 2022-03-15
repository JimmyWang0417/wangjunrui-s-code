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
long long p,n,inv[(int)3e6+10];
inline long long quickpow(long long a,long long  b,long long p)
{
	long long res=1ll;
	a%=p;
	while(b)
	{
		if(b&1)
			res=res*a%p;
		a=a*a%p;
		b>>=1;
	}
	return res%p;
}
int main()
{
	read(n);
	read(p);
	inv[1]=1;
	for(re int i=2; i<=n; ++i)
		inv[i]=(p-p/i)*inv[p%i]%p;
	for(re int i=1; i<=n; i++)
		printf("%lld\n",inv[i]);
	return 0;
}

