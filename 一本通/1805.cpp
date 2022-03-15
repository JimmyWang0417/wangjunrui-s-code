#include<cstdio>
#include<cctype>
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
	char Out[25*1000],*fe=Out,ch[25];
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
#define ull unsigned long long
inline ull f(ull a,ull b,ull c,ull n)
{
	ull s=(n+1)*(b/c);
	if(n&1)
		s+=(n+1)/2*n*(a/c);
	else
		s+=n/2*(n+1)*(a/c);
	a%=c;
	b%=c;
	ull m=(a*n+b)/c;
	if(m==0)
		return s;
	return s+n*m-f(c,c-b-1,a,m-1);
}
int main()
{
	re int T;
	re ull a,b,n,ans;
	for(read(T); T; T--)
	{
		read(a);
		read(b);
		read(n);
		ans=0;
		for(re int i=0; i<=60; ++i)
			if(b&(1ll<<i))
				ans--;
		for(re int i=0; i<=60; ++i)
			ans+=f(a,b,1ll<<i,n)-(f(a,b,1ll<<i+1,n)<<1);
		write(ans);
	}
	IO::flush();
	return 0;
}

