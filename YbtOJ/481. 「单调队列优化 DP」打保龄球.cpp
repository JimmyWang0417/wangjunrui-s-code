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
const int N=1e4+100+5,K=505;
ll dp[K][N],sum[N];
int a[N];
int q[N],head,tail;
inline void work()
{
	int n,k,w;
	read(n,k,w);
	for(int i=1; i<=n; ++i)
	{
		read(a[i]);
		sum[i]=sum[i-1]+a[i];
	}
	for(int i=n+1; i<=n+w; ++i)
		sum[i]=sum[i-1];
	memset(dp,~0x3f3f3f,sizeof(dp));
	dp[0][0]=0;
	ll ans=0;
	for(int now=1; now<=k; ++now)
	{
		head=1;
		q[tail=1]=0;
		ll maxx=dp[0][1];
		for(int i=1; i<=n+w; ++i)
		{
			if(i>=w)
				maxx=max(maxx,dp[now-1][i-w]);
			while(head<=tail&&q[head]<i-w)
				++head;
			dp[now][i]=max(dp[now-1][q[head]]+sum[i]-sum[q[head]],maxx+sum[i]-sum[i-w]);
			ans=max(dp[now][i],ans);
			while(head<=tail&&dp[now-1][q[tail]]-sum[q[tail]]<=dp[now-1][i]-sum[i])
				--tail;
			q[++tail]=i;
		}
	}
//	for(int now=1; now<=k; ++now)
//		for(int i=1; i<=n+w; ++i)
//			ans=max(ans,dp[now][i]);
	printf("%lld\n",ans);
}
signed main()
{
	freopen("bowling.in","r",stdin),freopen("bowling.out","w",stdout);
	int T;
	read(T);
	while(T--)
		work();
	return 0;
}


