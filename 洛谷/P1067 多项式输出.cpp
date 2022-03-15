/*https://www.luogu.org/problemnew/show/P1067*/
#include<cstdio>
using namespace std;
bool f;
int a[100],n;
int main()
{
	scanf("%d",&n);
	for(register int i=0; i<n; i++)
		scanf("%d",&a[i]);
	for(register int i=0; i<n-1; i++)
	{
		if(a[i]==0)continue;
		if(a[i]==-1)
		{
			putchar('-');
			f=true;
		}
		else if(a[i]==1)
		{
			if(f)putchar('+');
			else f=true;
			printf("x^%d",n-i);
			continue;
		}
		else if(a[i]<0)
		{
			f=true;
			printf("%d",a[i]);
		}
		else
		{
			if(!f)
			{
				printf("%d",a[i]);
				f=true;
			}
			else
				printf("+%d",a[i]);
		}
		printf("x^%d",n-i);
	}
	n=n-1;
	if(a[n]!=0)
	{
		if(a[n]==1)
		{
			if(f)putchar('+');
			else f=true;
			putchar('x');
		}
		else if(a[n]==-1)
			printf("-x");
		else if(a[n]<0)
			printf("%dx",a[n]);
		else
		{
			if(f)putchar('+');
			else f=true;
			printf("%dx",a[n]);
		}
	}
	scanf("%d",&n);
	if(n<0)printf("%d",n);
	else if(n==0)return 0;
	else if(f)printf("+%d",n);
	else printf("%d",n);
}
