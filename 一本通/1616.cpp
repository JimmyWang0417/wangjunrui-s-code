#include<cstdio>
using namespace std;
inline long long quickPow(long long a,long long  b,long long n)
{
	long long res=0b1;
	while(b)
	{
		if(b%2==1)res=res*a%n;
		a=a*a%n;
		b/=2;
	}
	return res;
}
inline long long read()
{
	long long x=0;
	char s=getchar();
	while(s<'0'||s>'9')s=getchar();
	while(s>='0'&&s<='9')
	{
		x=(x<<1)+(x<<3)+s-'0';
		s=getchar();
	}
	return x;
}
int main()
{
	int a=read(),b=read(),c=read();
	printf("%d\n",quickPow(a,b,c));
}
