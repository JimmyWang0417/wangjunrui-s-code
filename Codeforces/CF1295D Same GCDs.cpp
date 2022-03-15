#include<cstdio>
#define re register
#define ll long long
using namespace std;
template<typename T>
inline void read(T&x)
{
	x=0;
	char s=(char)getchar();
	bool flag=false;
	while(!(s>='0'&&s<='9'))
	{
		if(s=='-')
			flag=true;
		s=(char)getchar();
	}
	while(s>='0'&&s<='9')
	{
		x=(x<<1)+(x<<3)+s-'0';
		s=(char)getchar();
	}
	if(flag)
		x=(~x)+1;
	return;
}
inline ll gcd(ll a,ll b)
{
	return b==0?a:gcd(b,a%b);
}
 
inline long long Eular(long long n)
{
	long long ans=n;
	for(re int i=2; 1ll*i*i<= n; i++)
	{
		if(n%i==0)
		{
			ans-=ans/i;
			while(n%i==0)
				n/=i;
		}
	}
	if(n>1)
		ans-=ans/n;
	return ans;
}
int T;
int main()
{
	read(T);
	while(T--)
	{
		ll a,m;
		read(a),read(m);
//	printf("%d\n",gcdd);
		printf("%lld\n",Eular(m/gcd(a,m)));
	}
 
	return 0;
}

