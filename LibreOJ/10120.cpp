#include<cstdio>
#define re register
using namespace std;
inline int min(int a,int b)
{
	return a<b?a:b;
}
inline int max(int a,int b)
{
	return a>b?a:b;
}
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
const int N=1e5+5,logN=17;
int log[N]= {-1},maxx[N][logN+3],minn[N][logN+3],a[N],n,k;
int main()
{
	re int i,j;
	n=read();
	k=read();
	for(i=1; i<=n; i++)
		for(j=1; j<=logN; j++)
			minn[i][j]=0x7fffffff;
	for(i=1; i<=n; i++)
	{
		minn[i][0]=maxx[i][0]=a[i]=read();
		log[i]=log[i>>1]+1;
	}
	for(j=1; j<=logN; j++)
		for(i=1; i+(1<<j)-1<=n; i++)
		{
			maxx[i][j]=max(maxx[i][j-1],maxx[i+(1<<j-1)][j-1]);
			minn[i][j]=min(minn[i][j-1],minn[i+(1<<j-1)][j-1]);
		}
#define x i
#define y (i+k-1)
#define s log[y-x+1]
	for(i=1; i<=n-k+1; i++)
		printf("%d %d\n",max(maxx[x][s],maxx[y-(1<<s)+1][s]),
		       min(minn[x][s],minn[y-(1<<s)+1][s]));
	return 0;
}
