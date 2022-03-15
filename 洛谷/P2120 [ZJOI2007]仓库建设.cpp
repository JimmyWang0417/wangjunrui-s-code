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
const int N=1e6+5;
int n;
ll dis[N];
ll cnt[N],sum[N];
int c[N];
int q[N];
ll dp[N];
#define g(x) (dp[x]+sum[x])
signed main()
{
	read(n);
	for(int i=1; i<=n; ++i)
	{
		int p;
		read(dis[i],p,c[i]);
		cnt[i]=cnt[i-1]+p;
		sum[i]=sum[i-1]+p*dis[i];
	}
	int head=1,tail=1;
	memset(dp,0x3f,sizeof(dp));
	dp[q[1]=0]=0;
	for(int i=1; i<=n; ++i)
	{
		while(head<tail&&(g(q[head+1])-g(q[head]))<=(cnt[q[head+1]]-cnt[q[head]])*dis[i])
			++head;
		dp[i]=dp[q[head]]+(cnt[i]-cnt[q[head]])*dis[i]-(sum[i]-sum[q[head]])+c[i];
//		printf("%d %d %d\n",head,tail,q[head]);
//		cout<<i<<' '<<dp[i]<<endl<<endl;
		while(head<tail&&(g(q[tail])-g(q[tail-1]))*(cnt[i]-cnt[q[tail]])>=(g(i)-g(q[tail]))*(cnt[q[tail]]-cnt[q[tail-1]]))
			--tail;
		q[++tail]=i;
	}
	printf("%lld\n",dp[n]);
	return 0;
}


