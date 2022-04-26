#include <bits/stdc++.h>
#define int ll
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
const int N=50004,mod=1e9+7;
int prime[N],tot,mul[N];
bitset<N>vis;
inline void getprime(int n)
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
			vis.set(prime[j]*i);
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
inline ll solve(int n,int m)
{
	ll ans=0;
	for(int l=1,r; l<=n&&l<=m; l=r+1)
	{
		r=min(n/(n/l),m/(m/l));
		ans+=(ll)(n/l)*(m/l)*(mul[r]-mul[l-1]);
	}
	return ans;
}
inline int calc(int n)
{
	return n*(n+1)/2;
}
inline int work(int n,int m)
{
	ll ans=0;
	for(int l=1,r=0; l<=n&&l<=m; l=r+1)
	{
		r=min(n/(n/l),m/(m/l));
		ans+=(calc(r)-calc(l-1)+mod)*solve(n/l,m/l);
	}
	return ans;
}
signed main()
{
	getprime(50000);
	int T,n,m;
	read(T,n,m);
	while(T--)
	{
		int i1,j1,i2,j2;
		read(i1,j1,i2,j2);
		cout<<(work(i2,j2)-work(i1-1,j2)-work(i2,j1-1)+work(i1-1,j1-1))%mod<<endl;
	}
	return 0;
}


