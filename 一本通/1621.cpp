#include<cstdio>
using namespace std;
inline int read()
{
	register char s=getchar();
	int x=0;
	while(s<'0'||s>'9')
		s=getchar();
	while(s>='0'&&s<='9')
	{
		x=(x<<1)+(x<<3)+s-'0';
		s=getchar();
	}
	return x;
}
int yue(int nn)
{
	int n=nn,sum=1,k=0,j=2;
	while(n!=1)
	{
		if(n%j==0)
		{
			k++;
			n/=j;
		}
		else
		{
			if(k!=0)sum*=(k+1);
			j++;
		}
	}
	sum*=(k+1);
	return sum;
}
int n,x;
int main()
{
	scanf("%d",&n); 
	for(register int i=1;i<=n;i++)
	{
		scanf("%d",&x);
		printf("%d\n",yue(x));
	}
}
