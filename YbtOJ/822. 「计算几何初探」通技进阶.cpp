#include <bits/stdc++.h>
#define lowbit(x) ((x)&(-(x)))
#define re register
#define ll long long
#define ull unsigned long long
#define rep(i,a,b) for(re int i=a;i<=b;++i)
#define per(i,a,b) for(re int i=a;i>=b;--i)
#define eps (1e-10)
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
const int N=1e3+5;
struct Point
{
	double x,y;
	Point (double _x=0,double _y=0):x(_x),y(_y) {}
	inline Point operator +(const Point&rhs)const
	{
		return Point(x+rhs.x,y+rhs.y);
	}
	inline Point operator -(const Point &rhs)const
	{
		return Point(x-rhs.x,y-rhs.y);
	}
	inline Point operator *(const double &k)const
	{
		return Point(x*k,y*k);
	}
	inline Point operator /(const double &k)const
	{
		return Point(x/k,y/k);
	}
	inline double operator *(const Point &rhs)const
	{
		return x*rhs.y-y*rhs.x;
	}
	inline double alpha()const
	{
		return atan2(y,x);
	}
	inline bool operator <(const Point &rhs)const
	{
		double d=alpha()-rhs.alpha();
		if(abs(d)>eps)
			return d<0;
		else
		{
			return (x==rhs.x?y<rhs.y:x<rhs.x);
		}
	}
	inline bool operator ==(const Point &rhs)const
	{
		return abs(x-rhs.x)<eps&&abs(y-rhs.y)<eps;
	}
} v[N],p[N];
int n;
inline double calc(int a,int b)
{
	Point dv=v[b]-v[a],
	      dp=p[b]-p[a];
	if(fabs(dv.x)>eps)
		return -dp.x/dv.x;
	else if(fabs(dv.y)>eps)
		return -dp.y/dv.y;
	else
		return 0;
}
signed main()
{
	freopen("gentech.in","r",stdin),freopen("gentech.out","w",stdout);
	read(n);
	for(int i=1; i<=n; ++i)
	{
		int t1,x1,y1,t2,x2,y2;
		read(t1,x1,y1,t2,x2,y2);
		v[i]=Point((x2-x1)/(double)(t2-t1),(y2-y1)/(double)(t2-t1));
		p[i]=Point(x1,y1)-v[i]*t1;
	}
//	for(int i=1; i<=n; ++i)
//		printf("%lf %lf %lf %lf\n",v[i].x,v[i].y,p[i].x,p[i].y);
	int ans=0;
	for(int u=1; u<=n; ++u)
	{
		int tot=0;
		double tim[N];
		Point cur[N];
		for(int to=1; to<=n; ++to)
			if(u!=to)
			{
				double t=calc(u,to);
				if(p[u]+v[u]*t==p[to]+v[to]*t)
				{
					tim[++tot]=t;
					cur[tot]=v[to]-v[u];
				}
			}
//		for(int i=1; i<=n; ++i)
//			printf("%lf ",tim[i]);
//		putchar('\n');
//		for(int i=1; i<=n; ++i)
//			printf("%lf %lf\n",cur[i].x,cur[i].y);
//		puts("\n\n");
		sort(tim+1,tim+1+tot);
		sort(cur+1,cur+1+tot);
		for(int l=1,r=0; l<=tot; l=r+1)
		{
			while(r<tot&&fabs(tim[r+1]-tim[l])<eps)
				++r;
			ans=max(ans,r-l+1);
		}
		for(int l=1,r=0; l<=tot; l=r+1)
		{
			while(r<tot&&fabs(cur[r+1]*cur[l])<eps)
				++r;
			int cnt=0;
			for(int i=l+1; i<=r; ++i)
				if(cur[i]==cur[i-1])
					++cnt;
			ans=max(ans,r-l+1-cnt);
		}
	}
	printf("%d\n",ans+1);
	return 0;
}


