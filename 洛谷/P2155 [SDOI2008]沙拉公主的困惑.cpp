#include <bits/stdc++.h>
#define lowbit(x) ((x)&(-(x)))
#define re register
#define ll long long
#define ull unsigned long long
#define rep(i,a,b) for(re int i=a;i<=b;++i)
#define per(i,a,b) for(re int i=a;i>=b;--i)
template<typename T>
inline void read(T&x)
{
	x=0;
	char s=(char)getchar();
	bool f=false;
	while(!(s>='0'&&s<='9'))
	{
		if(s=='-')
			f=true;
		s=(char)getchar();
	}
	while(s>='0'&&s<='9')
	{
		x=(x<<1)+(x<<3)+s-'0';
		s=(char)getchar();
	}
	if(f)
		x=(~x)+1;
}
template<typename T,typename ...T1>
inline void read(T&x,T1&...x1)
{
	read(x);
	read(x1...);
}
template<typename T>
inline void clear(T*a,int l,int r,int val)
{
	memset(&a[l],val,sizeof(T)*(r-l+1));
}
int t,mod;
inline ll quickpow(ll a,int b,int p=mod)
{
//	printf("wdnmd\n");
	ll res=1;
	while(b)
	{
		if(b&1)
			res=res*a%p;
		a=a*a%p;
		b>>=1;
	}
//	printf("%d\n",res);
	return res;
}
const int N=1e7+5;
int prime[N],tot;
bool vis[N];
ll inv[N];
ll ans[N];
inline void getprime(int n)
{
	ans[1]=1;
	for(int i=2; i<=n; ++i)
	{
//		printf("%d ",i);
		if(!vis[i])
		{
			prime[++tot]=i;
			if(i!=mod)
				ans[i]=ans[i-1]*inv[i]%mod*(i-1)%mod;
			else
				ans[i]=ans[i-1]%(i-1)%mod;
			vis[i]=true;
		}
		else ans[i]=ans[i-1];
		for(int j=1; j<=tot; ++j)
		{
			if(prime[j]*i>n)
				break;
			vis[prime[j]*i]=true;
			if(i%prime[j]==0)
				break;
		}
	}
}
ll fac[N];
inline void work()
{
	int n,m;
	read(n,m);
	ll answer=fac[n]*ans[m]%mod;
	if(m<mod&&n>=mod)
		answer=answer*mod%mod;
	printf("%lld\n",answer);
}
signed main()
{
	read(t,mod);
	inv[1]=1;
	fac[0]=fac[1]=1;
	for(int i=2; i<=1e7; ++i)
	{
		inv[i]=(mod-mod/i)*inv[mod%i]%mod;
		fac[i]=fac[i-1]*(i==mod?1:i)%mod;
	}
	getprime(1e7);
//	printf("%d\n",tot);
	while(t--)
		work();
	return 0;
}


