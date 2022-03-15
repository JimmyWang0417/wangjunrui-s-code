#include<cstdio>
#include<algorithm>
#define re register
int n;
int main()
{
	scanf("%d",&n);
	for(re int i=n,cnt=0; i>=0; --i)
	{
		for(re int j=1; j<=i; ++j)
			printf("%02d",cnt+j);
		printf("\n");
		cnt+=i;
	}
}
