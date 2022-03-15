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
const int N=20005;
int n,d[N],w[N];
int cnt[N],dis[N];
ll sum;
int q[N],head=1,tail;
#define g(x) (ll)cnt[x]*dis[x]
signed main()
{
	read(n);
	for(int i=1; i<=n; ++i)
		read(w[i],d[i]);
	for(int i=n; i>=1; --i)
		dis[i]=dis[i+1]+d[i];
	for(int i=1; i<=n; ++i)
	{
		sum+=(ll)w[i]*dis[i];
		cnt[i]=cnt[i-1]+w[i];
	}
	ll ans=0;
	for(int i=1; i<=n; ++i)
	{
		while(head<tail&&(g(q[head+1])-g(q[head]))>=(cnt[q[head+1]]-cnt[q[head]])*dis[i])
			++head;
		if(head<=tail)
			ans=max(ans,(ll)cnt[q[head]]*dis[q[head]]+(ll)(cnt[i]-cnt[q[head]])*dis[i]);
//		printf("q[%d]=%d %d\n",head,q[head],i);
		while(head<tail&&(g(q[tail])-g(q[tail-1]))*(cnt[i]-cnt[q[tail]])<=(g(i)-g(q[tail]))*(cnt[q[tail]]-cnt[q[tail-1]]))
			--tail;
		q[++tail]=i;
	}
	printf("%lld\n",sum-ans);
	return 0;
}


