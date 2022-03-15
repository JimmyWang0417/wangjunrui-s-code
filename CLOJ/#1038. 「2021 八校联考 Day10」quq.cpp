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
const int N=1e6+5,M=1e7+5;
const int mod=19260817;
int n,a[N];
ll inv[M];
signed main()
{
	read(n);
	for(int i=1; i<=n; ++i)
		read(a[i]);
	sort(a+1,a+1+n);
	inv[1]=1;
	for(int i=2; i<=a[n]; ++i)
		inv[i]=(mod-mod/i)*inv[mod%i]%mod;
	ll ans=0;
	for(int i=n; i>=1; --i)
		for(int j=a[i]; j>a[i-1]; --j)
			(ans+=a[i]*inv[a[n]-j+1])%=mod;
	printf("%lld\n",ans);
	return 0;
}


