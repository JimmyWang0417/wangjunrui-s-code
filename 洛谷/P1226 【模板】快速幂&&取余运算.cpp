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
inline long long quick_pow(long long a,long long b,long long n)
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
long long b,p,k;
int main()
{
	read(b);
	read(p);
	read(k);
	printf("%lld^%lld mod %lld=%lld",b,p,k,quick_pow(b,p,k));
	return 0;
}

