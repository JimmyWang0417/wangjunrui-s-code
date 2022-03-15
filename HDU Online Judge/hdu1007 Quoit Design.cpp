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
const int N=1e5+5;
struct Point
{
	double x,y;
	inline bool operator <(const Point &rhs)const
	{
		return y<rhs.y;
	}
} a[N],b[N];
inline bool cmp(Point x,Point y)
{
	return x.x<y.x;
}
using std::sort;
using std::min;
using std::cin;
inline double calc(Point x,Point y)
{
	return sqrt((x.x-y.x)*(x.x-y.x)+(x.y-y.y)*(x.y-y.y));
}
inline double dfs(int l,int r)
{
	if(l==r)
		return 1e18;
	int mid=(l+r)>>1;
	double d=min(dfs(l,mid),dfs(mid+1,r));
	int top=0;
	for(re int i=l; i<=r; ++i)
		if(fabs(a[i].x-a[mid].x)<d)
			b[++top]=a[i];
	sort(b+1,b+1+top);
	for(re int i=1; i<=top; ++i)
		for(re int j=i+1; j<=top&&b[j].y-b[i].y<d; ++j)
			d=min(d,calc(b[i],b[j]));
	return d;
}
	int n;
inline void work()
{
	for(re int i=1; i<=n; ++i)
		cin>>a[i].x>>a[i].y;
	sort(a+1,a+1+n,cmp);
	printf("%.2lf\n",dfs(1,n)/2);
}
signed main()
{
	std::ios::sync_with_stdio(false);
	while(cin>>n,n)
		work();
	return 0;
}


