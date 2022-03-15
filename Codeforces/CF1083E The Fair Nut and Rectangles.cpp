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
struct Point
{
	int x,y;
	ll a;
	inline bool operator <(const Point &rhs)
	{
		return x<rhs.x;
	}
};
inline double getslope(int x1,ll y1,int x2,ll y2)
{
	return (double)(y2-y1)/(x2-x1);
}
Point point[N];
int q[N];
int a[N];
ll dp[N];
signed main()
{
	read(n);
	for(int i=1; i<=n; ++i)
		read(point[i].x,point[i].y,point[i].a);
	sort(point+1,point+1+n);
//	for(int i=1; i<=n; ++i)
//		printf("%d %d\n",point[i].x,point[i].y);
	int head=1,tail=1;
	q[1]=0;
	ll ans=0;
	for(int i=1; i<=n; ++i)
	{
		while(head<tail&&getslope(point[q[head]].x,dp[q[head]],point[q[head+1]].x,dp[q[head+1]])>=point[i].y)
			++head;
		dp[i]=dp[q[head]]-(ll)point[q[head]].x*point[i].y+(ll)point[i].x*point[i].y-point[i].a;
//		printf(" %d %lld\n",q[head],dp[i]);
//		printf(" %lld %lld %lld\n",dp[q[head]],(ll)point[q[head]].x*point[i].y,(ll)point[i].x*point[i].y-a[i]);
		ans=max(ans,dp[i]);
		while(head<tail&&getslope(point[q[tail-1]].x,dp[q[tail-1]],point[q[tail]].x,dp[q[tail]])<=getslope(point[q[tail]].x,dp[q[tail]],point[i].x,dp[i]))
			--tail;
		q[++tail]=i;
	}
	printf("%lld\n",ans);
	return 0;
}


