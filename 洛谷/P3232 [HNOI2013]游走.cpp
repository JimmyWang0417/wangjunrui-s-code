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
const int N=505,M=125000+5;
int n,m,a[N];
struct node
{
	int u,v;
} e[M];
int in[N];
double f[N][N],ans[N];
inline void Gauss()
{
	for(re int i=1; i<=n; ++i)
	{
		int pos=i;
		for(re int j=i+1; j<=n; ++j)
			if(fabs(f[pos][i])<fabs(f[j][i]))
				pos=i;
		if(i!=pos)
			std::swap(f[i],f[pos]);
		for(re int j=i+1; j<=n; ++j)
		{
			double tmp=f[j][i]/f[i][i];
			for(re int k=i; k<=n+1; ++k)
				f[j][k]-=tmp*f[i][k];
		}
	}
//	for(re int i=1; i<=n; ++i)
//	{
//		for(re int j=1; j<=n+1; ++j)
//			printf("%lf ",f[i][j]);
//		putchar('\n');
//	}
	for(re int i=n; i>=1; --i)
	{
		ans[i]=f[i][n+1];
		for(re int j=i+1; j<=n; ++j)
			ans[i]-=(f[i][j]*ans[j]);
		ans[i]/=f[i][i];
	}
}
double answer[M];
int deg[N];
signed main()
{
	read(n,m);
	for(re int i=1; i<=m; ++i)
	{
		int &u=e[i].u,&v=e[i].v;
		read(e[i].u,e[i].v);
		++deg[u],++deg[v];
	}
	for(re int i=1; i<=m; ++i)
	{
		int &u=e[i].u,&v=e[i].v;
		if(u!=n)
			f[v][u]+=1.0/deg[u];
		if(v!=n)
			f[u][v]+=1.0/deg[v];
	}
	for(re int i=1; i<=n; ++i)
		f[i][i]=-1.0;
	f[1][n+1]=-1.0;
//	for(re int i=1; i<=n; ++i)
//	{
//		for(re int j=1; j<=n+1; ++j)
//			printf("%lf ",f[i][j]);
//		putchar('\n');
//	}
	Gauss();
//	for(re int i=1; i<=n; ++i)
//		printf("%lf ",ans[i]);
//	putchar('\n');
	for(re int i=1; i<=m; ++i)
	{
		int &u=e[i].u,&v=e[i].v;
		if(u!=n)
			answer[i]+=ans[u]/deg[u];
		if(v!=n)
			answer[i]+=ans[v]/deg[v];
//		printf("%lf ",answer[i]);
	}
//	putchar('\n');
	std::sort(answer+1,answer+1+m);
	double sum=0;
	for(re int i=1; i<=m; ++i)
		sum+=(m-i+1)*answer[i];
	printf("%.3lf\n",sum);
	return 0;
}


