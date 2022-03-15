/*https://www.luogu.org/problemnew/show/P1022*/
#include<cstdio>
using namespace std;
int x,sum1,sum2;
char s,a;
bool f;
int main()
{
	s=getchar();
	while(s!='=')
	{
		if(s=='-')
		{
			f=true;
			s=getchar();
		}
		else if(s>='0'&&s<='9')
		{
			x=0;
			do
			{
				x=(x<<1)+(x<<3)+s-'0';
				s=getchar();
			}
			while(s>='0'&&s<='9');
			if(f)
				x=-x;
			f=false;
			if(s>='a'&&s<='z')
			{
				sum1+=x;
				a=s;
				s=getchar();
			}
			else
				sum2-=x;
		}
		else if(s>='a'&&s<='z')
		{
			a=s;
			sum1++;
			s=getchar();
		}
		else
			s=getchar();
	}
	s=getchar();
	while(s!='\n')
	{
		if(s=='-')
		{
			f=true;
			s=getchar();
		}
		else if(s>='0'&&s<='9')
		{
			x=0;
			do
			{
				x=(x<<1)+(x<<3)+s-'0';
				s=getchar();
			}
			while(s>='0'&&s<='9');
			if(f)
				x=-x;
			f=false;
			if(s>='a'&&s<='z')
			{
				sum1-=x;
				a=s;
				s=getchar();
			}
			else
				sum2+=x;
		}
		else if(s>='a'&&s<='z')
		{
			a=s;
			sum1--;
			s=getchar();
		}
		else
			s=getchar();
	}
	if(sum2/(double)sum1==0.0)
		printf("%c=0.000",a);
	else
		printf("%c=%0.3f\n",a,sum2/(double)sum1);
}
