/*https://www.luogu.org/problemnew/show/P1307*/
#include<cstdio>
using namespace std;
int sum,n;
int main()
{
	scanf("%d",&n);
	while(n!=0)
	{
		sum=(sum<<1)+(sum<<3)+n%10; 
		n/=10;
	}
	printf("%d\n",sum);
}
