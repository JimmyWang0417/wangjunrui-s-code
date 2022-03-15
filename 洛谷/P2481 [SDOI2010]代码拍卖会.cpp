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
const int mod=999911659;
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
inline ll C(ll n,int m)
{
	ll x=1,y=1;
	for(int i=0; i<m; ++i)
	{
		x=x*((n-i)%mod)%mod;
		y=y*(i+1)%mod;
	}
//	printf("%lld %lld\n",x,y);
	return x*quickpow(y,mod-2)%mod;
}
ll n;
int p;
int vis[505];
ll g[505];
ll dp[505][15][505];
signed main()
{
//	freopen("auction.in","r",stdin);
//	freopen("auction.out","w",stdout);
	read(n,p);
	int now=0;
	int cycle=0,cyclenum=0;
	for(int i=1; i<=p+1&&i<=n; ++i)
	{
		now=(now*10+1)%p;
//		printf("%d\n",now);
		if(!vis[now])
			vis[now]=i;
		else
		{
			cyclenum=vis[now];
			cycle=i-vis[now];
			break;
		}
	}
	if(cycle)
	{
		ll times=(n-(cyclenum-1))/cycle;
		n-=cycle*times+(cyclenum-1);
//		printf("%lld\n",cycle*times+(cyclenum-1));
		now=0;
		for(int i=1; i<cyclenum; ++i)
		{
			now=(now*10+1)%p;
			(++g[now])%=mod;
		}
		for(int i=1; i<=cycle; ++i)
		{
			now=(now*10+1)%p;
			(g[now]+=times)%=mod;
		}
	}
	now=0;
	for(int i=1; i<cyclenum; ++i)
		now=(now*10+1)%p;
//	printf("%d %d\n",now,n);
	if(n==0)
	{
		for(int i=1; i<=cycle; ++i)
			now=(now*10+1)%p;
	}
	else
	{
		for(int i=1; i<=n; ++i)
		{
			now=(now*10+1)%p;
			(++g[now])%=mod;
		}
	}

//	printf("now=%d \n",now);
//	printf("%d %d\n",cycle,cyclenum);
//	for(int i=0; i<p; ++i)
//		printf("%lld ",g[i]);
//	putchar('\n');
//	printf("%d\n",now);
	dp[0][1][now]=1;
	for(int i=0; i<p; ++i)
		for(int j=1; j<=9; ++j)
			for(int s=0; s+j<=9; ++s)
			{
				ll mul=C(g[i]+s-1,s);
				for(int l=0; l<p; ++l)
					(dp[i+1][s+j][(l+s*i)%p]+=dp[i][j][l]*mul%mod)%=mod;
			}
//	for(int i=0; i<=p; ++i)
//		for(int j=1; j<=9; ++j)
//			for(int k=0; k<p; ++k)
//			{
//				if(dp[i][j][k])
//					printf("%d %d %d %lld\n",i,j,k,dp[i][j][k]);
//			}
	ll ans=0;
	for(int i=1; i<=9; ++i)
		(ans+=dp[p][i][0])%=mod;

	printf("%lld\n",ans);
	return 0;
}


