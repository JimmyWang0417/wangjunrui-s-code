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
int T;
ll n,t,d,x,y,a,b,gcd;
inline void Exgcd(ll a,ll b,ll&d,ll&x,ll&y)
{
	if(b==0)
	{
		x=1;
		y=0;
		d=a;
	}
	else
	{
		Exgcd(b,a%b,d,x,y);
		t=x;
		x=y;
		y=t-a/b*y;
	}
	return;
}
int main()
{
	read(T);
	for(re int i=1;i<=T;i++)
	{
		read(n);
		read(d);
		read(x);
		read(y);
		Exgcd(d,n,gcd,a,b);
		if(((y-x+n)%n)%gcd!=0)
		{
			printf("Impossible\n");
			continue;
		}
		ll k=((y-x+n)%n)/gcd;
		printf("%lld\n",(a*k%(n/gcd)+(n/gcd))%(n/gcd));
	}
	return 0;
}
