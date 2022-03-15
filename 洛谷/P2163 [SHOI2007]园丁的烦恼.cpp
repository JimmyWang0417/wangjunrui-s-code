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
const int N=3e6+5;
struct Point
{
	int opt,x,y,id;
	inline bool operator <(const Point &rhs)const
	{
		return x==rhs.x?(y==rhs.y?opt<rhs.opt:y<rhs.y):x<rhs.x;
	}
} a[N];
int n,m;
int p[N],tot;
int cnt;
class Tree_array
{
	private:
		int sum[N];
	public:
		inline void update(int pos)
		{
			for(int i=pos; i<=tot; i+=lowbit(i))
				++sum[i];
		}
		inline int query(int pos)
		{
			int res=0;
			for(int i=pos; i; i-=lowbit(i))
				res+=sum[i];
			return res;
		}
} tree;
int answer[N];
signed main()
{
	read(n,m);
	for(int i=1; i<=n; ++i)
	{
		a[i].opt=1;
		read(a[i].x,a[i].y);
		++a[i].x,++a[i].y;
		p[++tot]=a[i].y;
	}
	cnt=n;
	for(int i=1; i<=m; ++i)
	{
		int x1,y1,x2,y2;
		read(x1,y1,x2,y2);
		++x2,++y2;
		p[++tot]=y1,p[++tot]=y2;
		++cnt;
		a[cnt].opt=2,a[cnt].x=x2,a[cnt].y=y2,a[cnt].id=i;
		++cnt;
		a[cnt].opt=3,a[cnt].x=x1,a[cnt].y=y2,a[cnt].id=i;
		++cnt;
		a[cnt].opt=3,a[cnt].x=x2,a[cnt].y=y1,a[cnt].id=i;
		++cnt;
		a[cnt].opt=2,a[cnt].x=x1,a[cnt].y=y1,a[cnt].id=i;
	}
	sort(a+1,a+1+cnt);
	sort(p+1,p+1+tot);
	tot=(int)(unique(p+1,p+1+tot)-p-1);
	for(int i=1; i<=cnt; ++i)
	{
		int y=(int)(lower_bound(p+1,p+1+tot,a[i].y)-p);
		if(a[i].opt==1)
			tree.update(y);
		else if(a[i].opt==2)
			answer[a[i].id]+=tree.query(y);
		else
			answer[a[i].id]-=tree.query(y);
	}
	for(int i=1; i<=m; ++i)
		printf("%d\n",answer[i]);
	return 0;
}


