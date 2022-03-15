#include<cstdio>
#define re register
using namespace std;
template<typename T>
inline void read(T&x)
{
	x=0;
	char s=getchar();
	bool f=false;
	while(!(s>='0'&&s<='9'))
	{
		if(s=='-')
			f=true;
		s=getchar();
	}
	while(s>='0'&&s<='9')
	{
		x=(x<<1)+(x<<3)+s-'0';
		s=getchar();
	}
	if(f)
		x=(~x)+1;
}
int p,t,pre;
long long n,a,b,temp;
int f[1000010]= {0,1};
#define ull unsigned long long
inline ull quickpow(ull a,ull x,ull mod)//快速幂，注意用unsigned long long ,否则long long 连样例都过不去。。。
{
	ull base=a,ans=1;
	while(x!=0)
	{
		if(x&1)
		{
			ans*=base;
			ans%=mod;
		}
		x>>=1;
		base*=base;
		base%=mod;
	}
	return ans%mod;
}
int main()
{
	ull a,b;
	int t,n,tmp,period;
	read(t);
	while(t--)
	{
		read(a);
		read(b);
		read(n);
		if(n==1 || a==0)
		{
			putchar('0');
			putchar('\n');
			continue;
		}
		f[1]=1;
		f[2]=1;
		for(int i=3; i<=n*n+10; i++)
		{
			f[i]=(f[i-1]+f[i-2])%n;
			if(f[i]==f[2] && f[i-1]==f[1])
			{
				period=i-2;
				break;
			}
		}
		tmp=quickpow(a%period,b,period);
		printf("%d\n",f[tmp]);
	}
}

