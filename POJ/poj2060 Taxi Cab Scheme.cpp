#include <bitset>
#include <cstdio>
#include <cmath>
#include <cstring>
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
template<typename T>
inline void clear(T*a,int l,int r,int val)
{
	memset(&a[l],val,sizeof(T)*(r-l+1));
}
const int N=1005;
struct Edge
{
	int next,to;
} edge[N*N];
int head[N],num_edge;
inline void add_edge(int from,int to)
{
	edge[++num_edge].next=head[from];
	edge[num_edge].to=to;
	head[from]=num_edge;
}
struct Node
{
	int tim,x1,y1,x2,y2;
	inline int calc()
	{
		return tim+abs(x2-x1)+abs(y2-y1);
	}
} a[N];
std::bitset<N>vis;
int belong[N];
inline bool find(int u)
{
	for(re int i=head[u];i;i=edge[i].next)
	{
		int &v=edge[i].to;
		if(vis[v])
		continue;
		vis[v]=true;
		if(!belong[v]||find(belong[v]))
		{
			belong[v]=u;
			return true;
		}
	}
	return false;
 } 
inline void work()
{
	int n;
	read(n);
	for(re int i=1; i<=n; ++i)
	{
		int t1,t2;
		read(t1),read(t2);
		a[i].tim=t1*60+t2;
		read(a[i].x1),read(a[i].y1),read(a[i].x2),read(a[i].y2);
	}
	for(re int i=1; i<=n; ++i)
		for(re int j=1; j<=n; ++j)
		{
			if(i==j)
				continue;
			if(a[i].calc()+abs(a[j].x1-a[i].x2)+abs(a[j].y1-a[i].y2)<a[j].tim)
				add_edge(i,j+n);
		}
	int ans=0;
	for(re int i=1; i<=n; ++i)
	{
		vis.reset();
		if(find(i))
			++ans;
	}
	printf("%d\n",n-ans);
	memset(belong,0,sizeof(belong));
	memset(head,num_edge=0,sizeof(head));
}
signed main()
{
	int T;
	read(T);
	while(T--)
		work();
	return 0;
}
