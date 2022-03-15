#include<cstdio>
#include<cmath>
#define re register
using namespace std;
template<typename T>
inline void read(T&x)
{
	x=0;
	char s=getchar();
	bool f=false;
	while(!(s>='0'&&s<='9'))
	{
		if(s=='-')
			f=true;
		s=getchar();
	}
	while(s>='0'&&s<='9')
	{
		x=(x<<1)+(x<<3)+s-'0';
		s=getchar();
	}
	if(f)
		x=(~x)+1;
}
int n,temp;
int main()
{
	read(n);
	temp=sqrt(n);
	for(re int i=2; i<=temp; i++)
		if(n%i==0)
		{
			printf("%d\n",n/i);
			return 0;
		}
	printf("1\n");
	return 0;
}

