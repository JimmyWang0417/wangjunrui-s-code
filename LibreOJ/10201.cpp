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
		if(v[i]==0)
		{
			v[i]=i;
			prime[++m]=i;
		}
		for(re int j=1; j<=m; j++)
		{
			if(prime[j]>v[i]||prime[j]*i>n)
				break;
			v[i*prime[j]]=prime[j];
		}
	}
	return;
}
int main()
{
	read(n);
	primes(n+1);
	//printf(" %d\n",m);
	printf("%d\n",(n>=3)+1);
	for(re int i=2; i<=n+1; i++)
		printf("%d ",(v[i]==i)?1:2);
	putchar('\n');
	return 0;
}

