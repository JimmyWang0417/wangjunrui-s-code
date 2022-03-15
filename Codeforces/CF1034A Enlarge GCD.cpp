#include <bits/stdc++.h>
#define lowbit(x) (x&(-x))
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
const int N=3e5+5,M=1.5*1e7+5;
int a[N];
int cnt[M];
inline int gcd(int _m,int _n)
{
	return !_n?_m:gcd(_n,_m%_n);
}
bool vis[M];
int prime[M],tot;
inline void getprime(int n)
{
	for(re int i=2; i<=n; ++i)
	{
		if(!vis[i])
			prime[++tot]=i;
		for(re int j=1; j<=tot; ++j)
		{
			if(i*prime[j]>n)
				break;
			vis[i*prime[j]]=true;
			if(i%prime[j]==0)
				break;
		}
	}
}
int main()
{
	int n;
	int _gcd=0,maxx=0;
	read(n);
	for(re int i=1; i<=n; ++i)
	{
		read(a[i]);
		_gcd=gcd(_gcd,a[i]);
	}
	for(re int i=1; i<=n; ++i)
	{
		a[i]/=_gcd;
		maxx=std::max(maxx,a[i]);
		++cnt[a[i]];
//		printf("%d ",a[i]);
	}
//	putchar('\n');
	getprime(maxx);
//	printf("%d\n",tot);
	int ans=n;
	for(re int i=1; i<=tot; ++i)
	{
		int now=0;
		for(re int j=prime[i]; j<=maxx; j+=prime[i])
			now+=cnt[j];
		if(now==n)
			continue;
		ans=std::min(ans,n-now);
	}
	printf("%d\n",ans==n?-1:ans);
	return 0;
}
