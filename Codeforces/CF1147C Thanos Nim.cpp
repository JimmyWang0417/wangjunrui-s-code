#include<cstdio>
#include<algorithm>
#define re register
using namespace std;
int a[55],n,num;
int main()
{
	scanf("%d",&n);
	for(re int i=1; i<=n; ++i)
		scanf("%d",&a[i]);
	nth_element(a+1,a+1,a+1+n);
	num=a[1];
	nth_element(a+1,a+n/2+1,a+1+n);
	if(num==a[n/2+1])
		printf("Bob\n");
	else
		printf("Alice\n");
	return 0;
}
