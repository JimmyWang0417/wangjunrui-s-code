#include<cstdio>
#include<algorithm>
#define re register
using namespace std;
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
char str[2][20]= {"Stan wins\n","Ollie wins\n"};
inline void gcd(int m,int n,bool flag)
{
	if(n==0)
		printf("%s\n",str[flag^1]);
	else if(m/n>1)
		printf("%s\n",str[flag]);
	else
		gcd(n,m-n,flag^1);

}
int n,m;
int main()
{
	while(read(n),read(m),n||m)
	{
		if(n>m)
			swap(n,m);
		gcd(m,n,0);
	}
}
