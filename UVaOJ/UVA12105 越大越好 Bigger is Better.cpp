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
const int N=105,M=3005;
int dp[N][M],p[N][M],n,m,kase,need[]= {6, 2, 5, 5, 4, 5, 6, 3, 7, 6};
int main()
{
	while(read(n),n)
	{
		printf("Case %d: ",++kase);
		read(m);
		for(re int i=0; i<=n; ++i)
			for(re int j=0; j<m; ++j)
			{
				int &ans=dp[i][j],&now=p[i][j];
				ans=now=-1;
				if(j==0)
					ans=0;
				for(re int d=9,t; d>=0; --d)
					if(i>=need[d])
					{
						t=dp[i-need[d]][(j*10+d)%m];
						if(t>-1&&t+1>ans)
						{
							ans=t+1;
							now=d;
						}
					}
			}
		/*for(re int i=0; i<=n; ++i)
		{
			for(re int j=0; j<m; ++j)
				printf("%d ",dp[i][j]);
			printf("\n");
		}*/
		if(p[n][0]<0)
		{
			printf("-1\n");
			continue;
		}
		for(re int i=n,j=0,d=p[i][j]; d>=0; d=p[i][j])
		{
			printf("%d",d);
			i-=need[d];
			j=(j*10+d)%m;
		}
		printf("\n");
	}
}
