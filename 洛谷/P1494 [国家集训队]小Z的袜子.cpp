#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <vector>
#define re register
#define ll long long
#define ull unsigned long long
#define rep(i,a,b) for(re int i=a;i<=b;++i)
#define per(i,a,b) for(re int i=a;i>=b;--i)
using namespace std;
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
inline ll gcd(ll m,ll n)
{
	return n==0ll?m:gcd(n,m%n);
}
const int N=5e4+5;
int n,m,a[N];
int block,belong[N];
struct Queue
{
	int l,r,id;
	inline bool operator <(const Queue&rhs)const
	{
		return belong[l]==belong[rhs.l]?r<rhs.r:belong[l]<belong[rhs.l];
	}
} q[N];
int cnt[N];
ll ans;
inline void add(int pos)
{
	ans+=2*cnt[a[pos]]+1;
	++cnt[a[pos]];
}
inline void del(int pos)
{
	ans+=-2*cnt[a[pos]]+1;
	--cnt[a[pos]];
}
pair<ll,ll>answer[N];
signed main()
{
	read(n,m);
	block=(int)sqrt(n);
//	printf("%d\n",n);
	for(re int i=1; i<=n; ++i)
	{
		read(a[i]);
//		printf(" %d\n",i);
		belong[i]=(i-1)/block+1;
	}
	for(re int i=1; i<=m; ++i)
	{
		read(q[i].l,q[i].r);
		q[i].id=i;
	}
	sort(q+1,q+1+m);
	int l=1,r=0;
	for(re int i=1; i<=m; ++i)
	{
		const int &ql=q[i].l,&qr=q[i].r;
		while(ql<l)
			add(--l);
		while(ql>l)
			del(l++);
		while(qr<r)
			del(r--);
		while(qr>r)
			add(++r);
		if(l==r)
		{
			answer[q[i].id]=make_pair(0,1);
			continue;
		}
		int len=r-l+1;
		ll now=ans-len,sum=1ll*len*(len-1),g=gcd(sum,now);
//		printf(" %d:%lld/%lld\n",q[i].id,now,sum);
		answer[q[i].id]=make_pair(now/g,sum/g);
	}
	for(re int i=1; i<=m; ++i)
		printf("%lld/%lld\n",answer[i].first,answer[i].second);
	return 0;
}

