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
const int N=4e5+5;
struct Point
{
	int x,y;
	pair<int,int>id;
	Point(int _x=0,int _y=0,pair<int,int> _id=pair<int,int>()):x(_x),y(_y),id(_id) {}
	inline bool operator <(const Point &rhs)const
	{
		return y<rhs.y;
	}
	inline bool operator >(const Point &rhs)const
	{
		return x<rhs.x;
	}
} point[N],a[N];
const int dx[4]= {1,-1,1,-1};
const int dy[4]= {1,1,-1,-1};
int n;

double mindis;
pair<pair<int,int>,pair<int,int> >minpair;
inline double calc(const Point &x,const Point &y)
{
	return sqrt((x.x-y.x)*(x.x-y.x)+(x.y-y.y)*(x.y-y.y));
}
inline void solve(int l,int r)
{
	if(l>=r)
		return;
	int mid=(l+r)>>1;
	solve(l,mid-1),solve(mid+1,r);
	int tot=0;
	for(int i=l; i<mid; ++i)
		if(point[mid].x-point[i].x<mindis)
			a[++tot]=point[i];
	a[++tot]=point[mid];
	for(int i=mid+1; i<=r; ++i)
		if(point[i].x-point[mid].x<mindis)
			a[++tot]=point[i];
	sort(a+1,a+1+tot);
	for(int i=1; i<=tot; ++i)
		for(int j=i+1; j<=tot&&a[j].y-a[i].y<mindis; ++j)
			if(a[i].id.first!=a[j].id.first&&mindis>calc(a[i],a[j]))
			{
				mindis=calc(a[i],a[j]);
				minpair=make_pair(a[i].id,a[j].id);
			}
}
signed main()
{
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	read(n);
	for(int i=1; i<=n; ++i)
	{
		int x,y;
		read(x,y);
		for(int j=0; j<4; ++j)
			point[i+j*n]=Point(x*dx[j],y*dy[j],make_pair(i,j+1));
	}
	sort(point+1,point+4*n+1,greater<Point>());
	mindis=1e100;
	solve(1,4*n);
	printf("%d %d %d %d\n",minpair.first.first,minpair.first.second,minpair.second.first,5-minpair.second.second);
	return 0;
}


