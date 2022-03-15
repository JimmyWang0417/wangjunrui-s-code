#include<cstdio>
using namespace std;
int c[10]= {6,2,5,5,4,5,6,3,7,6},a[2001]= {6},sum,n;
int main()
{
	scanf("%d",&n);
	for(int i=1; i<=2000; i++)
	{
		int j=i;
		while(j>=1)//求每个数所用的火柴棒
		{
			a[i]=a[i]+c[j%10];
			j=j/10;
		}
	}
	for(int i=0; i<=1000; i++)
	{
		for(int j=0; j<=1000; j++)
			if(a[i]+a[j]+a[i+j]+4==n)sum++;//还有加号与等号
	}
	printf("%d\n",sum);
}
