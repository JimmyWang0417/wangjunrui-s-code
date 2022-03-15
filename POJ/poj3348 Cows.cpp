#include <iostream>
#include <cmath>
#include <algorithm>
#define lowbit(x) ((x)&(-(x)))
#define re register
#define ll long long
#define ull unsigned long long
#define rep(i,a,b) for(re int i=a;i<=b;++i)
#define per(i,a,b) for(re int i=a;i>=b;--i)
template<typename T>
inline void clear(T*array,int l,int r,int val)
{
	memset(&array[l],val,sizeof(T)*(r-l+1));
}
using namespace std;
const int N=1005;
struct Point
{
	int x,y;
	Point(int _x=0,int _y=0):x(_x),y(_y) {}
	inline Point operator +(const Point &rhs)const
	{
		return Point(x+rhs.x,y+rhs.y);
	}
	inline Point operator -(const Point &rhs)const
	{
		return Point(x-rhs.x,y-rhs.y);
	}
	inline int operator *(const Point &rhs)const
	{
		return x*rhs.y-y*rhs.x;
	}
	inline int operator ^(const Point &rhs)const
	{
		return x*rhs.x+y*rhs.y;
	}
	inline bool operator >(const Point&rhs)const
	{
		return x==rhs.x?y<rhs.y:x<rhs.x;
	}
	inline int norm()
	{
		return x*x+y*y;
	}
} point[N];
inline bool operator <(const Point &rhsx,const Point &rhsy)
{
	int ans=(rhsx-point[1])*(rhsy-point[1]);
	if(ans)
		return ans>=0;
	return (rhsx-point[1]).norm()<(rhsy-point[1]).norm();
}
int n;
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
	st[top=1]=1;
	for(int i=2; i<=n; ++i)
	{
		while(top>=2&&(point[st[top-1]]-point[st[top]])*(point[i]-point[st[top]])>=0)
			--top;
		st[++top]=i;
	}
	int ans=0;
//	for(int i=1; i<=top; ++i)
//		printf("%d ",st[i]);
	for(int i=1; i<=top; ++i)
		ans+=point[st[i]]*point[st[i%top+1]];
	cout<<abs(ans)/2/50<<endl;
	return 0;
}


