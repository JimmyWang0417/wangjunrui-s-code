#include<cstdio>
#define re register
using namespace std;
int prime[12]= {0,2,3,5,7,11,13,17,19,23,29};
int n;
long long s,s1;
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
inline void f(int x,long long y,int b,long long z)
{
	if(x==11)
		return;
	long long k=1ll;
	for(re int i=1; i<=b; i++)
	{
		k*=prime[x];
		if(y*k>n)
			return;
		if(z*(i+1)==s1&&y*k<s)
			s=y*k;
		if(z*(i+1)>s1)
		{
			s1=z*(i+1);
			s=y*k;
		}
		f(x+1,y*k,i,z*(i+1));
	}
	return;
}
int main()
{
	read(n);
	f(1,1ll,31,1ll);
	printf("%lld\n",s);
	return 0;
}
