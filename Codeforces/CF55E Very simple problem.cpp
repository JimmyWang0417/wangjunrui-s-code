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
struct Point
{
	double x,y;
	Point(double _x=0,double _y=0):x(_x),y(_y) {}
	inline Point operator +(const Point &rhs)const
	{
		return Point(x+rhs.x,y+rhs.y);
	}
	inline Point operator -(const Point &rhs)const
	{
		return Point(x-rhs.x,y-rhs.y);
	}
	inline Point operator *(const Point &rhs)const
	{
		return Point(x*rhs.x,y*rhs.y);
	}
	inline double operator ^(const Point &rhs)const
	{
		return x*rhs.y-y*rhs.x;
	}
} a[N];
int n;
inline void work()
{
	Point q;
	cin>>q.x>>q.y;
	for(int i=1; i<=n; ++i)
	{
		if(((a[i]-q)^(a[i+1]-q))>0)
		{
			cout<<"0\n";
			return;
		}
	}
	ll ans=(ll)n*(n-1)*(n-2)/6;
	for(int i=1,j=2; i<=n; ++i)
	{
		while(j<=2*n&&((a[i]-q)^(a[j]-q))<=0)
			++j;
		int now=j-i-1;
		ans-=(ll)(now)*(now-1)/2;
//		printf(" %d %d %d\n",i,j,j-i-1);
	}
//	putchar('\n');
	cout<<ans<<'\n';
}
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin>>n;
	for(int i=1; i<=n; ++i)
	{
		cin>>a[i].x>>a[i].y;
		a[i+n]=a[i];
	}
	int T;
	cin>>T;
	while(T--)
		work();
	cout<<unitbuf;
	return 0;
}


