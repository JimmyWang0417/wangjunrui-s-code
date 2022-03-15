#include<cstdio>
#include<cctype>
#define re register
using namespace std;
const int N=1e5+5;
int n;
__int128 lcm,now,t,gcd,a,b,x,y;
namespace IO
{
	template<typename T>
	inline void read(T & x)
	{
		x=0;
		bool b=false;
		char ch=getchar();
		while(!isdigit(ch)&&ch^'-')
			ch=getchar();
		if(ch=='-')
		{
			b=true;
			ch=getchar();
		}
		while(isdigit(ch))
		{
			x=(x<<1)+(x<<3)+(ch^'0');
			ch=getchar();
		}
		if(b)
			x=~x+1;
		return;
	}
	char Out[1<<30],*fe=Out,ch[25];
	int num=0;
	template<typename T>
	inline void write(T x)
	{
		if(!x)
			*fe++='0';
		if(x<0)
		{
			*fe++='-';
			x=-x;
		}
		while(x)
		{
			ch[++num]=x%10+'0';
			x/=10;
		}
		while(num)
			*fe++=ch[num--];
		*fe++='\n';
	}
	inline void flush()
	{
		fwrite(Out,1,fe-Out,stdout);
		fe=Out;
	}
}
inline void Exgcd(__int128 a,__int128 b,__int128&d,__int128&x,__int128&y)
{
	if(b==0)
	{
		x=1;
		y=0;
		d=a;
	}
	else
	{
		Exgcd(b,a%b,d,x,y);
		t=x;
		x=y;
		y=t-a/b*y;
	}
	return;
}
using namespace IO;
int main()
{
	read(n);
	bool flag=false;
	read(a);
	read(b);
	now=b;
	lcm=a;
	for(re int i=1; i<n; i++)
	{
		read(a);
		read(b);
		b=(b-now%a+a)%a;
		Exgcd(lcm,a,gcd,x,y);
		if(b%gcd!=0&&!flag)
		{
			printf("-1\n");
			flag=true;
		}
		now+=x*(b/gcd)%a*lcm;
		lcm=lcm/gcd*a;
		now=(now%lcm+lcm)%lcm;
	}
	if(!flag)
		write(now);
	IO::flush();
	return 0;
}
