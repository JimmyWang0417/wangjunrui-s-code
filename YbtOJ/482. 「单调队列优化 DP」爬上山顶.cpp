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
const int N=5e5+5;
struct Edge
{
	int next,to;
} edge[N];
int head[N],num_edge;
bitset<N>vis;
inline void add_edge(int from,int to)
{
	edge[++num_edge].next=head[from];
	edge[num_edge].to=to;
	head[from]=num_edge;
//	printf(" %d %d\n",from,to);
	vis.set(to);
}
struct Point
{
	int x,y;
	Point(int _x=0,int _y=0):x(_x),y(_y) {}
	inline Point operator +(const Point&rhs)const
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
	inline bool operator >(const Point &rhs)const
	{
		return y==rhs.y?x>rhs.x:y>rhs.y;
	}
	inline bool operator <=(const Point &rhs)const
	{
		return !((*this)>rhs);
	}
} a[N];
int n;
int st[N],top;
int l[N],r[N];
int to[N];
ll dis[N];
inline void dfs(int u)
{
	for(int i=head[u]; i; i=edge[i].next)
	{
		int &v=edge[i].to;
		dis[v]=dis[u]+abs(u-v);
		dfs(v);
	}
}
signed main()
{
	freopen("mountain.in","r",stdin),freopen("mountain.out","w",stdout);
	read(n);
	for(int i=1; i<=n; ++i)
		read(a[i].x,a[i].y);
	a[0].y=-100;
	st[top=1]=1;
	for(int i=2; i<=n; ++i)
	{
		while(top>1&&(a[st[top-1]]-a[i])*(a[st[top]]-a[i])>0)
			--top;
//		printf("%d:\n",i);
//		for(int j=1; j<=top; ++j)
//			printf("%d ",st[j]);
//		putchar('\n');
		if(a[st[top]]>a[i])
			l[i]=st[top];
		st[++top]=i;
	}
	st[top=1]=n;
	for(int i=n-1; i>=1; --i)
	{
		while(top>1&&(a[st[top-1]]-a[i])*(a[st[top]]-a[i])<0)
			--top;
		if(a[st[top]]>a[i])
			r[i]=st[top];
		st[++top]=i;
	}
//	for(int i=1; i<=n; ++i)
//		printf("-%d %d\n",l[i],r[i]);
	for(int i=1; i<=n; ++i)
		to[i]=a[l[i]].y<=a[r[i]].y?r[i]:l[i];
//	for(int i=1; i<=n; ++i)
//		printf("%d ",to[i]);
//	putchar('\n');
	st[top=1]=1;
	for(int i=2; i<=n; ++i)
	{
		while(top&&a[to[st[top]]]<=a[to[i]])
			--top;
		if(to[i]&&to[i]<i)
			add_edge(top?st[top]:to[i],i);
		st[++top]=i;
	}
	st[top=1]=n;
	for(int i=n-1; i>=1; --i)
	{
		while(top&&a[to[st[top]]]<=a[to[i]])
			--top;
		if(to[i]&&to[i]>i)
			add_edge(top?st[top]:to[i],i);
		st[++top]=i;
	}
	for(int i=1; i<=n; ++i)
		if(!vis[i])
			dfs(i);
	for(int i=1; i<=n; ++i)
		printf("%lld\n",dis[i]);
//	putchar('\n');
	return 0;
}


