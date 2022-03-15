/*https://www.luogu.org/problemnew/show/P1014*/
#include<cstdio>
using namespace std;
int a,b,n,sum,num=1;
int main()
{
	scanf("%d",&n);
	while(sum+num<n)
	{
		sum+=num;
		num++;
	}
	if(num%2==0)
		for(register int i=1; i<=n-sum; i++)
		{
			a=i;
			b=num+1-i;
		}
	else
		for(register int i=1; i<=n-sum; i++)
		{
			a=num+1-i;
			b=i;
		}
	printf("%d/%d\n",a,b);
}
