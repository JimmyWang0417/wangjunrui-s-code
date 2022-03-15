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
const int N=1e7+5,mod=20101009;
int prime[N],tot,mul[N];
ll sum[N];
std::bitset<N>vis;
inline void getmul(int n)
{
	mul[1]=1;
	for(int i=2; i<=n; ++i)
	{
		if(!vis[i])
		{
			prime[++tot]=i;
			mul[i]=-1;
		}
		for(int j=1; j<=tot; ++j)
		{
			if(i*prime[j]>n)
				break;
			vis.set(i*prime[j]);
			if(i%prime[j])
				mul[i*prime[j]]=-mul[i];
			else
			{
				mul[i*prime[j]]=0;
				break;
			}
		}
	}
	for(int i=1; i<=n; ++i)
		sum[i]=(sum[i-1]+(ll)(mul[i]+mod)*i%mod*i%mod)%mod;
}
inline ll calc(int n)
{
	return ((ll)n*(n+1)/2)%mod;
}
inline ll getans(int n,int m)
{
	ll ans=0;
	for(int l=1,r; l<=n&&l<=m; l=r+1)
	{
		r=std::min(n/(n/l),m/(m/l));
		(ans+=(calc(n/l)*calc(m/l)%mod*(sum[r]-sum[l-1]+mod)%mod))%=mod;
	}
	return ans;
}
inline ll work(int n,int m)
{
	ll ans=0;
	for(int l=1,r; l<=n&&l<=m; l=r+1)
	{
		r=std::min(n/(n/l),m/(m/l));
		(ans+=(calc(r)-calc(l-1)+mod)%mod*getans(n/l,m/l)%mod)%=mod;
	}
	return ans;
}
signed main()
{
	getmul(1e7);
	int n,m;
	read(n,m);
	printf("%lld\n",work(n,m));
	return 0;
}


