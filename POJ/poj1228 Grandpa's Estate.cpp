#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cmath>
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
	inline int operator *(const Point &rhs)const
	{
		return x*rhs.y-y*rhs.x;
	}
	inline Point operator -(const Point &rhs)const
	{
		return Point(x-rhs.x,y-rhs.y);
	}
	inline bool operator >(const Point &rhs)const
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
		return ans>0;
	return (rhsx-point[1]).norm()<(rhsy-point[1]).norm();
}
int st[N],top;
int n;
inline void work()
{
	cin>>n;
	for(int i=1; i<=n; ++i)
	{
		cin>>point[i].x>>point[i].y;
		if(point[i]>point[1])
			swap(point[i],point[1]);
	}
	if(n<6)
	{
		puts("NO");
		return;
	}
	sort(point+2,point+1+n);
	st[top=1]=1;
	for(int i=2; i<=n; ++i)
	{
		while(top>=2&&(point[st[top-1]]-point[st[top]])*(point[i]-point[st[top]])>0)
			--top;
		st[++top]=i;
	}
	bool flag=0;
//	if(top<=2)
//	{
//		puts("NO");
//		return;
//	}
	for(int i=2; i<=top; ++i)
	{
		Point x=point[st[i-1]],y=point[st[i]],z=point[st[i%top+1]];
		if((x-y)*(z-y)==0)
			flag=false;
		else
		{
			if(flag)
			{
				puts("NO");
				return;
			}
			flag=true;
		}
	}
	puts("YES");
}
signed main()
{
	int T;
	cin>>T;
	while(T--)
		work();
	return 0;
}


