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
const int N=1e7+5;
int prime[N],tot,mul[N];
int sum[N];
bitset<N>vis;
inline void getprime(int n)
{
	mul[1]=1;
	for(re int i=2; i<=n; ++i)
	{
		if(!vis[i])
		{
			prime[++tot]=i;
			mul[i]=-1;
		}
		for(re int j=1; j<=tot; ++j)
		{
			if(i*prime[j]>n)
				break;
			vis.set(i*prime[j]);
			if(i%prime[j])
				mul[i*prime[j]]=-mul[i];
			else
			{
				mul[i*prime[j]]=0;
				break;
			}
		}
	}
	for(re int i=1; i<=tot; ++i)
		for(re int j=1; j*prime[i]<=n; ++j)
			sum[j*prime[i]]+=mul[j];
	for(re int i=1; i<=n; ++i)
		sum[i]+=sum[i-1];
}
inline void work()
{
	int n,m;
	read(n,m);
	ll ans=0;
	for(re int l=1,r; l<=min(n,m); l=r+1)
	{
		r=min(n/(n/l),m/(m/l));
		ans+=(sum[r]-sum[l-1])*(n/l)*(ll)(m/l);
	}
	printf("%lld\n",ans);
}
signed main()
{
	getprime(1e7);
	int T;
	read(T);
	while(T--)
		work();
	return 0;
}


