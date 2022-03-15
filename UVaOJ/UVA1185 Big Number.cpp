#include<stdio.h>
#include<ctype.h>
#include<math.h>
#define re register
using namespace std;
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
	char Out[1000*7+10],*fe=Out,ch[25];
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
using IO::read;
using IO::write;
const int N=1e7+10;
int T,x,maxx,tmp[N];
double lg[N];
int main()
{
	read(T);
	for(re int i=1; i<=1e7; i++)
		lg[i]=lg[i-1]+log10(i);
	for(re int i=1; i<=1e7; i++)
		tmp[i]=lg[i]+1;
	while(T--)
	{
		read(x);
		printf("%d\n",tmp[x]);
	}
	return 0;
}

