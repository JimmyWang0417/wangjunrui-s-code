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
const int N=1e6+5,INF=0x7fffffff;
struct Edge
{
	int next,to;
} edge[N];
int head[N],num_edge;
inline void add_edge(int from,int to)
{
	edge[++num_edge].next=head[from];
	edge[num_edge].to=to;
	head[from]=num_edge;
}
bitset<N>vis;
int belong[N];
inline bool find(int u)
{
	for(int i=head[u]; i; i=edge[i].next)
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
int a[1005][1005],n,m;
int h[N],l[N];
signed main()
{
	read(n,m);
	for(int i=1; i<=n; ++i)
		for(int j=1; j<=m; ++j)
			read(a[i][j]);
	for(int i=1; i<=n; ++i)
		for(int j=1; j<=m; ++j)
		{
			h[i]=max(h[i],a[i][j]);
			l[j]=max(l[j],a[i][j]);
		}
	ll ans=0;
	for(int i=1; i<=n; ++i)
		for(int j=1; j<=m; ++j)
			ans+=max(0,a[i][j]-1);

	for(int i=1; i<=n; ++i)
		ans-=max(0,h[i]-1);
	for(int i=1; i<=m; ++i)
		ans-=max(0,l[i]-1);

//	printf("%lld\n",ans);
	for(int i=1; i<=n; ++i)
		for(int j=1; j<=m; ++j)
			if(a[i][j]&&h[i]==l[j])
				add_edge(i,j);
	for(int i=1; i<=n; ++i)
	{
		if(find(i))
			ans+=h[i]-1;
		vis.reset();
	}
	printf("%lld\n",ans);
	return 0;
}


