#include <bits/stdc++.h>
#define int long long
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
const int N=40000+5,mod=1e9+7;
int prime[N],tot;
std::bitset<N>vis;
inline void getprime(int n)
{
	for(int i=2; i<=n; ++i)
	{
		if(!vis[i])
		{
			prime[++tot]=i;
			vis.set(i);
		}
		for(int j=1; j<=tot; ++j)
		{
			if(prime[j]*i>n)
				break;
			vis.set(prime[j]*i);
			if(i%prime[j]==0)
				break;
		}

	}
}
inline int getphi(int n)
{
	int ans=n;
	for(int i=1; i<=tot&&prime[i]*prime[i]<=n; ++i)
	{
		if(n%prime[i]==0)
		{
			while(n%prime[i]==0)
				n/=prime[i];
			ans-=ans/prime[i];
		}
	}
	if(n>1)
		ans-=ans/n;
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
	return res;
}
signed main()
{
	getprime(N-5);
//	printf("%d\n",tot);
	int T;
	read(T);
	while(T--)
	{
		int n;
		read(n);
		int i=1,ans=0;
//		printf("%d\n",qui);
		for(i=1; i*i<n; ++i)
			if(n%i==0)
				(ans+=((ll)quickpow(n,i-1)*getphi(n/i)%mod+(ll)quickpow(n,n/i-1)*getphi(i)%mod)%mod)%=mod;
		if(i*i==n)
			(ans+=((ll)quickpow(n,i-1)*getphi(i)%mod))%=mod;
		printf("%d\n",ans);
	}
	return 0;
}


