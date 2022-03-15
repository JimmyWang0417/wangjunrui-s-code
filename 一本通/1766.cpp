#include<cstdio>
#include<algorithm>
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
	return;
}
const int N=56,INF=0x3f3f3f3f;
int n,a,b,f[N][N][N][N],w[N],p[N],tot,c[N];//w[i]是离散化后的值，c[i]是离散化前的值，p[i]是去重后的值 
bool vis[N][N][N][N];
inline int dp(int i,int j,int l,int r)
{
	int &ans=f[i][j][l][r];
	if(vis[i][j][l][r])
		return ans;
	vis[i][j][l][r]=true;
	ans=INF;
	if(!l&&!r)
	{
		re int x=-INF,y=INF;
		for(re int k=i; k<=j; k++)
		{
			x=max(x,c[k]);
			y=min(y,c[k]);
		}
		ans=min(ans,a+b*(x-y)*(x-y));
		for(x=1; x<=tot; x++)
			for(y=x; y<=tot; y++)
				ans=min(ans,dp(i,j,x,y)+a+b*(p[y]-p[x])*(p[y]-p[x]));
		return ans;
	}
	else
	{
		if(i==j)
		{
			if(l<=w[i]&&w[i]<=r)
				ans=0;
			return ans;
		}
		for(re int k=i; k<j; k++)
			ans=min(min(ans,dp(i,k,l,r)+dp(k+1,j,l,r)),min(dp(i,k,0,0)+dp(k+1,j,l,r),dp(i,k,l,r)+dp(k+1,j,0,0)));
		return ans;
	}
}
int main()
{
	read(n);
	read(a);
	read(b);
	for(re int i=1; i<=n; i++)
	{
		read(p[i]);
		c[i]=w[i]=p[i];
	}
	sort(p+1,p+1+n);
	tot=unique(p+1,p+1+n)-p-1;
	for(re int i=1; i<=n; i++)
		w[i]=lower_bound(p+1,p+1+tot,c[i])-p;
	/*for(re int i=1; i<=tot; i++)
		printf("%d ",p[i]);
	putchar('\n');*/
	/*for(re int i=1; i<=n; i++)
		printf("%d\n",w[i]);*/
	printf("%d\n",dp(1,n,0,0));
	return 0;
}

