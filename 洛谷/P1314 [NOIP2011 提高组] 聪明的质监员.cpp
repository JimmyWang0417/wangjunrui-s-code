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
const int N=2e5+5;
int n,m;
ll S,sum[N];
int w[N],v[N];
int cnt[N];
struct node
{
	int l,r;
} a[N];
inline ll calc(int val)
{
	memset(sum,0,sizeof(sum));
	memset(cnt,0,sizeof(cnt));
	for(int i=1; i<=n; ++i)
	{
		sum[i]=sum[i-1];
		cnt[i]=cnt[i-1];
		if(w[i]>=val)
		{
			sum[i]+=v[i];
			++cnt[i];
		}
	}
	ll ans=0;
	for(int i=1; i<=m; ++i)
		ans+=(sum[a[i].r]-sum[a[i].l-1])*(cnt[a[i].r]-cnt[a[i].l-1]);
	return ans;
}
signed main()
{
	read(n,m,S);
	for(int i=1; i<=n; ++i)
		read(w[i],v[i]);
	for(int i=1; i<=m; ++i)
		read(a[i].l,a[i].r);
	int l=0,r=1e9,ans=-1;
	while(l<=r)
	{
		int mid=(l+r)>>1;
		if(calc(mid)>=S)
		{
			ans=mid;
			l=mid+1;
		}
		else
			r=mid-1;
	}
//	printf("%d\n",ans);
	printf("%lld\n",min(abs(calc(ans)-S),abs(calc(ans+1)-S)));
	return 0;
}


