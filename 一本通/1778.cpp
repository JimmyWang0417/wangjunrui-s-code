#include<cstdio>
#include<cctype>
#include<cstring>
#define re register
#define max(x,y) ((x)>(y)?(x):(y))
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
#define mod 999983
using namespace IO;
int n,ans,a[20],len,ans1,ans2,f[(int)1e3+1][(int)9e3+1],maxx;
char s[20];
int main()
{
	read(n);
	scanf("%s",s+1);
	len=strlen(s+1);
	for(re int i=1; i<=len; i++)
	{
		a[i]=s[i]-'0';
		maxx=max(maxx,a[i]);
	}
	//putchar('\n');
	f[0][0]=1;
	for(re int i=1; i<=n; i++)
		for(re int j=0; j<=i*maxx; j++)
			for(re int k=1; k<=len; k++)
				if(j-a[k]>=0)
					f[i][j]=(f[i][j]+f[i-1][j-a[k]])%mod;
	for(re int i=0; i<=maxx*n; i++)
		ans=(ans+2ll*f[n][i]%mod*f[n][i]%mod)%mod;
	int l1=(n+1)>>1,l2=n>>1;
	for(re int i=0; i<=maxx*l1; i++)
		ans1=(ans1+1ll*f[l1][i]*f[l1][i]%mod)%mod;
	for(re int i=0; i<=maxx*l2; i++)
		ans2=(ans2+1ll*f[l2][i]*f[l2][i]%mod)%mod;
	write((ans-1ll*ans1*ans2%mod+mod)%mod);
	flush();
	return 0;
}
