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
const int N=15,M=(1<<12)+5,NMSL=2005;
int g[N][M],dp[N][M];
int n,m;
struct node
{
	int a[N],max;
	inline void calc()
	{
		max=0;
		for(int i=0; i<n; ++i)
			max=std::max(max,a[i]);
	}
	inline bool operator <(const node &rhs)const
	{
		return max>rhs.max;
	}
	inline void print()
	{
		for(int i=0; i<n; ++i)
			printf("%d ",a[i]);
		putchar('\n');
	}
} a[M];
inline void work()
{
	read(n,m);
	for(int i=0; i<n; ++i)
	{
		for(int j=1; j<=m; ++j)
			read(a[j].a[i]);
	}
	for(int i=1; i<=m; ++i)
		a[i].calc();
	sort(a+1,a+1+m);
	if(m>n)
		m=n;
	for(int S=0; S<(1<<n); ++S)
		for(int i=1; i<=m; ++i)
		{
			int &ans=g[i][S]=0;
			for(int j=0; j<n; ++j)
			{
				int res=0;
				for(int k=0; k<n; ++k)
					if((S>>k)&1)
						res+=a[i].a[(j+k)%n];
				ans=max(ans,res);
			}
		}
	memset(dp,~0x3f,sizeof(dp));
	dp[0][0]=0;
	for(int i=1; i<=m; ++i)
		for(int S=0; S<(1<<n); ++S)
		{
			dp[i][S]=dp[i-1][S];
			for(int G=S; G; G=(G-1)&S)
				dp[i][S]=max(dp[i][S],dp[i-1][S^G]+g[i][G]);
		}
	printf("%d\n",dp[m][(1<<n)-1]);
}
signed main()
{
	int T;
	read(T);
	while(T--)
		work();
	return 0;
}


