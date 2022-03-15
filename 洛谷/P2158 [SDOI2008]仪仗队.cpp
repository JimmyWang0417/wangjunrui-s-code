
// Problem : P2158 [SDOI2008]仪仗队
// Contest : Luogu
// URL : https://www.luogu.com.cn/problem/P2158
// Memory Limit : 125 MB
// Time Limit : 1000 ms
// Powered by CP Editor (https://github.com/cpeditor/cpeditor)

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
const int N=4e4+5;
bool vis[N];
int phi[N],tot,prime[N];
inline void getprime(int n)
{
	phi[1]=1;
	for(re int i=2;i<=n;++i)
	{
		if(!vis[i])
		{
			phi[i]=i-1;
			prime[++tot]=i;
		}
		for(re int j=1;j<=tot&&i*prime[j]<=n;++j)
		{
			vis[i*prime[j]]=true;
			if(i%prime[j]==0)
			{
				phi[i*prime[j]]=phi[i]*prime[j];
				break;
			}
			phi[i*prime[j]]=phi[i]*(prime[j]-1);
		}
	}
	// for(re int i=1;i<=n;++i)
		// printf(" %d",phi[i]);
	// putchar('\n');
}
signed main()
{
	int n;
	read(n);
	if(!(--n))
	{
		printf("0\n");
		return 0;
	}
	getprime(n);
	ll ans=0;
	for(re int i=2;i<=n;++i)
		ans+=phi[i];
	printf("%lld\n",ans*2+3);
	return 0;
}

