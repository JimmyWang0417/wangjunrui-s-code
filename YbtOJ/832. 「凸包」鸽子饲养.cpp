#include <bits/stdc++.h>
#define lowbit(x) ((x)&(-(x)))
#define re register
#define ll long long
#define ull unsigned long long
#define rep(i,a,b) for(re int i=a;i<=b;++i)
#define per(i,a,b) for(re int i=a;i>=b;--i)
template<typename T>inline void read(T&x)
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
const int N=1e5+5,M=505;
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
	inline ll operator *(const Point &rhs)const
	{
		return (ll)x*rhs.y-(ll)y*rhs.x;
	}
} a[N],b[M];
int n,m;
int f[M][M];
signed main()
{
	freopen("lo.in","r",stdin),freopen("lo.out","w",stdout);
	read(n,m);
	for(int i=1; i<=n; ++i)
		read(a[i].x,a[i].y);
	for(int i=1; i<=m; ++i)
		read(b[i].x,b[i].y);
	memset(f,0x3f,sizeof(f));
	for(int i=1; i<=m; ++i)
	{
		int maxx=0,minn=0;
		int high=0,low=0;
		for(int j=1; j<=n; ++j)
		{
			if(a[j].x==b[i].x&&a[j].y==b[i].y)continue;
			if(!maxx||(a[maxx]-b[i])*(a[j]-b[i])>0)maxx=j;
			if(!minn||(a[minn]-b[i])*(a[j]-b[i])<0)minn=j;
#define calc(j) ((a[j]-b[i])*(a[1]-b[i]))
			if(!high||calc(high)<calc(j))high=j;
			if(!low||calc(low)>calc(j))low=j;
		}
		if((a[high]-b[i])*(a[low]-b[i])<0)continue;
		for(int j=1; j<=m; ++j)if(i!=j)
			{
				if((a[minn]-b[i])*(b[j]-b[i])<=0&&(b[j]-b[i])*(a[maxx]-b[i])>=0)
					f[i][j]=1;
			}
	}
	for(int k=1; k<=m; ++k)
		for(int i=1; i<=m; ++i)
			for(int j=1; j<=m; ++j)
				f[i][j]=min(f[i][j],f[i][k]+f[k][j]);
	int ans=f[0][0];
	for(int i=1; i<=m; ++i)ans=min(ans,f[i][i]);
	printf("%d\n",ans);
	return 0;
}


