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
const int N=35;
ll cnt[N][N];
int dp[N][N];
using std::cin;
using std::getline;
inline void work()
{
	std::string str1,str2;
	getline(cin,str1),getline(cin,str2);
	int n=str1.length(),m=str2.length();
	memset(cnt,0,sizeof(cnt));
	memset(dp,0x3f3f3f3f,sizeof(dp));
	dp[0][0]=0;
	cnt[0][0]=1;
	for(re int i=0; i<=n; ++i)
		for(re int j=0; j<=m; ++j)
		{
			if(i==n&&j==m)
				continue;
			if(str1[i]==str2[j])
			{
				if(dp[i+1][j+1]>dp[i][j]+1)
				{
					dp[i+1][j+1]=dp[i][j]+1;
					cnt[i+1][j+1]=cnt[i][j];
				}
				else if(dp[i+1][j+1]==dp[i][j]+1)
					cnt[i+1][j+1]+=cnt[i][j];
				continue;
			}
			if(i<n)
			{
				if(dp[i+1][j]>dp[i][j]+1)
				{
					dp[i+1][j]=dp[i][j]+1;
					cnt[i+1][j]=cnt[i][j];
				}
				else if(dp[i+1][j]==dp[i][j]+1)
					cnt[i+1][j]+=cnt[i][j];
			}
			if(j<m)
			{
				if(dp[i][j+1]>dp[i][j]+1)
				{
					dp[i][j+1]=dp[i][j]+1;
					cnt[i][j+1]=cnt[i][j];
				}
				else if(dp[i][j+1]==dp[i][j]+1)
					cnt[i][j+1]+=cnt[i][j];
			}
		}
	printf("%d %lld\n",dp[n][m],cnt[n][m]);
}
signed main()
{
	int T;
	scanf("%d\n",&T);
	for(re int i=1; i<=T; ++i)
	{
		printf("Case #%d: ",i);
		work();
	}
	return 0;
}
