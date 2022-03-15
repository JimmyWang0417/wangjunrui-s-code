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
const int N=1e6+5;
int prime[N],tot,phi[N];
ll sum[N];
bitset<N>vis;
inline void getprime(int n)
{
	sum[1]=phi[1]=1;
	for(int i=2; i<=n; ++i)
	{
		if(!vis[i])
		{
			phi[i]=i-1;
			prime[++tot]=i;
		}
		for(int j=1; j<=tot; ++j)
		{
			if(prime[j]*i>n)
				break;
			vis.set(i*prime[j]);
			if(i%prime[j]==0)
			{
				phi[i*prime[j]]=phi[i]*prime[j];
				break;
			}
			phi[i*prime[j]]=phi[i]*(prime[j]-1);
		}
		sum[i]=sum[i-1]+phi[i];
	}
//	for(int i=1; i<=n; ++i)
//		printf("%d ",phi[i]);
//	putchar('\n');
}
inline void work()
{
}
signed main()
{
	getprime(1e6);
	int T;
	read(T);
	for(int i=1;i<=T;++i)
	{
		int n;
		read(n);
		printf("Case %d: %lld\n",i,(ll)n*(n+1)/2-sum[n]);
	}
	return 0;
}


