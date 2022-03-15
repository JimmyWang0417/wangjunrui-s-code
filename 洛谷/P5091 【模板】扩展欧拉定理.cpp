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
inline void clear(T*array,int l,int r,int val)
{
	memset(&array[l],val,sizeof(T)*(r-l+1));
}
using namespace std;
const int N=1e5+5;
inline int getphi(int n)
{
	int ans=n;
	for(int i=2; i*i<=n; ++i)
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
inline void get(int &x,const int mod)
{
	x=0;
	char s=(char)getchar();
	bool flag=false;
	while(!(s>='0'&&s<='9'))
		s=(char)getchar();
	while(s>='0'&&s<='9')
	{
		x=(x*10)+s-'0';
		if(x>=mod)
		{
			x%=mod;
			flag=true;
		}
		s=(char)getchar();
	}
	if(flag)
		x+=mod;
}
inline ll quickpow(ll a,int b,int mod)
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
signed main()
{
	int a,m,b;
	read(a,m);
	a%=m;
	int phi=getphi(m);
	get(b,phi);
	printf("%lld\n",quickpow(a,b,m));
	return 0;
}


