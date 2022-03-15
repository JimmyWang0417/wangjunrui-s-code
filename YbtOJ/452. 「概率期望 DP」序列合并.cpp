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
const int N=2e3+5;
const int mod=1e9+7;
int p[N][N],q[N][N],g[N][N],f[N][N];
int ans[N];
//p[i][j]表示结束时序列长度为 i、第一个数为 j 的概率（亦可看作是序列长度始终不超过 i，结束时序列仅有一个数 j 的概率）
//q[i][j]表示初始时序列只有一个数 j，结束时序列长度为 i、第一个数为 j 的概率
//g[i][j]表示初始时序列只有一个数 j，结束时序列长度为 i、第一个数为 j 的情况下的期望
//f[i][j]表示初始时序列只有一个数 j，结束时序列长度为 i 的情况下的期望
int n,m,t;
inline int quickpow(int a,int b)
{
	int res=1;
	while(b)
	{
		if(b&1)
			res=res*a%mod;
		a=a*a%mod;
		b>>=1;
	}
	return res;
}
signed main()
{
	freopen("sequence.in","r",stdin),freopen("sequence.out","w",stdout);
	read(n,m,t);
	int lim=min(n+m-1,t);
	int inv=quickpow(m,mod-2);
	for(int i=1; i<=n; ++i)
		for(int j=1; j<=lim; ++j)
		{
			p[i][j]=(p[i][j-1]*p[i-1][j-1]%mod+(j<=m?inv:0))%mod;
			q[i][j]=(1-(j<lim?p[i-1][j]:0)+mod)%mod;
		}
	for(int j=1; j<=lim; ++j)
	{
		g[1][j]=f[1][j]=j;
		ans[1]=(p[1][j]*q[1][j]%mod*g[1][j]%mod+ans[1])%mod;
	}
	for(int i=2; i<=n; ++i)
	{
		for(int j=1; j<=lim; ++j)
		{
			g[i][j]=(j+(ans[i-1]-(j<lim?p[i-1][j]*f[i-1][j]%mod:0)+mod)%mod*quickpow(q[i][j],mod-2)%mod)%mod;
			ans[i]=(p[i][j]*q[i][j]%mod*g[i][j]%mod+ans[i])%mod;
		}
		for(int j=lim; j>=1; --j)
			f[i][j]=(q[i][j]*g[i][j]%mod+(1-q[i][j]+mod)%mod*f[i][j+1]%mod)%mod;
	}
	cout<<ans[n]<<endl;
	return 0;
}


