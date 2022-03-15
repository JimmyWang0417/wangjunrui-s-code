#include<cstdio>
#include<algorithm>
#define re register
#define int long long
using std::max;
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
const int N = 2e5 + 10 ;
int n ;
int a[N] ;
int dp1[N] , dp2[N] ;
int num , head[N] , tot;
struct node
{
	int nex , v;
} edge[N << 1];
inline void add_edge(int u , int v)
{
	edge[++ tot].v = v ;
	edge[tot].nex = head[u] ;
	head[u] = tot ;
}
inline int dfs1(int far , int u)
{
	if(a[u] == 1)  dp1[u] = 1 ;
	else  dp1[u] = -1 ;
	for(int i = head[u] ; i ; i = edge[i].nex)
	{
		int v = edge[i].v ;
		if(v == far)  continue ;
		dp1[u] += max(0LL , dfs1(u , v)) ;
	}
	return dp1[u] ;
}
inline void dfs2(int far , int u)
{
	for(int i = head[u] ; i ; i = edge[i].nex)
	{
		int v = edge[i].v ;
		if(v == far)  continue ;
		dp2[v] = dp1[v] + max(0LL , dp2[u] - max(0LL , dp1[v])) ;
		dfs2(u , v) ;
	}
}
signed main()
{
	read(n);
	for(re int i=1; i<=n; ++i) read(a[i]);
	for(re int i=1; i<n; ++i)
	{
		int u , v ;
		read(u),read(v);
		add_edge(u , v) ;
		add_edge(v , u) ;
	}
	dfs1(1 , 1) ;
	dp2[1] = dp1[1] ;
	dfs2(1 , 1) ;
	for(re int i=1; i<=n; ++i)
		printf("%lld ",dp2[i]);
	putchar('\n');
	return 0 ;
}


