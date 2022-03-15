#include<cstdio>
#include<cstring>
#include<iostream>
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
const int N=110,INF=0x3f3f3f3f;
int d[3][N],n,m,ans,l,r,mid,f[N][N];
inline bool check(int mid)
{
	memset(f,INF,sizeof(f));
	for(int i=0; i<=m; i++)
		for(int j=0; j<=m; j++)
			f[i][j]=INF;
	f[0][0]=0;
	for(re int n1=1; n1<=n; n1++)
	{
		//memset(f,INF,sizeof(f));
		//f[0][0]=0;
		int d1=d[1][n1],d2=d[2][n1];
		for(re int i=0; i<=m; i++)
			for(re int j=0; j<=m; j++)
			{
				if(i!=0)
					f[i][j]=min(f[i-1][j]+d1,f[i][j]);
				if(j!=0)
					f[i][j]=min(f[i][j-1]+d2,f[i][j]);
			}
		for(int i = 0; i <= m; i++)
			for(int j = 0; j <= m; j++)
			{
				if(f[i][j]>mid)

					f[i][j]=INF;
				else
					f[i][j]=0;
			}

	}
	if(f[m][m]<=mid)
		return 1;
	return false;
}
int main()
{
	read(n);
	read(m);
	for(re int i=1; i<=n; i++)
	{
		read(d[1][i]);
		read(d[2][i]);
	}
	l=0;
	r=2000000;
	while(l<=r)
	{
		mid=l+r>>1;
		if(check(mid))
		{
			ans=mid;
			r=mid-1;
		}
		else
			l=mid+1;
	}
	printf("%d\n",ans);
	//check(18);
	/*for(re int i=0; i<=n; i++)
	{
		for(re int j=0; j<=m; j++)
		{
			for(re int k=0; k<=m; k++)
				printf("%d",f[i][j][k]);
			putchar('\n');
		}
		putchar('\n');
	}*/
	return 0;
}

