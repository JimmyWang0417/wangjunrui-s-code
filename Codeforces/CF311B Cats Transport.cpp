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
const int N=1e5+5,P=105;
int n,m,p;
ll a[N];
ll d[N],sum[N];
int q[N];
ll dp[P][N];
#define g(x) (dp[now-1][x]+sum[x])
signed main()
{
	read(n,m,p);
	for(int i=2; i<=n; ++i)
	{
		read(d[i]);
		d[i]+=d[i-1];
	}
	for(int i=1; i<=m; ++i)
	{
		int h,t;
		read(h,t);
		a[i]=t-d[h];
	}
	sort(a+1,a+1+m);
	for(int i=1; i<=m; ++i)
		sum[i]=sum[i-1]+a[i];
	memset(dp,0x3f,sizeof(dp));
	dp[0][0]=0;
	for(int now=1; now<=p; ++now)
	{
		int head=1,tail=1;
		q[1]=0;
		for(int i=1; i<=m; ++i)
		{
			while(head<tail&&g(q[head+1])-g(q[head])<=(q[head+1]-q[head])*a[i])
				++head;
			dp[now][i]=dp[now-1][q[head]]+a[i]*(i-q[head])-(sum[i]-sum[q[head]]);
			while(head<tail&&((g(q[tail])-g(q[tail-1]))*(i-q[tail]))>=((g(i)-g(q[tail]))*(q[tail]-q[tail-1])))
				--tail;
			q[++tail]=i;
		}
	}
	cout<<dp[p][m];
	return 0;
}


