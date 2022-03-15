#include<cstdio>
using namespace std;
const int maxn=401,MAX=0x7fffffff>>1;
int maxx[maxn][maxn],minn[maxn][maxn],sum[maxn],a[maxn],n,maxans,minans=MAX;
inline int read()
{
	int x=0;
	char s=getchar();
	bool b=false;
	while(s<'0'||s>'9')
	{
		if(s=='-')b=true;
		s=getchar();
	}
	while(s>='0'&&s<='9')
	{
		x=(x<<1)+(x<<3)+s-'0';
		s=getchar();
	}
	return b?-x:x;
}
inline int max(const int &a,const int &b)
{
	return a>b?a:b;
}
inline int min(const int &a,const int &b)
{
	return a<b?a:b;
}
int main()
{
	n=read();
	for(register int i=1; i<=n; i++)
		a[i+n]=a[i]=read();
	for(register int i=1; i<=2*n; i++)
	{
		sum[i]=sum[i-1]+a[i];
		maxx[i][i]=minn[i][i]=0;
	}
	for(register int len=2; len<=n; len++)
		for(register int i=1; i<=2*n-len+1; i++)
		{
			int j=i+len-1;
			maxx[i][j]=0;
			minn[i][j]=MAX;
			for(register int k=i; k<j; k++)
			{
				maxx[i][j]=max(maxx[i][j],maxx[i][k]+maxx[k+1][j]);
				minn[i][j]=min(minn[i][j],minn[i][k]+minn[k+1][j]);
			}
			maxx[i][j]+=+sum[j]-sum[i-1];
			minn[i][j]+=+sum[j]-sum[i-1];
		}
	for(register int i=1; i<=n; i++)
	{
		maxans=max(maxans,maxx[i][i+n-1]);
		minans=min(minans,minn[i][i+n-1]);
	}
	printf("%d\n%d\n",minans,maxans);
}
