#include<stdio.h>
#include<ctype.h>
#include<algorithm>
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
	char Out[1<<30],*fe=Out,ch[25];
	int num=0;
	template<typename T>
	inline void write(T x,char s)
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
		*fe++=s;
	}
	inline void flush()
	{
		fwrite(Out,1,fe-Out,stdout);
		fe=Out;
	}
}
using IO::read;
using IO::write;
const int N=6010*6010;
int n,m,sum,cnt=-1,ans[6010],prime[N];
int vis[N];
bool v[N];
inline void solve(int s)
{
	int x=s;
	while(s&&x)
	{
		if(ans[x]==1)
		{
			ans[x]=2;
			s-=x;
		}
		x=x>s?s:x-1;
	}
	return;
}
inline void primes(int n)
{
	m=0;
	for(re int i=2; i<=n; i++)
	{
		if(vis[i]==0)
		{
			vis[i]=i;
			v[i]=true;
			prime[++m]=i;
		}
		for(re int j=1; j<=m; j++)
		{
			if(prime[j]>vis[i]||prime[j]>n/i)
				break;
			vis[i*prime[j]]=prime[j];
		}
	}
}
int main()
{
	read(n);
	if(n<=1)
	{
		write(-1,'\n');
		IO::flush();
		return 0;
	}
	sum=n*(n+1)>>1;
	fill(ans+1,ans+1+n,1);
	primes(sum);
	if(v[sum])
		cnt=1;
	else
	{
		if(v[sum-2])
		{
			ans[2]=2;
			cnt=2;
			solve(sum-2);
		}
		else if(sum%2==0)
		{
			for(re int i=1; i<=m; i++)
				if(v[sum-prime[i]])
				{
					solve(prime[i]);
					cnt=2;
					break;
				}
		}
		else
		{
			ans[3]=3;
			sum-=3;
			for(re int i=1; i<=m; i++)
				if(v[sum-prime[i]])
				{
					solve(prime[i]);
					cnt=3;
					break;
				}
		}
	}
	write(cnt,'\n');
	if(cnt>0)
	{
		for(re int i=1; i<=n; i++)
			write(ans[i],' ');
	}
	IO::flush();
	return 0;
}

