#include<cstdio>
#include<cmath>
#define re register
#define ll long long
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
	return;
}
const int N=1e6+10,mod=1e9+7,INV6=166666668;
ll n,sqrtn,prime[N],sump[N],sum2p[N],cnt,g1[N],g2[N];
bool v[N];
inline void primes(int n)
{
	cnt=0;
	for(re int i=2; i<=n; i++)
	{
		if(!v[i])
		{
			prime[++cnt]=i;
			sump[cnt]=(sump[cnt-1]+i)%mod;
			sum2p[cnt]=(sum2p[cnt-1]+(ll)i*i%mod)%mod;
		}
		for(re int j=1; j<=cnt&&prime[j]*i<=n; j++)
		{
			v[prime[j]*i]=1;
			if(i%prime[j]==0)
				break;
		}
	}
}
ll val[N];
int id1[N],id2[N];
inline int get_id(ll x)
{
	return ((x<=sqrtn)?id1[x]:id2[n/x]);
}
inline ll min_25(ll x,ll y)
{
	if(x<prime[y]||x<=1)
		return 0;
	int k=get_id(x);
	ll res=((g2[k]-g1[k]+mod)%mod-(sum2p[y-1]-sump[y-1]+mod)%mod+mod)%mod;
	for(re int i=y; i<=cnt&&prime[i]*prime[i]<=x; i++)
	{
		ll t1=prime[i],t2=prime[i]*prime[i];
		for(re int j=1; t2<=x; j++,t1=t2,t2*=prime[i])
		{
			ll tt1=t1%mod,tt2=t2%mod;
			res=(res+min_25(x/t1,i+1)*tt1%mod*(tt1-1)%mod+tt2*(tt2-1)%mod)%mod;
		}
	}
	return res%mod;
}
int main()
{
	read(n);
	primes(sqrtn=sqrt(n));
	int tot=0;
	for(re ll i=1,j; i<=n; i=j+1)
	{
		j=n/(n/i);
		ll w=n/i;
		val[++tot]=w;
		if(w<=sqrtn)
			id1[w]=tot;
		else
			id2[n/w]=tot;
		w%=mod;
		g1[tot]=w*(w+1)/2%mod;
		g2[tot]=w*(w+1)%mod*(2ll*w+1)%mod*INV6%mod;

		g1[tot]=(g1[tot]-1+mod)%mod;
		g2[tot]=(g2[tot]-1+mod)%mod;
	}
	for(re int j=1; j<=cnt; j++)
	{
		for(re int i=1; i<=tot&&prime[j]*prime[j]<=val[i]; i++)
		{
			int k=get_id(val[i]/prime[j]);
			g1[i]=(g1[i]-prime[j]*(g1[k]-sump[j-1]+mod)%mod+mod)%mod;
			g2[i]=(g2[i]-prime[j]*prime[j]%mod*(g2[k]-sum2p[j-1]+mod)%mod+mod)%mod;
		}
	}
	/*for(int i=1; i<=tot; ++i)
		printf("%lld %lld %lld\n",val[i],g1[i],g2[i]);*/
	printf("%lld\n",(min_25(n,1)+1)%mod);
	return 0;
}
