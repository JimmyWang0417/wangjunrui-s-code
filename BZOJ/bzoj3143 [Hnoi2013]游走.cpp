#include<algorithm>
#include<cstdio>
#include<cmath>
#define N 505
#define re register
using namespace std;
template<typename T>
inline void read(T&x)
{
	x=0;
	char s=getchar();
	bool f=false;
	while(!(s>='0'&&s<='9'))
	{
		if(s=='-')
			f=true;
		s=getchar();
	}
	while(s>='0'&&s<='9')
	{
		x=(x<<1)+(x<<3)+s-'0';
		s=getchar();
	}
	if(f)
		x=(~x)+1;
}
int n,m;
int to[N*N*2],nxt[N*N*2],h[N],etop;
int F[N*N],T[N*N];
double q[N*N];
int num[N];
double f[N][N];
double im[N*N*2];
inline void add(int u,int v)
{
	num[u]++;
	to[++etop]=v;
	nxt[etop]=h[u];
	h[u]=etop;
}
int main()
{
	read(n);
	read(m);
	for(re int i=1,u,v; i<=m; i++)
	{
		read(u);
		read(v);
		add(u,v);
		add(v,u);
		F[i]=u;
		T[i]=v;
	}
	f[1][n]=1;
	for(re int i=1; i<n; i++)
	{
		f[i][i]=1;
		for(re int j=h[i]; j; j=nxt[j])
			if(to[j]!=n)
				f[i][to[j]]=-1.0/num[to[j]];
	}
	for(re int i=1; i<n; i++)
	{
		int now=i;
		double s=f[i][i];
		for(re int j=i+1; j<n; j++)
			if(fabs(f[j][i])-fabs(s)>1e-10)
			{
				now=j;
				s=f[j][i];
			}
		if(now!=i)
		{
			for(re int j=1; j<n; j++)
				swap(f[i][j],f[now][j]);
		}
		for(re int j=n; j>=i; j--)f[i][j]/=f[i][i];
		for(re int j=1; j<n; j++)
			if(i!=j)
				for(re int k=n; k>=i; k--)
					f[j][k]-=f[j][i]*f[i][k];
	}
	for(re int i=1; i<=m; i++)
	{
		if(F[i]!=n)
			q[i]+=f[F[i]][n]*(1.0/num[F[i]]);
		if(T[i]!=n)
			q[i]+=f[T[i]][n]*(1.0/num[T[i]]);
		//printf("%d %d %lf\n",F[i],T[i],q[i]);
	}
	sort(q+1,q+1+m);
	double ans=0;
	for(int i=1; i<=m; i++)
		ans+=q[i]*((m-i+1)*1.0);
	printf("%.3lf",ans);
	return 0;
}
