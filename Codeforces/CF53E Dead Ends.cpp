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
const int N=15;
int n,m,k;
int g[N][N];
int dp[(1<<10)+5][(1<<10)+5];
signed main()
{
	read(n,m,k);
	for(int i=1; i<=m; ++i)
	{
		int x,y;
		read(x,y);
		--x,--y;
		g[x][y]=g[y][x]=true;
	}
	for(int i=1; i<n; ++i)
		if(g[0][i])
			dp[1|(1<<i)][1|(1<<i)]=1;
	for(int S=3; S<(1<<n); ++S)
		for(int T=S; T; T=(T-1)&S)
			if(dp[S][T])
			{
//				printf("dp[%d][%d]=%d\n",S,T,dp[S][T]);
				for(int i=0; i<n; ++i)
					if((S>>i)&1)
					{
						for(int j=0; j<n; ++j)
							if(!((S>>j)&1)&&g[i][j])
							{
								int now=(T&(~(1<<i)))|(1<<j);
//								printf("%d %d %d %d\n",i,j,now,(now>>(j+1))&1);
								if(!(now>>(j+1)))
									dp[S|(1<<j)][now]+=dp[S][T];
							}
					}
			}
	int ans=0;
	for(int S=0; S<(1<<n); ++S)
	{
		int cnt=0;
		for(int i=0; i<n; ++i)
			if((S>>i)&1)
				++cnt;
		if(cnt==k)
			ans+=dp[(1<<n)-1][S];
	}
	printf("%d\n",ans);
	return 0;
}


