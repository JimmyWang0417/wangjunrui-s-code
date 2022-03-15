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
		b>>=1ll;
	}
	return res%n;
}
int t;
long long a,b,c,k;
int main()
{
	read(t);
	while(t--)
	{
		read(a);
		read(b);
		read(c);
		read(k);
		if(c-b==b-a)
			printf("%lld\n",((k-1)%200907*(b-a)%200907+a)%200907);
		else
			printf("%lld\n",(a%200907*quick_pow((c/b)%200907,k-1,(long long)200907))%200907);
	}
	return 0;
}

