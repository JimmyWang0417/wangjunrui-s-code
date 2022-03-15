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
inline T quick_pow(T a,T b,T c)
{
	T res=1;
	while(b)
	{
		if(b&1)
			res=res*a%c;
		a=a*a%c;
		b>>=1;
	}
	return res%c;
}
long long a,b,m;
int main()
{
	read(a);
	read(b);
	read(m);
	printf("%lld",quick_pow(a,b,m));
	return 0;
}

