#include<cstdio>
#define re register
using namespace std;
inline int read()
{
	char s=getchar();
	bool f=false;
	int x=0;
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
	return f?-x:x;
}
const int N=110;
int n,q,l[N],r[N],
    f[N][N],map[N][N],a[N],
    x,y,z;
inline int max(int a,int b)
{
	return a>b?a:b;
}
inline void maketree(int u)
{
	for(re int i=1; i<=n; i++)
		if(map[u][i]>=0)
		{
			l[u]=i;
			a[i]=map[u][i];
			map[u][i]=map[i][u]=-1;
			maketree(i);
			break;
		}
	for(re int i=1; i<=n; i++)
		if(map[u][i]>=0)
		{
			r[u]=i;
			a[i]=map[u][i];
			map[u][i]=map[i][u]=-1;
			maketree(i);
			break;
		}
}
inline int dp(int i,int j)
{
	if(j==0)return 0;
	if(l[i]==r[i]&&l[i]==0)
		return a[i];
	if(f[i][j]>0)
		return f[i][j];
	for(re int k=0; k<j; k++)
		f[i][j]=max(f[i][j],dp(l[i],k)+dp(r[i],j-k-1)+a[i]);
	return f[i][j];
}
int main()
{
	n=read();
	q=read();
	for(re int i=1; i<=n; i++)
		for(re int j=1; j<=n; j++)
			map[i][j]=-1;
	for(re int i=1; i<n; i++)
	{
		x=read();
		y=read();
		z=read();
		map[x][y]=z;
		map[y][x]=z;
	}
	maketree(1);
	printf("%d\n",dp(1,q+1));
	return 0;
}

