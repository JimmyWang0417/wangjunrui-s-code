#include<cstdio>
#define re register
using namespace std;
const int N=1e5+5;
int n;
long long lcm,now,t,gcd,a,b,x,y;
inline void Exgcd(long long a,long long b,long long&d,long long&x,long long&y)
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
	while(scanf("%d",&n)==1)
	{
		bool flag=false;
		scanf("%lld%lld",&a,&b);
		now=b;
		lcm=a;
		for(re int i=1; i<n; i++)
		{
			scanf("%lld%lld",&a,&b);
			b=(b-now%a+a)%a;
			Exgcd(lcm,a,gcd,x,y);
			if(b%gcd!=0&&!flag)
			{
				printf("-1\n");
				flag=true;
			}
			now+=x*(b/gcd)%a*lcm;
			lcm=lcm/gcd*a;
			now=(now%lcm+lcm)%lcm;
		}
		if(!flag)
			printf("%lld\n",now);
	}
	return 0;
}

