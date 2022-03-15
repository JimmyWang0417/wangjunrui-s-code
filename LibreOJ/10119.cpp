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
inline int max(int a,int b)
{
	return a>b?a:b;
}
const int N=1e6+5,logN=20;
int n,m,log[N],f[N][logN+5],a[N],x,y;
int main()
{
	n=read();
	m=read();
	log[0]=-1;
	for(re int i=1; i<=n; i++)
	{
		f[i][0]=a[i]=read();
		log[i]=log[i>>1]+1;
	}
	for(re int j=1; j<=logN; j++)
		for(re int i=1; i+(1<<j)-1<=n; i++)
			f[i][j]=max(f[i][j-1],f[i+(1<<j-1)][j-1]);
	while(m--)
	{
		x=read();
		y=read();
		printf("%d\n",
		       max(f[x][log[y-x+1]],
		           f[y-(1<<log[y-x+1])+1]
		           [log[y-x+1]]));
	}
	return 0;
}
