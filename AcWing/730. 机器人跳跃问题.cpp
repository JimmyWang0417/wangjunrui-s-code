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
int n,a[N];
inline bool check(ll E)
{
	for(int i=1; i<=n; ++i)
	{
		if(E>=a[i])
			E+=E-a[i];
		else
			E-=a[i]-E;
//		printf("%lld ",E);
		if(E<0)
			return false;
		if(E>=1e18)
			return true;
	}
	return E>=0;
//	putchar('\n');
}
signed main()
{
	read(n);
	for(int i=1; i<=n; ++i)
		read(a[i]);
	ll l=0,r=1e10,ans=1e10;
//	printf("%d\n",check(4));
	while(l<=r)
	{
		ll mid=(l+r)>>1;
		if(check(mid))
		{
			ans=mid;
			r=mid-1;
		}
		else
			l=mid+1;
//		printf("%lld %lld %lld\n",l,r,ans);
	}
	printf("%lld\n",ans);
	return 0;
}


