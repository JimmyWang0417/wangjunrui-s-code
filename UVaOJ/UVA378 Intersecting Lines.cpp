#include <cstdio>
#include <cmath>
#include <iostream>
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
	inline Point operator +(const Point&rhs)const
	{
		return Point(x+rhs.x,y+rhs.y);
	}
	inline Point operator -(const Point &rhs)const
	{
		return Point(x-rhs.x,y-rhs.y);
	}
	inline double operator ^(const Point &rhs)const//µã»ý
	{
		return x*rhs.x+y*rhs.y;
	}
	inline double operator *(const Point&rhs)const//²æ»ý
	{
		return x*rhs.y-rhs.x*y;
	}
	inline Point operator *(const double &rhs)const
	{
		return Point(x*rhs,y*rhs);
	}
	inline void get()
	{
		cin>>x>>y;
	}
};
struct Line
{
	Point x,y;
	inline Point calc()
	{
		return Point(y.x-x.x,y.y-x.y);
	}
	inline void get()
	{
		x.get(),y.get();
	}
} ;
inline bool check(Line line,Point x)
{
	return fabs((line.x-x)*(line.y-x))<eps;
}
inline Point intersection(Line x,Line y)
{
	Point a=x.x,b=x.y,c=y.x,d=y.y;
	double s1=(c-a)*(d-a),s2=(d-b)*(c-b);
	Point add=(b-a)*(s1/(s1+s2));
	return a+add;
}
signed main()
{
	ios::sync_with_stdio(false);
	int T;
	cin>>T;
	printf("INTERSECTING LINES OUTPUT\n");
	while(T--)
	{
		Line a,b;
		a.get(),b.get();
		if(fabs(a.calc()*b.calc())<eps)
		{
			if(check(a,b.x))
				printf("LINE\n");
			else
				printf("NONE\n");
		}
		else
		{
			Point ans=intersection(a,b);
			printf("POINT %.2lf %.2lf\n",ans.x,ans.y);
		}
	}
	printf("END OF OUTPUT\n");
	return 0;
}


