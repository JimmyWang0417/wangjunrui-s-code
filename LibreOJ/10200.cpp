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
const int N=1e6+5;
int n,m,prime[N],v[N];
inline void primes(int n)
{
	m=0;
	for(re int i=2; i<=n; i++)
	{
		if(!v[i])
		{
			v[i]=i;
			prime[++m]=i;
		}
		for(re int j=1; j<=m; j++)
		{
			if(prime[j]>n/i||prime[j]>v[i])
				break;
			v[i*prime[j]]=prime[j];
		}
	}
}
int main()
{
	primes(1e6);
	while(read(n),n)
	{
		bool flag=false;
		for(re int i=1; i<=m&&prime[i]<=n/2; i++)
			if(v[n-prime[i]]==n-prime[i])
			{
				printf("%d = %d + %d\n",n,prime[i],n-prime[i]);
				flag=true;
				break;
			}
		if(!flag)
			printf("Goldbach's conjecture is wrong.\n");
	}
	return 0;
}

