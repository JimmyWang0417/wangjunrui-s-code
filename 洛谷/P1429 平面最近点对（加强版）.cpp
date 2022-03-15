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
inline void clear(T*a,int l,int r,int val)
{
	memset(&a[l],val,sizeof(T)*(r-l+1));
}
const int N=2e5+5;
struct Point
{
	int x,y;
	inline bool operator <(const Point &rhs)const
	{
		return y<rhs.y;
	}
} a[N],st[N];
inline double calc(Point x,Point y)
{
	return sqrt(1ll*(x.x-y.x)*(x.x-y.x)+1ll*(x.y-y.y)*(x.y-y.y));
}
using std::min;
inline bool cmp(Point x,Point y)
{
	return x.x<y.x;
}
inline double dfs(int l,int r)
{
	int mid((l+r)>>1),top=0;
	if(l==r)
		return 1e18;
	double d=min(dfs(l,mid),dfs(mid+1,r));
	for(re int i=mid; i>=l&&a[mid].x-a[i].x<d; --i)
		st[++top]=a[i];
	for(re int i=mid+1; i<=r&&a[i].x-a[mid].x<d; ++i)
		st[++top]=a[i];
	std::sort(st+1,st+1+top);
	for(re int i=1; i<=top; ++i)
		for(re int j=i+1; j<=top&&st[j].y-st[i].y<d; ++j)
			d=min(d,calc(st[i],st[j]));
	return d;
}
signed main()
{
	int n;
	read(n);
	for(re int i=1; i<=n; ++i)
	{
		read(a[i].x,a[i].y);
	}
	std::sort(a+1,a+1+n,cmp);
	printf("%.4lf\n",dfs(1,n));
	return 0;
}

