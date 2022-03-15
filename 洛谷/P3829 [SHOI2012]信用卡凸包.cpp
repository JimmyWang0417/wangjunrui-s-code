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
const int N=1e5+5;
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
	inline Point rotate(double rad)
	{
		return Point(x*cos(rad)-y*sin(rad),x*sin(rad)+y*cos(rad));
	}
	inline double norm()
	{
		return x*x+y*y;
	}
} add[4],point[N];
int cnt;
#define eps 1e-10
inline bool operator <(const Point &rhsx,const Point &rhsy)
{
	double ans=(rhsx-point[1])*(rhsy-point[1]);
	if(abs(ans)>eps)
		return ans>=0;
	return (rhsx-point[1]).norm()<(rhsy-point[1]).norm();
}
int st[N],top;
signed main()
{
	double n,a,b,r;
	cin>>n>>b>>a>>r;
	a/=2,b/=2;
	a-=r,b-=r;
	add[0]=Point(a,b),add[1]=Point(a,-b);
	add[2]=Point(-a,b),add[3]=Point(-a,-b);
	for(int i=1; i<=n; ++i)
	{
		double x,y,c;
		cin>>x>>y>>c;
		for(int j=0; j<4; ++j)
			point[++cnt]=add[j].rotate(c)+Point(x,y);
	}
	for(int i=2; i<=cnt; ++i)
	{
		if(point[i]>point[1])
			swap(point[i],point[1]);
	}
	sort(point+2,point+1+cnt);
//	for(int i=1; i<=cnt; ++i)
//		printf(" %lf %lf\n",point[i].x,point[i].y);
	st[top=1]=1;
	for(int i=2; i<=cnt; ++i)
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
//		printf("%LF ",len);
	}
//	putchar('\n');
	printf("%.2lf\n",len+2*r*acos(-1.0));
	return 0;
}

