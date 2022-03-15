#include <cstdio>
#include <cstring>
#include <iostream>
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
const int N=5005;
struct Point
{
	int x,y;
	Point(int _x=0,int _y=0):x(_x),y(_y) {}
	inline Point operator +(const Point &rhs)const
	{
		return Point(x+rhs.x,y-rhs.y);
	}
	inline Point operator -(const Point &rhs)const
	{
		return Point(x-rhs.x,y-rhs.y);
	}
	inline int operator *(const Point &rhs)const
	{
		return x*rhs.y-rhs.x*y;
	}
} a[N];
struct Line
{
	Point x,y;
} b[N];
int sum[N];
inline bool inner(Line line,Point x)
{
	int ans=(line.x-x)*(line.y-x),d1=line.x.y-x.y,d2=line.y.y-x.y;
	return (ans<=0&&d1<0&&d2>=0)||(ans>=0&&d1>=0&&d2<0);
}
signed main()
{
	ios::sync_with_stdio(false);
	int n,m,x1,y1,x2,y2;
	while(cin>>m>>n>>x1>>y1>>x2>>y2&&m)
	{
		for(int i=1; i<=m; ++i)
		{
			int u,l;
			cin>>u>>l;
			b[i].x.x=u,b[i].x.y=y1;
			b[i].y.x=l,b[i].y.y=y2;
		}
		for(int i=1; i<=n; ++i)
			cin>>a[i].x>>a[i].y;
		b[0].x.x=x1,b[0].x.y=y1;
		b[0].y.x=x1,b[0].y.y=y2;
		b[m+1].x.x=x2,b[m+1].x.y=y1;
		b[m+1].y.x=x2,b[m+1].y.y=y2;
		for(int i=1; i<=n; ++i)
		{
			for(int j=0; j<=m; ++j)
				if((inner(b[j],a[i])+inner(b[j+1],a[i]))&1)
				{
					++sum[j];
					break;
				}
		}
		for(int i=0; i<=m; ++i)
			printf("%d: %d\n",i,sum[i]);
		memset(sum,0,sizeof(sum));
		putchar('\n');
	}
	return 0;
}


