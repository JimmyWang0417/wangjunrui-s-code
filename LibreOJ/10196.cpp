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
template<typename T>
inline T quick_pow(T a,T b,T n)
{
	T res=1;
	while(b)
	{
		if(b&1)
		res=res*a%n;
		a=a*a%n;
		b>>=1;
	}
	return res%n;
}
long long m,n;
int main()
{
	read(m);
	read(n);
	printf("%lld\n",(quick_pow(m,n,100003ll)-quick_pow(m-1,n-1,100003ll)*m+100003*m)%100003);
	return 0; 
}

