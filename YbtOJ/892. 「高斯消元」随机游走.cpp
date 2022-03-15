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
const int N=1005+5;
int n,m,q;
struct node
{
	int u,v;
} e[N*N];
#define calc(i,j) ((i-1)*n+j)
#define eps 1e-10
double p[N];
struct Edge
{
	int next,to,id;
} edge[N*N];
int head[N],num_edge;
int deg[N];
inline void add_edge(int from,int to,int id)
{
	edge[++num_edge].next=head[from];
	edge[num_edge].to=to;
	edge[num_edge].id=id;
	head[from]=num_edge;
	++deg[from];
}
double g[N][N*2];
inline void gaosi(int a,int b)
{
	for(int i=1; i<=a; ++i)
	{
		int id=0;
		for(int j=i; j<=a; ++j)
			if(fabs(g[j][i])>eps)
			{
				id=j;
				break;
			}
		if(id!=i)
			swap(g[id],g[i]);
//		printf("fuckyou\n");
//		printf("%d\n",i);
		for(int j=1; j<=a; ++j)
			if(j!=i)
			{
				double div=g[j][i]/g[i][i];
				for(int k=i; k<=b; ++k)
					g[j][k]-=g[i][k]*div;
			}
	}
//	for(int i=1; i<=a; ++i)
//	{
//		for(int j=1; j<=b; ++j)
//			printf("%lf ",g[i][j]);
//		putchar('\n');
//	}
}
int w[N*N];
inline void work()
{
	int s,t;
	for(int i=1; i<=m; ++i)
		read(w[i]);
	read(s,t);
	int pos=calc(s,t);
	double ans=0;
	for(int i=1; i<=m; ++i)
		ans-=g[pos][i+n*n]*w[i];
	ans/=g[pos][pos];
	printf("%.2lf\n",ans);
}
int rk[N][N];
signed main()
{
	freopen("average.in","r",stdin);
	freopen("average.out","w",stdout);
	read(n,m,q);
	for(int i=1; i<=m; ++i)
	{
		read(e[i].u,e[i].v);
		add_edge(e[i].u,e[i].v,i);
		add_edge(e[i].v,e[i].u,i);
	}
	for(int i=1; i<=n; ++i)
		scanf("%lf",&p[i]);
	for(int u=1; u<=n; ++u)
		for(int v=1; v<=n; ++v)
			if(u!=v)
			{
				g[calc(u,v)][calc(u,v)]=p[u]*p[v]-1;
				for(int i=head[u]; i; i=edge[i].next)
				{
					int &x=edge[i].to;
					double add=(1-p[u])/deg[u]*p[v];
					g[calc(u,v)][calc(x,v)]+=add;
					g[calc(u,v)][n*n+edge[i].id]+=add;
				}
				for(int i=head[v]; i; i=edge[i].next)
				{
					int &y=edge[i].to;
					double add=p[u]*(1-p[v])/deg[v];
					g[calc(u,v)][calc(u,y)]+=add;
					g[calc(u,v)][n*n+edge[i].id]+=add;
				}
				for(int i=head[u]; i; i=edge[i].next)
				{
					int &x=edge[i].to;
					for(int j=head[v]; j; j=edge[j].next)
					{
						int &y=edge[j].to;
						double add=(1-p[u])/deg[u]*(1-p[v])/deg[v];
						g[calc(u,v)][calc(x,y)]+=add;
						g[calc(u,v)][n*n+edge[i].id]+=add;
						g[calc(u,v)][n*n+edge[j].id]+=add;
					}
				}
			}
	for(int i=1; i<=n; ++i)
		g[calc(i,i)][calc(i,i)]=1;
	gaosi(n*n,n*n+m);
	while(q--)
		work();
	return 0;
}

