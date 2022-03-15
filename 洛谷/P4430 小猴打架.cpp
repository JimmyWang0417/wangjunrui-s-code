#include<cstdio>
#include<cctype>
#define re register
using namespace std;
namespace IO
{
	template<typename T>
	inline void read(T &x)
	{
		x=0;
		T f=1, ch=getchar();
		while (!isdigit(ch) && ch^'-') ch=getchar();
		if (ch=='-') f=-1, ch=getchar();
		while (isdigit(ch)) x=(x<<1)+(x<<3)+(ch^48), ch=getchar();
		x*=f;
	}

	char Out[25],*fe=Out;
	inline void flush()
	{
		fwrite(Out,1,fe-Out,stdout);
		fe=Out;
	}
	template<typename T>
	inline void write(T x)
	{
		if (!x) *fe++=48;
		if (x<0) *fe++='-', x=-x;
		T num=0, ch[20];
		while (x) ch[++num]=x%10+48, x/=10;
		while (num) *fe++=ch[num--];
		*fe++='\n';
	}
}
#define mod 9999991
using namespace IO;
int n;
long long ans=1;
int main()
{
	read(n);
	for(re int i=1; i<=n-2; i++)
		ans=(ans*n)%mod;
	for(re int i=1; i<n; i++)
		ans=(ans*i)%mod;
	write(ans);
	flush();
	return 0;
}
