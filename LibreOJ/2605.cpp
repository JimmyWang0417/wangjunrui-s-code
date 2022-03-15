#include<cstdio>
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
inline void Exgcd(int a,int b,int&x,int&y)
{
	if(b==0)
	{
		x=1;
		y=0;
	}
	else
	{
		Exgcd(b,a%b,x,y);
		int t=x;
		x=y;
		y=t-a/b*y;
	}
	return;
 } 
bvbb int a,b,x,y;
int main()
{
	read(a);
	read(b);
	Exgcd(a,b,x,y);
	printf("%d\n",(unsigned int)(x%b+b)%b);
	return 0;
}

