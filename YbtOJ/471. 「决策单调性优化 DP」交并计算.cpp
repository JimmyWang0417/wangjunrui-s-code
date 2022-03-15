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
const int N=1e7+5;
struct node
{
	int l,r;
	inline bool operator <(const node &rhs)const
	{
		return l==rhs.l?r>rhs.r:l<rhs.l;
	}
	inline ll operator +(const node &rhs)const
	{
		return (ll)max((max(r,rhs.r)-min(l,rhs.l)),0)*max((min(r,rhs.r)-max(l,rhs.l)),0);
	}
} a[N],b[N];
int n;
ll ans=0;
inline void solve(int l,int r,int x,int y)
{
	if(l>r)
		return;
	if(l==r)
	{
//		printf("pos=%d [%d,%d]\n",l,x,y);
		for(int i=x; i<l; ++i)
			ans=max(ans,b[i]+b[l]);
		return;
	}
	int mid=(l+r)>>1;
	int pos=x;
	for(int i=x+1; i<=min(mid-1,y); ++i)
		if(b[mid]+b[pos]<b[mid]+b[i])
			pos=i;
	ans=max(ans,b[mid]+b[pos]);
	solve(l,mid-1,x,pos);
	solve(mid+1,r,pos,y);
}
signed main()
{
	freopen("interval.in","r",stdin),freopen("interval.out","w",stdout);
	read(n);
	for(int i=1; i<=n; ++i)
		read(a[i].l,a[i].r);
	sort(a+1,a+1+n);
	int tot=0;
	b[++tot]=a[1];
	for(int i=2; i<=n; ++i)
	{
		if(b[tot].r<a[i].r)
			b[++tot]=a[i];
		else
			ans=max(ans,b[tot]+a[i]);
	}
	solve(1,tot,1,tot);
	printf("%lld\n",ans);
//	cerr<<cnt;
	return 0;
}


