#include <bits/stdc++.h>
#define lowbit(x) ((x)&(-(x)))
#define eps (1e-4)
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
const int N=2500+5;
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
struct node
{
	int p,s;
} a[N],v[N];
int k,n;
int nxt[N],dfstime=-1;
inline void dfs(int u)
{
	int now=++dfstime;
	v[now]=a[u];
	for(int i=head[u]; i; i=edge[i].next)
		dfs(edge[i].to);
	nxt[now]=dfstime+1;
}
double dp[N][N];
inline bool check(double val)
{
	memset(dp,~(127/3),sizeof(dp));
//	printf("%lf\n",dp[0][0]);
	dp[0][0]=0;
	for(int i=0; i<=dfstime; ++i)
		for(int j=0; j<=k; ++j)
		{
			dp[i+1][j+1]=max(dp[i+1][j+1],dp[i][j]+v[i].p-v[i].s*val);
			dp[nxt[i]][j]=max(dp[nxt[i]][j],dp[i][j]);
		}
	return dp[dfstime+1][k]>eps;
}
signed main()
{
	read(k,n);
	++k;
	for(int i=1; i<=n; ++i)
	{
		int fa;
		read(a[i].s,a[i].p,fa);
		add_edge(fa,i);
	}
	dfs(0);
	double l=0,r=1e4;
//	printf("%d\n",check(1.662));
	while(l+eps<r)
	{
		double mid=(l+r)/2;
//		printf("%lf %d\n",mid,check(mid));
		if(check(mid))
			l=mid+eps;
		else
			r=mid-eps;
	}
	printf("%.3lf\n",l);
	return 0;
}

