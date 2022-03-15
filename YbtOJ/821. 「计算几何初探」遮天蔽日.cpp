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
#define eps 1e-10
const int N=35;
const double pi=acos(-1);
struct Point
{
	double x,y;
	Point(double _x=0,double _y=0):x(_x),y(_y) {}
	inline Point operator +(const Point rhs)const
	{
		return Point(x+rhs.x,y+rhs.y);
	}
	inline Point operator -(const Point rhs)const
	{
		return Point(x-rhs.x,y-rhs.y);
	}
	inline Point operator *(const double k)const
	{
		return Point(x*k,y*k);
	}
	inline Point operator /(const double k)const
	{
		return Point(x/k,y/k);
	}
	inline double operator *(const Point rhs)const
	{
		return x*rhs.y-y*rhs.x;
	}
	inline Point rotate(const double alpha)const
	{
		double cosa=cos(alpha),sina=sin(alpha);
		return Point(x*cosa-y*sina,x*sina+y*cosa);
	}
	inline double operator ^(const Point &rhs)const
	{
		return x*rhs.x+y*rhs.y;
	}
	inline double norm()const
	{
		return sqrt(x*x+y*y);
	}
	inline bool operator <(const Point &rhs)const
	{
		return (*this)*rhs>0;
	}
} a[N],b[N],G,sun,o;
double R;
int n;
inline double area()
{
	double ans=0;
	for(int i=1; i<=n; ++i)
		ans+=a[i]*a[i+1];
	return ans/2;
}
inline bool iscross(Point a, Point b, Point c, Point d) // ?§Ø???? ab ?? cd?????
{
	if (min(a.x, b.x) - max(c.x, d.x) > eps || min(c.x, d.x) - max(a.x, b.x) >
	        eps)
		return false;
	if (min(a.y, b.y) - max(c.y, d.y) > eps || min(c.y, d.y) - max(a.y, b.y) >
	        eps)
		return false;
	if (((d - a) * (b - a)) * ((c - a) * (b - a)) > eps)
		return false;
	if (((d - c) * (a - c)) * ((d - c) * (b - c)) > eps)
		return false;
	return true;
}
double t1,t2,t;
int m;
inline void init()
{
	for(int i=1; i<=n; ++i)
	{
		double s=a[i]*a[i+1]/2;
		G=G+(a[i]+a[i+1])*s/3;
	}
	G=G/area();
	double alpha=asin(R/o.norm());
	b[1]=o.rotate(alpha)*cos(alpha);
	b[2]=o.rotate(-alpha)*cos(alpha);
	m=2;
}
inline Point getcross(Point a)
{
	double d=o*a/a.norm();
	double alpha=acos(d/R);
	if(d>=0)
		return a.rotate(pi/2+alpha)/a.norm()*R+o;
	else
		return a.rotate(-pi/2-alpha)/a.norm()*R+o;
}
inline double calc(const Point rhsa,const Point rhsb)
{
//	printf("%lf\n",(rhsa-o)^(rhsb-o));
	double alpha=acos(((rhsa-o)^(rhsb-o))/R/R);
	return fabs(alpha*R);
}
inline bool check(const Point rhsa,const Point rhsb)
{
	for(int i=1; i<=n; ++i)
	{
		if(iscross(Point(0,0),rhsa,a[i],a[i+1])&&iscross(Point(0,0),rhsb,a[i],a[i+1]))
			return false;
	}
	return true;
}
signed main()
{
	freopen("blot.in","r",stdin),freopen("blot.out","w",stdout);
	ios::sync_with_stdio(false);
	cin>>sun.x>>sun.y>>o.x>>o.y>>R;
	cin>>n>>t1>>t2>>t;
	o=o-sun;
	for(int i=1; i<=n; ++i)
	{
		cin>>a[i].x>>a[i].y;
		a[i]=a[i]-sun;
	}
	if(area()<0)
		reverse(a+1,a+1+n);
	a[n+1]=a[1];
	init();
	t1=t/t1*2*pi;
	t2=t/t2*2*pi;
//	printf("%lf\n",t2);
	for(int i=1; i<=n; ++i)
	{
		a[i]=a[i]-G;
//		printf("(%lf,%lf)\n",a[i].x,a[i].y);
		a[i]=a[i].rotate(t2);
	}
//	printf("(%lf,%lf)\n",G.x,G.y);
	G=(G-o).rotate(t1)+o;
	for(int i=1; i<=n; ++i)
		a[i]=a[i]+G;
//	for(int i=1; i<=n; ++i)
//		printf("(%lf,%lf)\n",a[i].x,a[i].y);
	a[n+1]=a[1];
	for(int i=1; i<=n; ++i)
	{
		if((a[i]*b[1])*(a[i]*b[2])<=0&&a[i].norm()<=b[1].norm())
			b[++m]=getcross(a[i]);
	}
//	for(int i=1; i<=n; ++i)
//		printf("(%lf,%lf)\n",a[i].x,a[i].y);
	sort(b+1,b+1+m);
//	for(int i=1; i<=m; ++i)
//		printf("(%lf,%lf)\n",b[i].x,b[i].y);
//	printf("%d\n",check(b[2],b[3]));
	double ans=0;
	for(int i=1; i<m; ++i)
		if(check(b[i],b[i+1]))
		{
//			printf("%d\n",i);
			ans+=calc(b[i],b[i+1]);
		}
	printf("%.2lf\n",ans);
	return 0;
}

