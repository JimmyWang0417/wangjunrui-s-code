#include <cstdio>
#include <iostream>
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
const int N=1e6+5;
struct Point
{
	double x,y;
	inline double operator *(const Point &rhs)const
	{
		return x*rhs.y-rhs.x*y;
	}
} p[N];
int n;
inline double area()
{
	double ans=0;
	for(int i=1; i<=n; ++i)
		ans+=p[i]*p[i%n+1];
	return ans;
}
signed main()
{
	ios::sync_with_stdio(false);
	while(cin>>n&&n)
	{
		for(int i=1; i<=n; ++i)
			cin>>p[i].x>>p[i].y;
		printf("%.0lf\n",fabs(area())/2);
	}
	return 0;
}


