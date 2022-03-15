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
const int N=3005;
int n,m;
double dp[N][N],p[N][N];
double g[N],ft[N];
double sum1[N],sum2[N];
double now[N];
int pt[N];
inline void calc(int x)
{
	ft[x]+=now[x];
	++pt[x];
	memcpy(g,dp[x],sizeof(dp[x]));
	dp[x][pt[x]-1]=0;
	for(int i=pt[x]; i<=n; ++i)
		dp[x][i]=dp[x][i-1]*(1-p[x][i])+g[i-1]*p[x][i];
//	printf("%d %d:\n",x,pt[x]);
//	for(int i=0; i<=n; ++i)
//		cout<<dp[x][i]<<' ';
//	cout<<endl;
	sum1[x]+=dp[x][n]*pt[x];
	sum2[x]+=dp[x][n];
	now[x]=sum1[x]+(1-sum2[x])*pt[x]-ft[x];
}
signed main()
{
	freopen("coin.in","r",stdin),freopen("coin.out","w",stdout);
	ios::sync_with_stdio(false);
	read(n,m);
	for(int i=1; i<=n; ++i)
		for(int j=1; j<=m; ++j)
		{
			int x;
			read(x);
			p[j][i]=x/1000.0;
		}
	for(int i=1; i<=m; ++i)
	{
		dp[i][0]=1;
		for(int j=1; j<=n; ++j)
			dp[i][j]=dp[i][j-1]*(1.0-p[i][j]);
		sum2[i]=dp[i][n];
		calc(i);
	}
	double ans=0;
	for(int i=1; i<=n; ++i)
	{
		int id=1;
		for(int j=2; j<=m; ++j)
			if(now[id]<now[j])
				id=j;
		ans+=now[id];
		calc(id);
	}
	printf("%.10lf\n",ans);
	return 0;
}


