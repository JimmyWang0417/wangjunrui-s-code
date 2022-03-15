#include <bits/stdc++.h>
#define lowbit(x) ((x)&(-(x)))
#define re register
#define ll long long
#define ull unsigned long long
#define rep(i,a,b) for(re int i=a;i<=b;++i)
#define per(i,a,b) for(re int i=a;i>=b;--i)
#define eps (1e-10)
#define INF (1e18)
template<typename T>
inline void clear(T*array,int l,int r,int val)
{
	memset(&array[l],val,sizeof(T)*(r-l+1));
}
using namespace std;
const int N=1e4+5;
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
		return x*rhs.y-y*rhs.x;
	}
	inline double norm()const
	{
		return sqrt(x*x+y*y);
	}
} point1[N],point2[N];
struct Line
{
	Point x,y;
	Line(Point _x=Point(),Point _y=Point()):x(_x),y(_y) {}
	inline double calc()const
	{
		return (y-x).norm();
	}
};
inline double area(const Point &rhsa,const Point &rhsb,const Point&rhsc)
{
	return abs((rhsa-rhsc)*(rhsb-rhsc));
}
int n,m;
inline double calc1(const Line &a,const Point &b)
{
	if(abs(a.calc())<eps)
		return (a.x-b).norm();
	return min(min((a.x-b).norm(),(a.y-b).norm()),area(a.x,a.y,b)/a.calc());
}
inline double calc2(const Line &a,const Line &b)
{
	return min(min(calc1(a,b.x),calc1(a,b.y)),min(calc1(b,a.x),calc1(b,a.y)));
}
inline double solve(const Point *a,const Point *b,const int &n,const int &m)
{
	int p=1,q=1;
	for(int i=1; i<=n; ++i)
		if(a[i].y<a[p].y)
			p=i;
	for(int i=1; i<=m; ++i)
		if(b[i].y>b[q].y)
			q=i;
	printf("%d %d\n",p,q);
	double answer=INF,ans=-1;
//	a[n+1]=a[1];
//	b[m+1]=b[1];
	for(int i=1; i<=n; ++i)
	{
		while(1)
		{
			ans=area(a[p],a[p+1],b[q+1])-area(a[p],a[p+1],b[q]);
			if(ans>=0)
				break;
			q=q%m+1;
		}
		printf("%d %d\n",p,q);
		answer=min(answer,abs(ans)>eps?calc1(Line(a[p],a[p+1]),b[q]):
		           calc2(Line(a[p],a[p+1]),Line(b[q],b[q+1])));
		p=p%n+1;
	}
	return answer;
}
signed main()
{
	while(cin>>n>>m)
	{
		if(!n&&!m)
			return 0;
		for(int i=1; i<=n; ++i)
			cin>>point1[i].x>>point1[i].y;
		for(int i=1; i<=m; ++i)
			cin>>point2[i].x>>point2[i].y;
		point1[n+1]=point1[1];
		point2[m+1]=point2[1];
		printf("%.5lf\n",solve(point1,point2,n,m));
	}
	return 0;
}


