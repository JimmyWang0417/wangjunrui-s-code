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
const int N=1e6+5,mod=9901;
long long b,prime[N],c[N],m,n,a,ans=1;
inline void devide(long long n)
{
	for(re int i=2; i*i<=n; i++)
		if(n%i==0)
		{
			prime[++m]=i;
			do
			{
				c[m]++;
				n/=i;
			}
			while(n%i==0);
		}
	if(n>1)
	{
		prime[++m]=n;
		c[m]=1;
	}
}
inline long long power(long long a,long long b)
{
	long long res=1;
	while(b)
	{
		if(b&1)
			res=res*a%mod;
		a=a*a%mod;
		b>>=1;
	}
	return res;
}
int main()
{
	read(a);
	read(b);
	devide(a);
	for(re int i=1; i<=m; i++)
		if((prime[i]-1)%mod==0)
			ans=(b*c[i]+1)%mod*ans%mod;
		else
			ans=ans*((power(prime[i],c[i]*b+1)+mod-1)%mod)%mod*power(prime[i]-1,mod-2)%mod;
	printf("%d\n",ans);
	return 0;
}
