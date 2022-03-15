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
using namespace std;
const int N=1e6+5;
struct Point
{
	double x,y;
	Point(double _x=0,double _y=0):x(_x),y(_y) {}
	inline Point operator +(const Point&rhs)const
	{
		return Point(x+rhs.x,y+rhs.y);
	}
	inline Point operator -(const Point &rhs)const
	{
		return Point(x-rhs.x,y-rhs.y);
	}
	inline double operator ^(const Point &rhs)const//¦Ì??y
	{
		return x*rhs.x+y*rhs.y;
	}
	inline double operator *(const Point&rhs)const//2??y
	{
		return x*rhs.y-rhs.x*y;
	}
	inline Point operator *(const double &rhs)const
	{
		return Point(x*rhs,y*rhs);
	}
	inline double norm()const
	{
		return sqrt(x*x+y*y);
	}
};
struct Line
{
	Point x,y;
	Line(Point _x=Point(),Point _y=Point()):x(_x),y(_y) {}
	inline Point calc()
	{
		return y-x;
	}
	inline double norm()
	{
		return calc().norm();
	}
} a[N];
int n;
inline Point intersection(Line x,Line y)
{
	Point a=x.x,b=x.y,c=y.x,d=y.y;
	double s1=(c-a)*(d-a),s2=(d-b)*(c-b);
	return a+(b-a)*(s1/(s1+s2));
}
inline double calc(Line line,Point x)
{
	return (line.x-x)*(line.y-x);
}
inline bool check(Line x)
{
	if(x.norm()<eps)
		return false;
//	printf("\n%lf %lf %lf %lf\n",x.x.x,x.x.y,x.y.x,x.y.y);
	for(int i=1; i<=n; ++i)
	{
		if(calc(x,a[i].x)*calc(x,a[i].y)>eps)
			return false;
//		printf("%lf %lf %lf %lf\n",a[i].x.x,a[i].x.y,a[i].y.x,a[i].y.y);
	}
	return true;
}
inline void work()
{
	cin>>n;
	for(int i=1; i<=n; ++i)
		cin>>a[i].x.x>>a[i].x.y>>a[i].y.x>>a[i].y.y;
	if(n==1)
	{
		puts("Yes!");
		return;
	}
	for(int i=1; i<=n; ++i)
		for(int j=i+1; j<=n; ++j)
		{
			if(check(Line(a[i].x,a[j].x))||check(Line(a[i].x,a[j].y))||
			        check(Line(a[i].y,a[j].x))||check(Line(a[i].y,a[j].y)))
			{
//				printf("%d %d\n",i,j);
				puts("Yes!");
				return;
			}
		}
	puts("No!");
}
signed main()
{
	ios::sync_with_stdio(false);
	int T;
	cin>>T;
	while(T--)
		work();
	return 0;
}


