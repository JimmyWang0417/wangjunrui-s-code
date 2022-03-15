#include<cstdio>
#include<iostream>
#include<cmath>
#define re register
#define ll long long
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
const int N=25e4+10;
int prime[N],tot,m,
    id1[N],id2[N];
bool vis[N];
ll sqrt_n,w[N],g[N],sp[N];
inline void primes(int n)
{
	for(re int i=2; i<=n; i++)
	{
		if(!vis[i])
		{
			prime[++tot]=i;
			sp[tot]=sp[tot-1]+i;
		}
		for(re int j=1; j<=tot&&1ll*i*prime[j]<=n; j++)
		{
			vis[i*prime[j]]=true;
			if(i%prime[j]==0)
				break;
		}
	}
	return;
}
inline ll min_25(ll n)
{
	m=tot=0;
	sqrt_n=sqrt(n);
	primes(sqrt_n);
	for(re ll i=1ll,j; i<=n; i=j+1)
	{
		j=n/(n/i);
		w[++m]=n/i;
		g[m]=(w[m]*(w[m]+1)>>1)-1;
		if(w[m]<=sqrt_n)
			id1[w[m]]=m;
		else
			id2[j]=m;
	}
	ll ans=0ll;
	for(re int j=1; j<=tot; j++)
		for(re int i=1; i<=m&&(ll)prime[j]*prime[j]<=w[i]; i++)
		{
			int k=(w[i]/prime[j]<=sqrt_n)?id1[w[i]/prime[j]]:id2[n/(w[i]/prime[j])];
			if(i==1)
				ans+=g[k]-sp[j-1];
			g[i]-=prime[j]*(g[k]-sp[j-1]);
		}
	return ans;
}
int main()
{
	ll l,r;
	read(l);
	read(r);
	printf("%lld\n",min_25(r)-min_25(l-1));
	return 0;
}
