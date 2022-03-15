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
inline void clear(T*a,int l,int r,int val)
{
	memset(&a[l],val,sizeof(T)*(r-l+1));
}
const int N=105,M=N*N;
int n,m;
struct Edge
{
	int next,to,dis;
} edge[M<<1];
int head[N],num_edge;
int out[N];
inline void add_edge(int from,int to,int dis)
{
	edge[++num_edge].next=head[from];
	edge[num_edge].to=to;
	edge[num_edge].dis=dis;
	++out[from];
	head[from]=num_edge;
}
double f[N][N],ans[N];
inline void Gauss()
{
	for(int i=1; i<=n; ++i)
	{
		int pos=i;
		for(int j=i+1; j<=n; ++j)
			if(fabs(f[pos][i])<fabs(f[j][i]))
				pos=i;
		if(i!=pos)
			std::swap(f[i],f[pos]);
		for(int j=i+1; j<=n; ++j)
		{
			double tmp=f[j][i]/f[i][i];
			for(re int k=i; k<=n+1; ++k)
				f[j][k]-=tmp*f[i][k];
		}
	}
	for(re int i=n; i>=1; --i)
	{
		ans[i]=f[i][n+1];
		for(re int j=i+1; j<=n; ++j)
			ans[i]-=(f[i][j]*ans[j]);
		ans[i]/=f[i][i];
	}
}
signed main()
{
	read(n,m);
	for(int i=1; i<=m; ++i)
	{
		int u,v,w;
		read(u,v,w);
		add_edge(u,v,w);
		if(u!=v)
			add_edge(v,u,w);
	}
	double answer=0.0;
	for(int now=0; now<=30; ++now)
	{
		for(int i=1; i<n; ++i)
		{
			f[i][i]=-out[i];
			for(int e=head[i]; e; e=edge[e].next)
			{
				int &v=edge[e].to,w=(edge[e].dis>>now)&1;
				if(w)
				{
					--f[i][n+1];
					--f[i][v];
				}
				else
					++f[i][v];
			}
		}
		f[n][n]=-1.0;
//		for(int i=1; i<=n; ++i)
//		{
//			for(int j=1; j<=n+1; ++j)
//				printf("%lf ",f[i][j]);
//			putchar('\n');
//		}
		Gauss();
//		printf("%lf\n",ans[1]);
		answer+=(1<<now)*ans[1];
		memset(f,0,sizeof(f));
	}
	printf("%.3lf\n",answer);
	return 0;
}


