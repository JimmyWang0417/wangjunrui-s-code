#include <bits/stdc++.h>
#define double long double
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
const int N=2e5+10;
const double INF=1e12,eps=1e-18;
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
	inline double operator ^(const Point &rhs)const//��??y
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
};
struct Line
{
	Point x,y;
	double theta;
	int id;
	Line(Point _x=Point(),Point _y=Point(),int _id=0):x(_x),y(_y),id(_id) {}
	inline friend Point intersection(const Line &rhsx,const Line &rhsy)
	{
		Point a=rhsx.x,b=rhsx.y,c=rhsy.x,d=rhsy.y;
		double s1=(c-a)*(d-a),s2=(d-b)*(c-b);
		Point add=(b-a)*(s1/(s1+s2));
		return a+add;
	}
	inline Point calc()
	{
		return y-x;
	}
	inline bool right(const Point &rhs)
	{
		return (y-x)*(rhs-x)<=0;
	}
	inline bool operator <(const Line &rhs)const
	{
		if(fabs(theta-rhs.theta)>eps)
			return theta<rhs.theta;
		return (y-x)*(rhs.y-x)<0;
	}
} line[N],a[N],q[N];
int n;
inline bool check(Line a,Line b,Line c)
{
	Point p=intersection(a,b);
	return c.calc()*(p-c.x)<0;
}
inline bool check(int val)
{
	int cnt=0;
	a[cnt].theta=-4;
	for(int i=1; i<=n; ++i)
		if(line[i].id<=val&&a[cnt].theta!=line[i].theta)
			a[++cnt]=line[i];
	int head=1,tail=0;
	for(int i=1; i<=cnt; ++i)
	{
		while(head<tail&&check(q[tail-1],q[tail],a[i]))
			--tail;
		while(head<tail&&check(q[head],q[head+1],a[i]))
			++head;
		q[++tail]=a[i];
			printf("%lf %lf %lf %lf %lf %d\n",q[j].x.x,q[j].x.y,q[j].y.x,q[j].y.y,q[j].theta,q[j].id);
	}
	while(head<tail&&check(q[tail-1],q[tail],q[head]))
		--tail;
	while(head<tail&&check(q[head],q[head+1],q[tail]))
		++head;
	return tail-head>1;
}
signed main()
{
	read(n);
	int cnt=0;
	for(int i=1; i<=n; ++i)
	{
		int x,y1,y2;
		read(x,y1,y2);
		line[++cnt]=Line(Point(0,(double)y1/x),Point(1,(double)y1/x-x),i);
		line[++cnt]=Line(Point(1,(double)y2/x-x),Point(0,(double)y2/x),i);
	}
	line[++cnt]=Line(Point(-INF,eps),Point(-eps,eps));
	line[++cnt]=Line(Point(-eps,eps),Point(-eps,INF));
	line[++cnt]=Line(Point(-eps,INF),Point(-INF,INF));
	line[++cnt]=Line(Point(-INF,INF),Point(-INF,eps));
	int l=1,r=n,ans=0,mid;
	n=cnt;
	for(int i=1; i<=n; ++i)
		line[i].theta=atan2(line[i].calc().y,line[i].calc().x);
	sort(line+1,line+1+n);
	while(l<=r)
	{
		mid=(l+r)>>1;
		if(check(mid))
		{
			l=mid+1;
			ans=mid;
		}
		else
			r=mid-1;
	}
	printf("%d\n",ans);
	return 0;
}

