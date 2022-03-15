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
		bool f=false;
		char ch=getchar();
		while (!isdigit(ch) && ch^'-') ch=getchar();
		if (ch=='-') f=true, ch=getchar();
		while (isdigit(ch)) x=(x<<1)+(x<<3)+(ch^48), ch=getchar();
		if(f)
			x=-x;
		return;
	}
	char Out[1<<28],*fe=Out;
	inline void flush()
	{
		fwrite(Out,1,fe-Out,stdout);
		fe=Out;
		return;
	}
	template<typename T>
	inline void write(T x)
	{
		if (!x) *fe++=48;
		if (x<0) *fe++='-', x=-x;
		T num=0, ch[20];
		while (x) ch[++num]=x%10+48, x/=10;
		while (num) *fe++=ch[num--];
		//*fe++='\n';
		return;
	}
	inline void insert_char(char s)
	{
		*fe++=s;
		return;
	}
}
using namespace IO;
const int SIZE=64;
int T,k;
long long m;
long long c[SIZE+10][SIZE+10];
inline long long solve(long long x)
{
	long long res=0;
	x++;
	for(re int i=62,j=0; i>=0; i--)
		if(x&(1ll<<i))
		{
			if(k>=j)
				res+=c[i][k-j];
			j++;
		}
	return res;
}
inline bool check(long long m,long long x)
{
	return solve(2ll*x)-solve(x)>=m;
}
inline long long find(long long m)
{
	long long l=1,r=2e18,ans=0,mid;
	while(l<=r)
	{
		mid=l+r>>1ll;
		if(check(m,mid))
		{
			ans=mid;
			r=mid-1;
		}
		else
			l=mid+1;
	}
	return ans;
}
int main()
{
	for(re int i=0; i<=SIZE; i++)
		c[i][0]=1;
	for(re int i=1; i<=SIZE; i++)
		for(re int j=1; j<=i; j++)
			c[i][j]=c[i-1][j-1]+c[i-1][j];
	read(T);
	while(T--)
	{
		read(m);
		read(k);
		if(m==1&&k==1)
		{
			write(1);
			insert_char(' ');
			write(-1);
			insert_char('\n');
		}
		else if(m==0)
		{
			write(1);
			insert_char(' ');
			write((1ll<<k-1)-1);
			insert_char('\n');
		}
		else
		{
			long long a=find(m+1),b=find(m);
			write(b);
			insert_char(' ');
			write(a-b);
			insert_char('\n');
		}
	}
	IO::flush();
	return 0;
}
