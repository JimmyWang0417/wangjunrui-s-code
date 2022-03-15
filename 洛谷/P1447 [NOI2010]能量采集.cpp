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
const int N=1e5+5;
int prime[N],tot;
int mul[N];
std::bitset<N>vis;
inline void getmul(int n)
{
	mul[1]=1;
	for(int i=2; i<=n; ++i)
	{
		if(!vis[i])
		{
			prime[++tot]=i;
			mul[i]=-1;
		}
		for(int j=1; j<=tot; ++j)
		{
			if(prime[j]*i>n)
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
		mul[i]+=mul[i-1];
	}
}
inline ll getans(int n,int m)
{
	ll ans=0;
	for(int l=1,r; l<=n&&l<=m; l=r+1)
	{
		r=std::min(n/(n/l),m/(m/l));
		ans+=(ll)(n/l)*(m/l)*(mul[r]-mul[l-1]);
	}
	return ans;
}
signed main()
{
	getmul(N-5);
	int n,m;
	read(n,m);
	ll ans=0;
	for(int i=1; i<=n&&i<=m; ++i)
		ans+=i*getans(n/i,m/i);
	printf("%lld\n",ans*2-(ll)n*m);
	return 0;
}
