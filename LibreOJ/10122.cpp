#include<cstdio>
#define re register
using namespace std;
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
const int N=2e5+5,logN=18;
int log[N]= {-1},f[N][logN+3],a[N],n,m,x,y;
int main()
{
	re int i,j;
	n=read();
	for(i=1; i<=n; i++)
	{
		f[i][0]=a[i]=read();
		log[i]=log[i>>1]+1;
	}
	for(j=1; j<=logN; j++)
		for(i=1; i+(1<<j)-1<=n; i++)
			f[i][j]=max(f[i][j-1],f[i+(1<<j-1)][j-1]);
	m=read();
#define s log[y-x+1]
	for(i=1; i<=m; i++)
	{
		x=read();
		y=read();
		printf("%d\n",max(f[x][s],f[y-(1<<s)+1][s]));
	}
	return 0;
}
