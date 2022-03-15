#include <cstdio>
#include <cmath>
#include <bitset>
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
using namespace std;
const int N=40005;
int mod;
int prime[N],tot;
bitset<N>vis;
inline void getprime(int n)
{
	for(int i=2; i<=n; ++i)
	{
		if(!vis[i])
		{
			vis[i]=true;
			prime[++tot]=i;
		}
		for(int j=1; j<=tot; ++j)
		{
			if(prime[j]*i>n)
				break;
			vis[i*prime[j]]=true;
			if(i%prime[j]==0)
				break;
		}
	}
}
inline int getphi(int n)
{
	int ans=n;
	for(int i=1; prime[i]*prime[i]<=n&&i<=tot; ++i)
	{
		if(n%prime[i]==0)
		{
			while(n%prime[i]==0)
				n/=prime[i];
			ans=ans-ans/prime[i];
		}
	}
	if(n>1)
		ans=ans-ans/n;
	return ans%mod;
}
inline int quickpow(int a,int b,int p=mod)
{
	int res=1;
	while(b)
	{
		if(b&1)
			res=(ll)res*a%p;
		a=(ll)a*a%p;
		b>>=1;
	}
//	printf("%d ",res);
	return res;
}
inline void work()
{
	int n;
	read(n),read(mod);
	int i=1;
	ll ans=0;
//	printf("%d\n", getphi(4));
	for(; i*i<n; ++i)
	{
		if(n%i==0)
			(ans+=((ll)quickpow(n,i-1)*getphi(n/i)%mod+(ll)quickpow(n,n/i-1)*getphi(i)%mod)%mod)%=mod;
//		if (n % i == 0)
//			printf("%d %d %d %d %d\n", ans, quickpow(n, i - 1), getphi(n / i), quickpow(n, n / i - 1), getphi(i));
	}
	if(i*i==n)
		(ans+=1ll*quickpow(n,i-1)*getphi(i))%=mod;
	printf("%lld\n",ans);
}
signed main()
{
	getprime(N-5);
	int T;
	read(T);
	while(T--)
		work();
	return 0;
}


