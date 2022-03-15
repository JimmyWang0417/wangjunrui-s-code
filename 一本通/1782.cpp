#include<stdio.h>
#include<ctype.h>
#include<string.h>
#include<algorithm>
#define re register
#define mod 998244353
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
const int N=1030;
int n,m,dp[2][N],pre[N],all,sup[12],opp[12],ans;
int main()
{
	read(n);
	read(m);
	re int *now=dp[0],*last=dp[1],s=0;
	all=(1<<m)-1;
	for(re int i=0,x; i<m; i++)
	{
		read(x);
		s|=(x<<i);
	}
	for(re int i=0; i<=all; i++)
		pre[i]=pre[i>>1]^(i&1);
	last[s]=1;
	for(re int i=2,x; i<=n-2; i++)
	{
		memset(sup,0,sizeof(sup));
		memset(opp,0,sizeof(opp));
		memset(now,0,sizeof(dp[0]));
		for(re int j=0; j<m; j++)
			for(re int k=0; k<m; k++)
			{
				read(x);
				sup[k]|=(x<<j);
				opp[j]|=(x<<k);
			}
		for(re int j=0,sups,opps; j<=all; j++)
		{
			if(last[j])
			{
				sups=opps=0;
				for(re int k=0; k<m; k++)
				{
					sups|=(pre[j&sup[k]]<<k);
					opps|=(pre[j&opp[k]]<<k);
				}
				now[sups]=(now[sups]+last[j])%mod;
				now[opps]=(now[opps]+last[j])%mod;
			}
		}
		swap(last,now);
	}
	s=0;
	for(re int i=0,x; i<m; i++)
	{
		read(x);
		s|=(x<<i);
	}
	for(re int i=0; i<=all; i++)
		ans=(ans+(pre[s&i]?0:last[i]))%mod;
	write(ans);
	IO::flush();
	return 0;
}
