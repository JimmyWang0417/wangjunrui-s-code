#include<cstdio>
#include<cctype>
#include<algorithm>
#include<cstring>
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
int prime[10]= {0,2,3,5,7,11,13,17,19,0},n;
#define N 300
#define size 255
int dp[N][N],f1[N][N],f2[N][N],mod,ans;
struct node
{
	int val,S,big;
	inline void init()
	{
		int tmp=val;
		big=-1;
		for(re int i=1; i<=8; i++)
		{
			if(tmp%prime[i])
				continue;
			S|=1<<(i-1);
			while(tmp%prime[i]==0)
				tmp/=prime[i];
		}
		if(tmp!=1)
			big=tmp;
	}
	inline bool operator < (const node &b)const
	{
		return big<b.big;
	}
} a[510];
int main()
{
	read(n);
	read(mod);
	for(re int i=1; i<n; i++)
	{
		a[i].val=i+1;
		a[i].init();
	}
	sort(a+1,a+1+n);
	dp[0][0]=1;
	for(re int i=1; i<n; i++)
	{
		if(i==1||a[i].big!=a[i-1].big||a[i].big==-1)
		{
			memcpy(f1,dp,sizeof(f1));
			memcpy(f2,dp,sizeof(f2));
		}
		for(re int j=size; j>=0; j--)
			for(re int k=size; k>=0; k--)
			{
				if(j&k)
					continue;
				if((a[i].S&j)==0)
					f2[j][k|a[i].S]=(f2[j][k|a[i].S]+f2[j][k])%mod;
				if((a[i].S&k)==0)
					f1[j|a[i].S][k]=(f1[j|a[i].S][k]+f1[j][k])%mod;
			}
		if(i==n-1||a[i].big!=a[i+1].big||a[i].big==-1)
		{
			for(re int j=size; j>=0; j--)
				for(re int k=size; k>=0; k--)
				{
					if(j&k)
						continue;
					dp[j][k]=((f1[j][k]+f2[j][k])%mod+mod-dp[j][k])%mod;
				}
		}
	}
	for(re int j=size; j>=0; j--)
		for(re int k=size; k>=0; k--)
		{
			if(j&k||!dp[j][k])
				continue;
			ans=(ans+dp[j][k])%mod;
		}
	printf("%d\n",ans);
	return 0;
}
