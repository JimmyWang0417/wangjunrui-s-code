#include<bits/stdc++.h>
#define re register
// Definition
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
#define ll long long
#define int ll
const ll MAXN=1e3+51,MOD=998244353,inf=0x3f3f3f3f;
ll cnt,k;
ll x[MAXN],dp[MAXN][MAXN],g[MAXN][MAXN],f[MAXN][MAXN];
signed main()
{
	read(cnt);
	for(re int i=1; i<=cnt; ++i)
		read(x[i]);
	for(re int i=1; i<=cnt; i++)
	{
		dp[i][i]=1,f[i][i]=x[i];
		for(re int j=i+1; j<=cnt; j++)
		{
			dp[i][j]=j-i+1;
		}
	}
	for(re int l=2; l<=cnt; l++)
	{
		for(re int i=1; i+l-1<=cnt; i++)
		{
			k=i+l-1;
			for(re int j=i; j<k; j++)
			{
				if(f[i][j]&&f[j+1][k]&&f[i][j]==f[j+1][k])
				{
					f[i][k]=f[i][j]+1,dp[i][k]=1;
				}
			}
		}
		for(re int i=1; i+l-1<=cnt; i++)
		{
			k=i+l-1;
			for(re int j=i; j<k; j++)
				dp[i][k]=min(dp[i][k],dp[i][j]+dp[j+1][k]);
		}
	}
	printf("%d\n",dp[1][cnt]);
}
