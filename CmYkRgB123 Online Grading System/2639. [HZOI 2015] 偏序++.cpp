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
const int N=4e4+5;
bitset<N>exist[N],now;
int sortflag;
struct node
{
	int a[6],id;
	inline bool operator < (const node &rhs)const
	{
		return a[sortflag]<rhs.a[sortflag];
	}
} a[N];
int n,k;
signed main()
{
	freopen("partial_order_plus.in","r",stdin);
	freopen("partial_order_plus.out","w",stdout);
	read(n,k);
	for(int i=1; i<=n; ++i)
	{
		a[i].id=i;
		exist[i]=now;
		now[i]=true;
	}
	for(int j=0; j<k; ++j)
	{
		for(int i=1; i<=n; ++i)
			read(a[i].a[j]);
	}
	for(int kase=0; kase<k; ++kase)
	{
		sortflag=kase;
		sort(a+1,a+1+n);
		now.reset();
		for(int i=1; i<=n; ++i)
		{
			exist[a[i].id]&=now;
			now[a[i].id]=1;
		}
	}
	ll ans=0;
	for(int i=1; i<=n; ++i)
		ans+=exist[i].count();
	printf("%lld\n",ans);
	return 0;
}


