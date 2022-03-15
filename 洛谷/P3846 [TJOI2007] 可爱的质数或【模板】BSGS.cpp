#include <map>
#include <cmath>
#include <cstdio>
#define int ll
#define re register
#define ll long long
#define rep(i,a,b) for(re int i=a;i<=b;++i)
#define per(i,a,b) for(re int i=a;i>=b;--i)
using namespace std;
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
map<int,int>mp;
inline int quickpow(int a,int b,int mod)
{
	int res=1;
	while(b)
	{
		if(b&1)
			res=res*a%mod;
		a=a*a%mod;
		b>>=1;
	}
	return res;
}
inline int solve(int a,int n,int mod)
{
	if(n==1)
		return 0;
	mp.clear();
	int res=n,m=(int)sqrt(mod)+1;
	for(re int i=0; i<m; ++i)
	{
		mp[res]=i;
		res=res*a%mod;
	}
	int x=quickpow(a,m,mod);
	res=1;
	for(re int i=1; i<=m+1; ++i)
	{
		res=res*x%mod;
		if(mp.count(res))
			return i*m-mp[res];
	}
	return -1;
}
signed main()
{
	int a,n,mod;
	read(mod,a,n);
	int ans=solve(a,n,mod);
	if(~ans)
		printf("%lld\n",ans);
	else
		printf("no solution\n");
	return 0;
}

