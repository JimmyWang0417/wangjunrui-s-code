#include<cstdio>
int main()
{
	long long sum=1;
	int n;
	scanf("%d",&n);
	for(int i=2; i<=n; ++i)
		sum*=i;
	printf("%lld\n",sum);
}
