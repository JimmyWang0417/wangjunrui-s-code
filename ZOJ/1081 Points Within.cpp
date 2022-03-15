#include <cstdio>
#include <iostream>
#include <cmath>
#define lowbit(x) ((x)&(-(x)))
#define re register
#define ll long long
#define ull unsigned long long
#define rep(i,a,b) for(re int i=a;i<=b;++i)
#define per(i,a,b) for(re int i=a;i>=b;--i)
#define eps (1e-10)
template<typename T>
inline void clear(T*array,int l,int r,int val)
{
	memset(&array[l],val,sizeof(T)*(r-l+1));
}
using namespace std;
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
	inline double operator *(const Point &rhs)const
	{
		return x*rhs.y-rhs.x*y;
	}
	inline double operator ^(const Point &rhs)const
	{
		return x*rhs.x+y*rhs.y;
	}
	inline Point operator *(const double &rhs)const
	{
		return Point(x*rhs,y*rhs);
	}
};
struct Line
{
	Point x,y;
	Line(Point _x=Point(),Point _y=Point()):x(_x),y(_y) {}
};
inline bool check(Line line,Point p)
{
	if(fabs((line.x-p)*(line.y-p))>eps)
		return false;
	return ((line.x-p)^(line.y-p))<=0;
}
const int N=105;
Point p[N];
int n,m;
inline bool inner(const Point &q)
{
	int cnt=0;
	for(int i=1; i<=n; ++i)
	{
		Point x=p[i],y=p[i%n+1];
		if(check(Line(x,y),q))
			return true;
		double d1=x.y-q.y,d2=y.y-q.y,ans=(x-q)*(y-q);
		if((ans>=0&&d1<0&&d2>=0)||(ans<=0&&d1>=0&&d2<0))
			++cnt;
	}
	return cnt&1;
}
signed main()
{
	int kase=0;
	ios::sync_with_stdio(false);
	while(cin>>n&&n)
	{
		if(kase)
			putchar('\n');
		printf("Problem %d:\n",++kase);
		cin>>m;
		for(int i=1; i<=n; ++i)
			cin>>p[i].x>>p[i].y;
		for(int i=1; i<=m; ++i)
		{
			Point x;
			cin>>x.x>>x.y;
			puts(inner(x)?"Within":"Outside");
		}
	}
	return 0;
}


