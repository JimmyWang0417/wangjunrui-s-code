
// Problem : P3146 [USACO16OPEN]248 G
// Contest : Luogu
// URL : https://www.luogu.com.cn/problem/P3146
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
const int N=250;
int dp[N][N],n;
using std::max;
signed main()
{
	read(n);
	int ans=0;
	for(re int i=1;i<=n;++i)
	{
		read(dp[i][i]);
		ans=max(ans,dp[i][i]);
	}
	for(re int len=2;len<=n;++len)
	{
		for(re int i=1;i+len-1<=n;++i)
		{
			int j=i+len-1;
			for(re int k=i;k<j;++k)
				if(dp[i][k]==dp[k+1][j])
					dp[i][j]=max(dp[i][j],dp[i][k]+1);
			ans=max(ans,dp[i][j]);
		}
	}
	printf("%d\n",ans);
	return 0;
}

