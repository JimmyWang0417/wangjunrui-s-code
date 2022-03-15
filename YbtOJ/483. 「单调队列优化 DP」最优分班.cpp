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
const int M=1e4+5,N=205;
int a[M],g[N];
ll sum[M];
ll dp[N][M];
int f[N][M];
int q[M];
inline void work()
{
	int m,n,A,B;
	read(m,n,A,B);
	int average=0;
	for(int i=1; i<=m; ++i)
	{
		read(a[i]);
		average+=a[i];
	}
	average/=m;
	for(int i=1; i<=m; ++i)
		sum[i]=sum[i-1]+(ll)(a[i]-average)*(a[i]-average);
	for(int i=1; i<=n; ++i)
		read(g[i]);
	memset(dp,0x3f,sizeof(dp));
//	memset(f,0,sizeof(f));
	dp[0][0]=0;
	for(int j=1; j<=n; ++j)
	{
		int head=1,tail=0;
//		for(int i=1; i<=A; ++i)
//			while(head<=tail&&dp[j-1][q[tail]]-sum[q[tail]]*g[j]>=dp[j-1][i-A]-sum[i-A]*g[j])
//				--tail;
		for(int i=1; i<=m; ++i)
		{
			while(head<=tail&&q[head]<i-B)
				++head;
			if(i>=A)
			{
				while(head<=tail&&dp[j-1][q[tail]]-sum[q[tail]]*g[j]>=dp[j-1][i-A]-sum[i-A]*g[j])
					--tail;
				q[++tail]=i-A;
			}
			if(head<=tail)
			{
				dp[j][i]=dp[j-1][q[head]]+(sum[i]-sum[q[head]])*g[j];
				f[j][i]=q[head];
			}
		}
	}
	int pos=1;
	for(int i=2; i<=n; ++i)
		if(dp[i][m]<dp[pos][m])
			pos=i;
	printf("%lld %d %d\n",dp[pos][m],pos,m-f[pos][m]);
}
signed main()
{
	freopen("divide.in","r",stdin),freopen("divide.out","w",stdout);
	int T;
	read(T);
	while(T--)
		work();
	return 0;
}


