#include <bits/stdc++.h>
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
const int N=1e5+5;
int n;
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
	inline Point operator *(const double &rhs)const
	{
		return Point(x*rhs,y*rhs);
	}
	inline bool operator >(const Point &rhs)const
	{
		return x==rhs.x?y<rhs.y:x<rhs.x;
	}
	inline double norm()
	{
		return x*x+y*y;
	}
} point[N];
inline bool operator <(const Point &rhsx,const Point &rhsy)
{
	double ans=(rhsx-point[1])*(rhsy-point[1]);
	if(fabs(ans)>eps)
		return ans>=0;
	else
		return (rhsx-point[1]).norm()<(rhsy-point[1]).norm();
}
int st[N],top;
signed main()
{
	ios::sync_with_stdio(false);
	cin>>n;
	for(int i=1; i<=n; ++i)
	{
		cin>>point[i].x>>point[i].y;
		if(point[i]>point[1])
			swap(point[i],point[1]);
	}
	sort(point+2,point+1+n);
//	for(int i=1; i<=n; ++i)
//		printf(" %lf %lf\n",point[i].x,point[i].y);
	st[top=1]=1;
	for(int i=2; i<=n; ++i)
	{
		while(top>=2&&(point[st[top-1]]-point[st[top]])*(point[i]-point[st[top]])>=0)
			--top;
		st[++top]=i;
	}
	double len=0;
//	for(int i=1; i<=top; ++i)
//		printf("%d ",st[i]);
//	putchar('\n');
	for(int i=1; i<=top; ++i)
	{
		len+=sqrt((point[st[i]]-point[st[i%top+1]]).norm());
	}
	printf("%.2lf\n",len);
	return 0;
}


