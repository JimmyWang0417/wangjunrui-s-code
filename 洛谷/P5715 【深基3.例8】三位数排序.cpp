#include<cstdio>
#define re register
#include<algorithm>
int a[3];
int main()
{
	for(re int i=0; i<3; ++i)
		scanf("%d",&a[i]);
	std::sort(a,a+3);
	for(re int i=0; i<3; ++i)
		printf("%d ",a[i]);
	putchar('\n');
}
