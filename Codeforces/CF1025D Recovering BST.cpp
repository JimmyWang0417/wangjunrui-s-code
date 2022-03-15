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
const int N=705;
bool dp[N][N][2];
bool g[N][N];
int n,a[N];
signed main()
{
	read(n);
	for(int i=1; i<=n; ++i)
		read(a[i]);

	for(int i=1; i<=n; ++i)
		for(int j=i+1; j<=n; ++j)
			g[j][i]=g[i][j]=(__gcd(a[i],a[j])>1);
	for(int i=1; i<=n; ++i)
		g[0][i]=g[i][0]=g[i][n+1]=g[n+1][i]=true;

	for(int i=1; i<n; ++i)
		dp[i][i][1]=dp[i+1][i+1][0]=g[i][i+1];
	for(int i=0; i<=n; ++i)
		dp[i+1][i][0]=dp[i+1][i][1]=true;
	for(int len=2; len<=n; ++len)
	{
		for(int l=1; l+len-1<=n; ++l)
		{
			int r=l+len-1;
			for(int k=l; k<=r; ++k)
			{
				if(g[l-1][k])
					dp[l][r][0]|=dp[l][k-1][1]&dp[k+1][r][0];
				if(g[k][r+1])
					dp[l][r][1]|=dp[l][k-1][1]&dp[k+1][r][0];
			}
		}
	}
	if(dp[1][n][0]|dp[1][n][1])
		printf("Yes\n");
	else
		printf("No\n");
	return 0;
}


