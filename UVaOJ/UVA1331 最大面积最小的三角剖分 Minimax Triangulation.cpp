#include<cstdio>
#include<cmath>
#include<iostream>
#define re register
#define ll long long
#define eps 1e-10
#define doubleinf 1e18
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
const int N=55;
struct node
{
	double x,y;
} point[N];
int n;
double dp[N][N];
inline double S(const node &a,const node &b,const node &c)
{
	return fabs((a.x-b.x)*(a.y-c.y)-(a.y-b.y)*(a.x-c.x))/2.0;
}
inline bool check(int a,int b,int c)
{
	for(re int i=1; i<=n; ++i)
	{
		if(a==i||b==i||c==i)continue;
		double sum=S(point[i],point[a],point[b])
		           +S(point[i],point[b],point[c])
		           +S(point[i],point[a],point[c]);
		if(sum-S(point[a],point[b],point[c])<eps)
			return true;
	}
	return false;
}
int main()
{
	re int T;
	read(T);
	while(T--)
	{
		read(n);
		for(re int i=1; i<=n; ++i)
			scanf("%lf%lf",&point[i].x,&point[i].y);
		for(re int i=1; i<=n; ++i)
			dp[i][i]=0;
		for(re int len=2; len<=n; ++len)
			for(re int i=1,j; j=i+len,i<=n-len; ++i)
			{
				dp[i][j]=doubleinf;
				for(re int k=i+1;k<j; ++k)
				{
					if(check(i,j,k))
						continue;
					dp[i][j]=min(dp[i][j],max(S(point[i],point[j],point[k]),max(dp[i][k],dp[k][j])));
				}
			}
		printf("%.1lf\n",dp[1][n]);
	}
}
