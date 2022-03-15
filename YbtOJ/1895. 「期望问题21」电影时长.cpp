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
const int N=2e5+5;
const int mod=1004535809;
inline ll quickpow(ll a,ll b)
{
	ll res=1;
	while(b)
	{
		if(b&1)
			(res*=a)%=mod;
		(a*=a)%=mod;
		b>>=1;
	}
	return res;
}
int n;
struct node
{
	int l,x,y;
	inline bool operator < (const node &rhs)const
	{
		return (ll)x*(rhs.y-rhs.x)*l>(ll)rhs.x*(y-x)*rhs.l;
	}
} a[N];
signed main()
{
	freopen("movie.in","r",stdin);
	freopen("movie.out","w",stdout);
	read(n);
	for(int i=1; i<=n; ++i)
		read(a[i].l,a[i].x,a[i].y);
	sort(a+1,a+1+n);
	ll len=0,ans=0;
	for(int i=1; i<=n; ++i)
	{
		ll p=a[i].x*quickpow(a[i].y,mod-2)%mod;
		// printf("%lld\n",quickpow(a[i].y,mod-2));
		(ans+=(2*p-1)%mod*a[i].l%mod+len*(1-p+mod)%mod)%=mod;
		(len+=p*a[i].l%mod)%=mod;
//		printf("%lld\n",len);
	}
	printf("%lld\n",ans);
	return 0;
}


