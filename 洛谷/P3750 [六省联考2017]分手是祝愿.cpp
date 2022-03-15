#include <bits/stdc++.h>
#define int ll
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
inline void clear(T*array,int l,int r,int val)
{
	memset(&array[l],val,sizeof(T)*(r-l+1));
}
using namespace std;
const int N=1e5+5,mod=1e5+3;
inline ll quickpow(ll a,int b)
{
	ll res=1;
	while(b)
	{
		if(b&1)
			res=res*a%mod;
		a=a*a%mod;
		b>>=1;
	}
	return res;
}
int n,k,a[N];
ll dp[N];
signed main()
{
	read(n,k);
	for(int i=1; i<=n; ++i)
		read(a[i]);
	int cnt=0;
	for(int i=n; i>=1; --i)
	{
		if(a[i])
		{
			++cnt;
			for(int j=1; j*j<=i; ++j)
				if(i%j==0)
				{
					a[j]^=1;
					if(j*j!=i)
						a[i/j]^=1;
				}
		}
	}
	ll sum;
	if(cnt<=k)
		sum=cnt;
	else
	{
		sum=k;
		dp[n+1]=0;
		for(int i=n; i>k; --i)
			dp[i]=(n+(n-i)*dp[i+1]%mod)%mod*quickpow(i,mod-2)%mod;
		for(int i=cnt; i>k; --i)
			(sum+=dp[i])%=mod;
	}

	for(int i=1; i<=n; ++i)
		(sum*=i)%=mod;
	printf("%lld\n",sum);
	return 0;
}


