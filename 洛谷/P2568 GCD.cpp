#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cmath>
#define re register
#define ll long long
#define ull unsigned long long
#define rep(i,a,b) for(re int i=a;i<=b;++i)
#define per(i,a,b) for(re int i=a;i>=b;--i)
using namespace std;
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
const int N=1e7+5;
int prime[N],tot,phi[N];
ull ans[N];
bool vis[N];
inline void getphi(int n)
{
	phi[1]=0;
	for(re int i=2; i<=n; ++i)
	{
		if(!vis[i])
		{
			prime[++tot]=i;
			phi[i]=i-1;
		}
		for(re int j=1; j<=tot; ++j)
		{
			if(i*prime[j]>n)
				break;
			vis[i*prime[j]]=true;
			if(i%prime[j]==0)
			{
				phi[i*prime[j]]=phi[i]*prime[j];
				break;
			}
			phi[i*prime[j]]=phi[i]*(prime[j]-1);
		}
	}
	for(re int i=1; i<=n; ++i)
		ans[i]=ans[i-1]+phi[i];
}
ull sum;
int n;
signed main()
{
	read(n);
	getphi(n);
	for(re int i=1; i<=tot; ++i)
		sum+=ans[n/prime[i]];
//		printf("%d %llu\n",prime[i],ans[n/prime[i]]);
	printf("%llu\n",sum*2+tot);
	return 0;
}

