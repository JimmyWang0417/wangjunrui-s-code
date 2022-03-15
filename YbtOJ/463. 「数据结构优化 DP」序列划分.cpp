#include <bits/stdc++.h>
#define int ll
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
const int N=1e5+5;
int n,m;
int a[N],b[N];
int maxa[N];
int minb[N][25];
int Log[N];
inline int query(int x,int y)
{
	int k=Log[y-x+1];
	return min(minb[x][k],minb[y-(1<<k)+1][k]);
}
int sum[N];
multiset<int>s;
int q[N];
int dp[N];
inline bool check(int mid)
{
	s.clear();
	int head=1,tail=1;
	q[head]=0;
	dp[0]=0;
	for(int i=1,le=0; i<=n; ++i)
	{
//		printf("%d\n",i);
		while(head<=tail&&sum[i]-sum[q[head]]>mid)
		{
			if(head<tail)
				s.erase(s.find(dp[q[head]]+a[q[head+1]]));
			++head;
		}
		while(head<=tail&&a[q[tail]]<a[i])
		{
			if(head<tail)
				s.erase(s.find(dp[q[tail-1]]+a[q[tail]]));
			--tail;
		}
		if(head<=tail)
			s.insert(dp[q[tail]]+a[i]);
		q[++tail]=i;
		while(le<i&&sum[i]-sum[le]>mid)
			++le;
		if(le==q[head])
			dp[i]=dp[le]+a[q[head+1]];
		else
			dp[i]=dp[le]+a[q[head]];
		if(head<tail)
			dp[i]=min(dp[i],*s.begin());
	}
	return dp[n]<=m;

}
signed main()
{
	freopen("sequence.in","r",stdin),freopen("sequence.out","w",stdout);
	read(n,m);
	Log[0]=-1;
	for(int i=1; i<=n; ++i)
	{
		read(a[i],b[i]);
		Log[i]=Log[i>>1]+1;
		minb[i][0]=b[i];
	}
	maxa[n]=n;
	for(int i=n-1; i>=1; --i)
		maxa[i]=a[maxa[i+1]]<=a[i]?i:maxa[i+1];
//	for(int i=1; i<=n; ++i)
//		printf("%d ",maxa[i]);
//	putchar('\n');
	for(int j=1; j<=20; ++j)
	{
		for(int i=1; i+(1<<j)-1<=n; ++i)
			minb[i][j]=min(minb[i][j-1],minb[i+(1<<(j-1))][j-1]);
	}
//	for(int i=1; i<=n; ++i)
//	{
//		for(int j=i; j<=n; ++j)
//			printf("[%lld,%lld]=%lld\n",i,j,query(i,j));
//		putchar('\n');
//	}
	int tot=0;
	for(int i=1,j; i<=n;)
	{
		for(j=i; j<n&&a[maxa[j+1]]>=query(i,j); j=maxa[j+1]);
//		printf("[%lld,%lld]\n",i,j);
		b[++tot]=b[i];
		a[tot]=a[i];
		for(i=i+1; i<=j; ++i)
		{
			a[tot]=max(a[tot],a[i]);
			b[tot]+=b[i];
		}
	}
	int l=0,r=0;
	n=tot;
	for(int i=1; i<=n; ++i)
	{
		l=max(l,b[i]);
		sum[i]=sum[i-1]+b[i];
	}
	int ans=r=sum[n];
//	for(int i=1; i<=n; ++i)
//		printf("%lld %lld\n",a[i],b[i]);
	while(l<=r)
	{
		int mid=(l+r)>>1;
		if(check(mid))
		{
			r=mid-1;
			ans=mid;
		}
		else
			l=mid+1;
	}
	printf("%lld\n",ans);
	return 0;
}

