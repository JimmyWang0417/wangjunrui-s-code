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
const int N=4100;
const int mod=998244353;
inline void add(int &x,int y)
{
	x+=y;
	if(x>=mod)
		x-=mod;
}
int n,m,S,a[N];
int f[N][N],g[N][N],sum[N];
signed main()
{
	read(n,m,S);
	for(int i=1; i<=n; ++i)
		read(a[i]);
	int ans=n;
	for(int i=1; i<=n; ++i)
	{
		for(int j=1; j<i; ++j)
		{
			f[i][j]=(sum[j]+1-g[j-1][a[i]^a[j]]+mod)%mod;
			add(g[i][S^a[i]^a[j]],f[i][j]);
			add(sum[i],f[i][j]);
			add(ans,f[i][j]);
		}
		for(int j=0; j<(1<<m); ++j)
			g[i+1][j]=g[i][j];
	}
	printf("%d\n",(ans+mod)%mod);
	return 0;
}
