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
const int N=50005;
const int mod=999911659;
const int needmod[]= {2,3,4679,35617};
inline ll quickpow(ll a,int b,int p)
{
	ll res=1;
	while(b)
	{
		if(b&1)
			(res*=a)%=p;
		(a*=a)%=p;
		b>>=1;
	}
	return res;
}
ll fac[N],inv[N];
inline ll C(int n,int m,int p)
{
	if(n<m||m<0)
		return 0;
	return fac[n]*inv[m]%p*inv[n-m]%p;
}
inline ll Lucas(int n,int m,int p)
{
	if(n<m)
		return 0;
	if(!m)
		return 1;
	return Lucas(n/p,m/p,p)*C(n%p,m%p,p)%p;
}
int n,g;
inline ll solve(int p)
{
	fac[0]=1;
	for(int i=1; i<p; ++i)
		fac[i]=fac[i-1]*i%p;
	inv[p-1]=quickpow(fac[p-1],p-2,p);
	for(int i=p-2; i>=0; --i)
		inv[i]=inv[i+1]*(i+1)%p;
//	printf(" %d\n",C(5,3,p));
	ll ans=0;
	for(int i=1; i*i<=n; ++i)
		if(n%i==0)
		{
			(ans+=Lucas(n,i,p))%=p;
//			printf("%d ",Lucas(n,i,p));
			if(i*i!=n)
			{
				(ans+=Lucas(n,n/i,p))%=p;
//				printf("%d ",Lucas(n,n/i,p));
			}
		}
//	putchar('\n');
	return ans;
}
signed main()
{
	read(n,g);
	if(g%mod==0)
	{
		printf("0\n");
		return 0;
	}
	ll res=0;
//	for(int i=0; i<4; ++i)
//		printf("%lld\n",solve(needmod[i]));
//	putchar('\n');
	for(int i=0; i<4; ++i)
	{
		ll m=(mod-1)/needmod[i];
		(res+=solve(needmod[i])*m%(mod-1)*quickpow(m,needmod[i]-2,needmod[i])%(mod-1))%=(mod-1);
	}
	printf("%lld\n",quickpow(g,res,mod));
	return 0;
}


