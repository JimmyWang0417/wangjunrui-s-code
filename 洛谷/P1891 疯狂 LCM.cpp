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
const int N=1e6+5;
int prime[N],tot;
int phi[N];
ll ans[N];
std::bitset<N>vis;
inline void getmul(int n)
{
	phi[1]=1;
	for(int i=2; i<=n; ++i)
	{
		if(!vis[i])
		{
			prime[++tot]=i;
			phi[i]=i-1;
		}
		for(int j=1; j<=tot; ++j)
		{
			if(prime[j]*i>n)
				break;
			vis.set(i*prime[j]);
			if(i%prime[j])
				phi[i*prime[j]]=phi[i]*(prime[j]-1);
			else
			{
				phi[i*prime[j]]=phi[i]*prime[j];
				break;
			}
		}
	}
	for(int i=1; i<=n; ++i)
	{
		for(int j=i; j<=n; j+=i)
			ans[j]+=((ll)phi[i]*i+1)/2;
	}
}
signed main()
{
	getmul(N-5);
	int T;
	read(T);
	while(T--)
	{
		int n;
		read(n);
//		for(int i=1; i<=n; ++i)
//			printf("%d ",phi[i]);
//		putchar('\n');
		printf("%lld\n",n*ans[n]);
	}
	return 0;
}


