#include <cstdio>
#define re register
#define ll long long
#define ull unsigned ll
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
const int N=505;
int prime[N],tot,phi[N];
bool vis[N];
ull ans[N];
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
			else
				phi[i*prime[j]]=phi[i]*(prime[j]-1);
		}
	}
	for(re int i=1; i<=n; ++i)
		ans[i]=phi[i];
	for(re int i=2; i*i<=n; ++i)
	{
//		printf("%d\n",i);
		ans[i*i]+=1ull*phi[i]*i;
		for(re int j=i+1; i*j<=n; ++j)
			ans[i*j]+=1ull*phi[i]*j+1ull*i*phi[j];
	}
	for(re int i=2; i<=n; ++i)
		ans[i]+=ans[i-1];
}
signed main()
{
	getphi(500);
	int n;
	while(read(n),n)
		printf("%llu\n",ans[n]);
	return 0;
}

