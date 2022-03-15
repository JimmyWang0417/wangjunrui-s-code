#include<cstdio>
using namespace std;
template<typename T>
inline void read(T&x)
{
	x=0;
	char s=(char)getchar();
	bool flag=false;
	while(!(s>='0'&&s<='9'))
	{
		if(s=='-')
			flag=true;
		s=(char)getchar();
	}
	while(s>='0'&&s<='9')
	{
		x=(x<<1)+(x<<3)+s-'0';
		s=(char)getchar();
	}
	if(flag)
		x=(~x)+1;
	return;
}
int num,n,T;
int main()
{
	read(T);
	while(T--)
	{
		read(n);
		num=n>>1;
		if(n&1)
		{
			putchar('7');
			--num;
		}
		while(num--)
			putchar('1');
		putchar('\n');
	}
	return 0;
}
