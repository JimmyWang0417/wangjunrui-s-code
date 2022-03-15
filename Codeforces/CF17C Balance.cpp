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
const int N=155,M=55;
const int mod=51123987;
int n,dp[N][M][M][M];
int nxt[N][26];
char str[N];
signed main()
{
	read(n);
	scanf("%s",str+1);
	nxt[n+1][0]=nxt[n+1][1]=nxt[n+1][2]=n+1;
	for(int i=n; i>=1; --i)
	{
		for(int j=0; j<3; ++j)
			nxt[i][j]=nxt[i+1][j];
		nxt[i][str[i]-'a']=i;
	}
	int ans=0;
	dp[1][0][0][0]=1;
	for(int i=1; i<=n; ++i)
		for(int j=0; j<=(n+2)/3; ++j)
			for(int k=0; k<=(n+2)/3&&j+k<=n; ++k)
				for(int l=0; l<=(n+2)/3&&j+k+l<=n; ++l)
				{
					if(j+k+l==n&&abs(j-k)<=1&&abs(k-l)<=1&&abs(j-l)<=1)
						(ans+=dp[i][j][k][l])%=mod;
					else
					{
						(dp[nxt[i][0]][j+1][k][l]+=dp[i][j][k][l])%=mod;
						(dp[nxt[i][1]][j][k+1][l]+=dp[i][j][k][l])%=mod;
						(dp[nxt[i][2]][j][k][l+1]+=dp[i][j][k][l])%=mod;
					}
				}
	printf("%d\n",ans);
	return 0;
}


