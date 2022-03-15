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
const int N=2e5+5;
struct Point
{
	int x,y;
	inline bool operator <(const Point &rhs)const
	{
		return y<rhs.y;
	}
	inline bool operator >(const Point &rhs)const
	{
		return x<rhs.x;
	}
} point[N],st[N];
int n;
inline double calc(const Point &x,const Point &y)
{
	return sqrt((double)(x.x-y.x)*(x.x-y.x)+(double)(x.y-y.y)*(x.y-y.y));
}
inline double solve(int l,int r)
{
	if(l>=r)
		return 1e18;
	int mid=(l+r)>>1;
	double mindis=min(solve(l,mid-1),solve(mid+1,r));
	int top=0;
	for(int i=l; i<mid; ++i)
		if(point[mid].x-point[i].x<mindis/2)
			st[++top]=point[i];
	st[++top]=point[mid];
	for(int i=mid+1; i<=r; ++i)
		if(point[i].x-point[mid].x<mindis/2)
			st[++top]=point[i];
	sort(st+1,st+1+top);
	for(int i=1; i<=top; ++i)
		for(int j=i+1; j<=top&&st[j].y-st[i].y<mindis/2; ++j)
			for(int k=j+1; k<=top&&st[k].y-st[i].y<mindis/2; ++k)
				mindis=min(mindis,calc(st[i],st[j])+calc(st[i],st[k])+calc(st[j],st[k]));
	return mindis;
}
signed main()
{
	read(n);
	for(int i=1; i<=n; ++i)
		read(point[i].x,point[i].y);
	sort(point+1,point+1+n,greater<Point>());
	printf("%F\n",solve(1,n));
	return 0;
}


