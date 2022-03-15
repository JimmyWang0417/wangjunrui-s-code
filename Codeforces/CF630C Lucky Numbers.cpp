#include<cstdio>
int main()
{
	int n;
	scanf("%d",&n);
	long long a=2ll,sum=1ll;
	++n;
	while(n)
	{
		if(n&1)
			sum*=a;
		a*=a;
		n>>=1;
	}
	printf("%lld\n",sum-2ll);
	return 0;
}
