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
const int N=1e5+5;
int n;
ll sum[N];
int a,b,c,d,minn,maxx;
char str[N];
struct node
{
	int a[26];
	inline node operator +(const node &rhs)const
	{
		node ans;
		for(int i=0; i<26; ++i)
			ans.a[i]=rhs.a[i]+a[i];
		return ans;
	}
	inline node operator -(const node &rhs)const
	{
		node ans;
		for(int i=0; i<26; ++i)
			ans.a[i]=a[i]-rhs.a[i];
		return ans;
	}
	inline int calc()
	{
		int ans=0;
		for(int i=0; i<26; ++i)
			ans=max(ans,a[i]);
		return ans;
	}
} cnt[N];
ll dp[N];
int p[N],q[N];
signed main()
{
	freopen("string.in","r",stdin),freopen("string.out","w",stdout);
	read(n,a,b,c,d,minn,maxx);
	scanf("%s",str+1);
	for(int i=1; i<=n; ++i)
	{
		cnt[i]=cnt[i-1];
		++cnt[i].a[str[i]-'a'];
	}
	for(int i=1; i<=n; ++i)
	{
		int x;
		read(x);
		sum[i]=sum[i-1]+x;
	}
	int head=1,tail=1,l=0,r=-1,h=1,t=1;
	p[1]=q[1]=0;
	for(int i=1; i<=n; ++i)
	{
#define g(x) (dp[x]+a*sum[x]*sum[x])
		while(head<tail&&(g(q[head+1])-g(q[head]))<=(sum[q[head+1]]-sum[q[head]])*2*a*sum[i])
			++head;
		dp[i]=dp[q[head]]+a*(sum[i]-sum[q[head]])*(sum[i]-sum[q[head]])+b;
#undef g

#define g(x) (dp[x]-c*sum[x])
		while(r<i&&(cnt[i]-cnt[r+1]).calc()>=minn)
		{
			++r;
			while(h<=t&&g(r)<=g(p[t]))
				--t;
			p[++t]=r;
		}
		while(l<=r&&(cnt[i]-cnt[l]).calc()>maxx)
		{
			++l;
			while(h<=t&&p[h]<l)
				++h;
		}
		if(l<=r)
			dp[i]=min(dp[i],dp[p[h]]+c*(sum[i]-sum[p[h]])+d);
#undef g

#define g(x) (dp[x]+a*sum[x]*sum[x])
		while(head<tail&&(g(q[tail])-g(q[tail-1]))*(sum[i]-sum[q[tail]])>=(g(i)-g(q[tail]))*(sum[q[tail]]-sum[q[tail-1]]))
			--tail;
		q[++tail]=i;
#undef g
	}
	for(int i=1; i<=n; ++i)
		printf("%lld\n",dp[i]);
	return 0;
}


