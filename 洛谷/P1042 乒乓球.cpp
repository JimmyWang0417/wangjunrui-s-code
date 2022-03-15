/*https://www.luogu.org/problemnew/show/P1042*/
#include<cstdio>
using namespace std;
char a[1000000],s;
int n,sum1,sum2,ans;
int main()
{
	while(true)
	{
		s=getchar();
		if(s=='E')break;
		if(s=='W'||s=='L')
			a[++n]=s;
	}
	if(n==0)
	{
		printf("0:0\n\n0:0\n");
		return 0;
	}
	for(register int i=1; i<=n; i++)
	{
		if(a[i]=='W')
			sum1++;
		else
			sum2++;
		if(sum1>=11&&sum1-sum2>=2||sum2>=11&&sum2-sum1>=2)
		{
			printf("%d:%d\n",sum1,sum2);
			ans++;
			sum1=sum2=0;
		}
	}
	if(sum1!=0||sum2!=0)
	{
		printf("%d:%d\n",sum1,sum2);
		sum1=sum2=0;
	}
	if(ans==1)
		printf("0:0\n");
	putchar('\n');
	for(register int i=1; i<=n; i++)
	{
		if(a[i]=='W')
			sum1++;
		else
			sum2++;
		if(sum1>=21&&sum1-sum2>=2||sum2>=21&&sum2-sum1>=2)
		{
			printf("%d:%d\n",sum1,sum2);
			sum1=sum2=0;
		}
	}
	if(sum1!=0||sum2!=0)
	{
		printf("%d:%d\n",sum1,sum2);
		sum1=sum2=0;
	}
}
