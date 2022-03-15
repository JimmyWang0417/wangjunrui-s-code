#include<cstdio>
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
int dis[60][60],n,m;
bool g[60][60][65];
int main()
{
	read(n);
	read(m);
	for(re int i=1; i<=n; i++)
		for(re int j=1; j<=n; j++)
			dis[i][j]=67;
	for(re int i=1,x,y; i<=m; i++)
	{
		read(x);
		read(y);
		dis[x][y]=1;
		g[x][y][0]=true;
	}
	for(re int t=1; t<=64; t++)
		for(re int k=1; k<=n; k++)
			for(re int i=1; i<=n; i++)
				for(re int j=1; j<=n; j++)
					if(g[i][k][t-1]&&g[k][j][t-1])
					{
						g[i][j][t]=true;
						dis[i][j]=1;
					}
	for(re int k=1; k<=n; k++)
		for(re int i=1; i<=n; i++)
			for(re int j=1; j<=n; j++)
				if(dis[i][k]+dis[k][j]<dis[i][j])
					dis[i][j]=dis[i][k]+dis[k][j];
	printf("%d\n",dis[1][n]);
	return 0;
}

