#include<cstdio>
#define re register
#define ll long long 
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
inline void swap(T&a,T&b)
{
	T c=a;
	a=b;
	b=c;
}
inline void Exgcd(ll m,ll n,ll&d,ll&x,ll&y)
{
	if(n==0)
	{
		d=m;
		x=1;
		y=0;
	}
	else
	{
		Exgcd(n,m%n,d,x,y);
		ll t=x;
		x=y;
		y=t-m/n*x;
	}
	return;
}
ll x,y,m,n,l,d,a,b;
int main()
{
	read(x);
	read(y);
	read(m);
	read(n);
	read(l);
	if(n-m<0)
	{
		swap(n,m);
		swap(x,y);
	}
	Exgcd(n-m,l,d,a,b);
	if((x-y)%d!=0)
	{
		printf("Impossible\n");
		return 0;
	}
	l/=d;
	printf("%lld\n",(a*(x-y)/d%l+l)%l);
	return 0;
}

