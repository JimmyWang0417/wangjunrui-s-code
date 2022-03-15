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
const int N=2e3+5;
const int mod=998244353;
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
struct node
{
	int x,y;
} a[N];
int n,k;
inline ll lagrange()
{
	ll ans=0;
	for(int i=1; i<=n; ++i)
	{
		ll resa=1,resb=1;
		for(int j=1; j<=n; ++j)
		{
			if(i==j)
				continue;
			resa=resa*(k-a[j].x)%mod;
			resb=resb*(a[i].x-a[j].x)%mod;
		}
		(ans+=a[i].y*resa%mod*quickpow(resb,mod-2)%mod)%=mod;
	}
	return (ans+mod)%mod;
}
signed main()
{
	read(n,k);
	for(int i=1; i<=n; ++i)
		read(a[i].x,a[i].y);
	printf("%lld\n",lagrange());
	return 0;
}


