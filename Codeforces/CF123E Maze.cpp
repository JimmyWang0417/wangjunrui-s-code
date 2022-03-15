#include <bits/stdc++.h>
#define lowbit(x) ((x)&(-(x)))
#define re register
#define ll long long
#define ull unsigned long long
#define rep(i,a,b) for(re int i=a;i<=b;++i)
#define per(i,a,b) for(re int i=a;i>=b;--i)
using namespace std;
const int N=1e6+5;
int n;
struct Edge
{
	int next,to;
} edge[N*2];
int head[N],num_edge;
inline void add_edge(int from,int to)
{
	edge[++num_edge].next=head[from];
	edge[num_edge].to=to;
	head[from]=num_edge;
}
int size[N];
double a[N],b[N],suma,sumb;
double ans;
inline void dfs(int u,int _fa)
{
	size[u]=1;
	double now=0;
	for(int i=head[u]; i; i=edge[i].next)
	{
		int &v=edge[i].to;
		if(v==_fa)
			continue;
		dfs(v,u);
		a[u]+=a[v];
		size[u]+=size[v];
		now+=size[v]*a[v];
	}
	now+=(n-size[u])*(1-a[u]);
	ans+=b[u]*now;
}
signed main()
{
	scanf("%d",&n);
	for(int i=1; i<n; ++i)
	{
		int x,y;
		scanf("%d%d",&x,&y);
		add_edge(x,y);
		add_edge(y,x);
	}
	for(int i=1; i<=n; ++i)
	{
		scanf("%lf%lf",&a[i],&b[i]);
		suma+=a[i],sumb+=b[i];
	}
	for(int i=1; i<=n; ++i)
	{
		a[i]/=suma;
		b[i]/=sumb;
	}
	dfs(1,0);
//	for(int i=1; i<=n; ++i)
//		printf("%lf %lf\n",a[i],b[i]);
	printf("%.9lf\n",ans);
	return 0;
}


