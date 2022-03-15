#include<cstdio>
#include<cstring>
#include<algorithm>
#define re register
#define co const
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
co int N=310,INF=0x3f3f3f3f;
int n,m,f[N][N],dp[20][N][N],dep,g[N][N],ans;
int main()
{
	read(n);
	read(m);
	int nn=n;
	while(nn)
	{
		dep++;
		nn>>=1;
	}
	memset(f,INF,sizeof(f));
	memset(dp,INF,sizeof(dp));
	for(re int i=1,u,v,w; i<=m; i++)
	{
		read(u);
		read(v);
		read(w);
		dp[0][u][v]=-w;
		read(w);
		dp[0][v][u]=-w;
	}
	for(re int i=1; i<=n; i++)
	{
		f[i][i]=0;
		for(re int r=0; r<=dep; r++)
			dp[r][i][i]=0;
	}
	for(re int r=0; r<dep; r++)
		for(re int k=1; k<=n; k++)
			for(re int i=1; i<=n; i++)
				for(re int j=1; j<=n; j++)
					dp[r+1][i][j]=min(dp[r+1][i][j],dp[r][i][k]+dp[r][k][j]);
	/*for(re int i=0; i<=9; i++)
	{
		for(re int j=1; j<=n; j++)
		{
			for(re int k=1; k<=n; k++)
				printf("%d\t\t",dp[i][j][k]);
			putchar('\n');
		}
		putchar('\n');
	}*/
	re bool flag;
	for(re int r=dep; r>=0; r--)
	{
		memcpy(g,f,sizeof(g));
		for(re int k=1; k<=n; k++)
			for(re int i=1; i<=n; i++)
				for(re int j=1; j<=n; j++)
					g[i][j]=min(g[i][j],min(dp[r][i][k]+f[k][j],f[i][k]+dp[r][k][j]));
		flag=true;
		for(re int i=1; i<=n; i++)
			if(g[i][i]<0)
			{
				flag=false;
				break;
			}
		if(flag)
		{
			ans|=1<<r;
			memcpy(f,g,sizeof(f));
		}
	}
	if(ans<=n)
		printf("%d\n",ans+1);
	else
		puts("0");
	return 0;
}

