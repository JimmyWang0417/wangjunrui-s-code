
// Problem : P3868 [TJOI2009]猜数字
// Contest : Luogu
// URL : https://www.luogu.com.cn/problem/P3868
// Memory Limit : 125 MB
// Time Limit : 1000 ms
// Powered by CP Editor (https://github.com/cpeditor/cpeditor)

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
inline ll quickmul(ll a,ll b,ll mod)
{
	ll res=0;
	while(b)
	{
		if(b&1)
			(res+=a)%=mod;
		(a<<=1)%=mod;
		b>>=1;
	}
	return res;
}
inline void exgcd(ll a,ll b,ll&d,ll&x,ll&y)
{
	if(b==0)
	{
		d=a;
		x=1;
		y=0;
	}
	else
	{
		exgcd(b,a%b,d,y,x);
		y-=(a/b)*x;
	}
}
const int N=15;
int n;
ll m[N],a[N];
signed main()
{
	read(n);
	for(re int i=1;i<=n;++i)
		read(a[i]);
	ll M=1;
	for(re int i=1;i<=n;++i)
	{
		read(m[i]);
		M*=m[i];
		a[i]=(a[i]%m[i]+m[i])%m[i];
	}
	ll ans=0;
	for(re int i=1;i<=n;++i)
	{
		ll Mi=M/m[i];
		ll x,y,d;
		exgcd(Mi,m[i],d,x,y);
		x=(x+M)%M;
		ans=(ans+quickmul(a[i],quickmul(Mi,x,M),M))%M;
	}
	printf("%lld\n",ans);
	return 0;
}



