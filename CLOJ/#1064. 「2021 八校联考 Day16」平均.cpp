#include <cstdio>
#include <cstring>
#include <algorithm>
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
const int N=155;
const int mod=998244353;
inline void add(int &x,int y)
{
	x+=y;
	if(x>=mod)
		x-=mod;
}
inline void del(int &x,int y)
{
	x-=y;
	if(x<0)
		x+=mod;
}
int dp[N][1132500+5],sumdp[N];
int n,m,q,k;
int sum[N];
signed main()
{
	read(k);
	dp[0][0]=1;
	for(int i=1; i<=150; ++i)
	{
		sum[i]=sum[i-1]+i*k;
		memset(sumdp,0,sizeof(sumdp));
		for(int j=0; j<=sum[i]; ++j)
		{
			add(sumdp[j%i],dp[i-1][j]);
			if(i*(k+1)<=j)
				del(sumdp[j%i],dp[i-1][j-i*(k+1)]);
			dp[i][j]=sumdp[j%i];
		}
	}
	read(q);
	while(q--)
	{
		read(n,m);
		if(n<m)
			printf("0\n");
		else
		{
			ll ans=0;
			int l=m-1,r=n-m;
			for(re int i=sum[std::min(l,r)]; i>=0; --i)
				(ans+=(ll)dp[l][i]*dp[r][i])%=mod;
			printf("%lld\n",(ans*(k+1)%mod-1+mod)%mod);
		}
	}
	return 0;
}


