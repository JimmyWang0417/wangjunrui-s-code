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
const int N=3605;
const int mod=998244353;
ll fac[N],inv[N];
inline ll C(int n,int m)
{
	if(n<m)
		return 0;
	return fac[n]*inv[m]%mod*inv[n-m]%mod;
}
inline void add(int &x,int y)
{
	x+=y;
	if(x>=mod)
		x-=mod;
}
bool visx[N],visy[N];
int n,m,k;
int f[N][N],g[N][N];
inline ll quickpow(ll a,int b)
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
signed main()
{
	read(n,m,k);
	for(int i=1; i<=k; ++i)
	{
		int x,y;
		read(x,y);
		visx[x]=visy[y]=true;
		read(x,y);
		visx[x]=visy[y]=true;
	}
	fac[0]=1;
	int cntx=n,cnty=m;
	for(int i=1; i<=n; ++i)
		if(visx[i])
			--cntx;
	for(int i=1; i<=m; ++i)
		if(visy[i])
			--cnty;
	int maxx=max(cntx,cnty);
	f[0][0]=1;
	for(int i=1; i<=n; ++i)
	{
		memcpy(f[i],f[i-1],sizeof(f[i]));
		if(visx[i]||visx[i-1]||i==1)
			continue;
		for(int j=1; j<=cntx; ++j)
			add(f[i][j],f[i-2][j-1]);
	}
	g[0][0]=1;
	for(int i=1; i<=m; ++i)
	{
		memcpy(g[i],g[i-1],sizeof(g[i]));
		if(visy[i]||visy[i-1]||i==1)
			continue;
		for(int j=1; j<=cnty; ++j)
			add(g[i][j],g[i-2][j-1]);
	}
	ll ans=0;
	fac[0]=1;
	for(int i=1; i<=maxx; ++i)
		fac[i]=fac[i-1]*i%mod;
	inv[maxx]=quickpow(fac[maxx],mod-2);
	for(int i=maxx-1; i>=0; --i)
		inv[i]=inv[i+1]*(i+1)%mod;
	for(int i=0; i<=cntx; ++i)
		for(int j=0; j<=cnty&&i*2+j<=cntx&&i+j*2<=cnty; ++j)
			(ans+=(ll)f[n][i]*g[m][j]%mod*C(cntx-2*i,j)%mod*C(cnty-2*j,i)%mod*fac[i]%mod*fac[j]%mod)%=mod;
	printf("%lld\n",ans);
	return 0;
}


