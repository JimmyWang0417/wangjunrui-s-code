#include <cmath>
#include <cstdio>
#include <bitset>
#include <cstring>
#include <algorithm>
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
const int N=1e5+5,M=2e6+5;
int n,m,k,a[N];
int block,belong[N];
struct Queue
{
	int l,r,id;
	inline bool operator <(const Queue &rhs)const
	{
		return belong[l]==belong[rhs.l]?r<rhs.r:belong[l]<belong[rhs.l];
	}
} q[N];
int cnt[M];
ll ans,answer[N];
inline void add(int val)
{
	ans+=cnt[val^k];
	++cnt[val];
}
inline void del(int val)
{
	--cnt[val];
	ans-=cnt[val^k];
}
signed main()
{
	read(n,m,k);
	block=(int)sqrt(n+1);
	for(re int i=1; i<=n; ++i)
	{
		read(a[i]);
		a[i]^=a[i-1];
	}
	for(re int i=0; i<=n; ++i)
		belong[i]=i/block+1;
	for(re int i=1; i<=m; ++i)
	{
		read(q[i].l,q[i].r);
		--q[i].l;
		q[i].id=i;
	}
	sort(q+1,q+1+m);
	int l=0,r=-1;
	for(re int i=1; i<=m; ++i)
	{
		const int &ql=q[i].l,&qr=q[i].r;
		while(ql<l)
			add(a[--l]);
		while(ql>l)
			del(a[l++]);
		while(qr<r)
			del(a[r--]);
		while(qr>r)
			add(a[++r]);
		answer[q[i].id]=ans;
	}
	for(re int i=1; i<=m; ++i)
		printf("%lld\n",answer[i]);
	return 0;
}
