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
	inline double norm()
	{
		return sqrt(x*x+y*y);
	}
	inline bool operator <(const Point &rhs)const
	{
		return x==rhs.x?y<rhs.y:x<rhs.x;
	}
	inline void print()
	{
		printf("(%d,%d)\n",x,y);
	}
};
set<Point>s;
double sum;
inline void insert(Point x)
{
//	x.print();
	if(s.size()==0)
	{
		s.insert(x);
		return;
	}
	if(s.size()==1)
	{
		sum+=(*s.begin()-x).norm();
		s.insert(x);
		return;
	}
	auto l=s.lower_bound(x);
	auto r=l--;
	if((*l-x)*(*r-x)<0)
		return;
	sum-=(*l-*r).norm();
	while(l!=s.begin())
	{
		auto las=l--;
		if((*l-x)*(*las-x)<0)
			break;
		sum-=(*las-*l).norm();
		s.erase(las);
	}
	while(r!=s.end())
	{
		auto las=r++;
		if(r==s.end()||(*las-x)*(*r-x)<0)
			break;
		sum-=(*las-*r).norm();
		s.erase(las);
	}
	s.insert(x);
	l=r=s.find(x);
	--l,++r;
//	printf("l:\n");
//	printf("%d %d\n",l->x,l->y);
//	printf("r:\n");
//	printf("%d %d\n",r->x,r->y);
	sum+=(x-*l).norm()+(x-*r).norm();
//	printf("%lf\n",sum);
}
Point a[N];
bool vis[N];
int opt[N*2];
int q[N*2];
double ans[N];
int n,m;
signed main()
{
	Point capital;
	read(n,capital.x,capital.y);
	insert(Point(0,0));
	insert(Point(n,0));
	insert(capital);
	read(n);
	for(int i=1; i<=n; ++i)
		read(a[i].x,a[i].y);
	read(m);
	for(int i=1; i<=m; ++i)
	{
		read(opt[i]);
		if(opt[i]==1)
		{
			read(q[i]);
			vis[q[i]]=true;
		}
	}
	for(int i=1; i<=n; ++i)
		if(!vis[i])
			insert(a[i]);
	for(int i=m; i>=1; --i)
	{
//		printf("opt[%d]=%d\n",i,opt[i]);
		if(opt[i]==1)
			insert(a[q[i]]);
		else
			ans[i]=sum;
	}
	for(int i=1; i<=m; ++i)
		if(opt[i]==2)
			printf("%.2lf\n",ans[i]);
	return 0;
}


