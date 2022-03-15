#include<cstdio>
template<typename T>
inline void read(T&x)
{
	x=0;
	char s=(char)getchar();
	bool f=false;
	while(!(s>='0'&&s<='9'))
	{
		if(s=='-')
			f=true;
		s=(char)getchar();
	}
	while(s>='0'&&s<='9')
	{
		x=(x<<1)+(x<<3)+s-'0';
		s=(char)getchar();
	}
	if(f)
		x=(~x)+1;
}
inline void exgcd(int a,int b,int &d,int &x,int &y)
{
	if(b==0)
	{
		d=a;
		x=1;
		y=0;
		return;
	}
	exgcd(b,a%b,d,y,x);
	y-=a/b*x;
}
using namespace std;
int x,y,a,b;
int main()
{
	int T;
	read(T);
	while(T--)
	{
		read(x),read(y),read(a),read(b);
		if((y-x)%(a+b))
			printf("-1\n");
		else
			printf("%d\n",(y-x)/(a+b));
	}
}
