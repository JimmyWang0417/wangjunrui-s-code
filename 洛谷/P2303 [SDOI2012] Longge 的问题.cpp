#include <bits/stdc++.h>
#define int unsigned int
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
inline int getphi(int n)
{
	int ans=n;
	for(int i=2; 1ll*i*i<=n; ++i)
		if(n%i==0)
		{
			while(n%i==0)
				n/=i;
			ans=ans/i*(i-1);
		}
	if(n>1)
		ans=ans/n*(n-1);
	return ans;
}
inline ll getans(int n)
{
	ll ans=(ll)n+(ll)getphi(n);
	int i=2;
	for(; 1ll*i*i<n; ++i)
	{
		if(n%i==0)
		{
			ans+=(ll)i*getphi(n/i)+(ll)(n/i)*getphi(i);
		}
	}
	if(i*i==n)
		ans+=(ll)i*getphi(i);
	return ans;
}
signed main()
{
	int n;
	read(n);
	printf("%lld\n",n==1?1ll:getans(n));
	return 0;
}


