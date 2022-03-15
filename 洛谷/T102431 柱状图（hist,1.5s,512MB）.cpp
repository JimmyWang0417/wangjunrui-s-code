#include<cstdio>
#include<algorithm>
#define re register
using namespace std;
const int N=16;
int n,a[N],tmp;
long long sum,fac[N];
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
	return;
}
int main()
{
	fac[0]=1;
	for(re int i=1; i<=14; i++)
		fac[i]=fac[i-1]*i;
	while(read(n),n)
	{
		for(re int i=1; i<=n; i++)
			read(a[i]);
		stable_sort(a+1,a+1+n);
		sum=n<<1;
		if(n&1)
		{
			tmp=n>>1;
			for(re int i=1; i<=tmp; i++)
				sum-=a[i]<<1;
			for(re int i=tmp+1; i<=n; i++)
				sum+=a[i]<<1;
			printf("%lld %lld\n",sum,fac[n>>1]*fac[n+1>>1]);
		}
		else
		{
			tmp=n>>1;
			for(re int i=1; i<tmp; i++)
				sum-=a[i]<<1;
			for(re int i=tmp+1; i<=n; i++)
				sum+=a[i]<<1;
			printf("%lld %lld\n",sum,fac[tmp]*fac[tmp]<<1);
		}
	}
	return 0;
}
