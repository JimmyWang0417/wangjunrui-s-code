#include<cstdio>
int n;
int main()
{
	scanf("%d",&n);
	printf("%d\n",(n&1)?0:(((n>>1)-1)>>1));
	return 0;
 } 
