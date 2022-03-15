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
inline int min(int a,int b)
{
	return a<b?a:b;
}
inline int max(int a,int b)
{
	return a>b?a:b;
}
const int N=5e6+5,logN=16;
int maxx[N][logN+4],minn[N][logN+4],log[N],x,y,n,q;
int main()
{
	re int i,j;
	n=read();
	q=read();
	log[0]=-1;
	for(i=1; i<=n; i++)
	{
		maxx[i][0]=minn[i][0]=read();
		log[i]=log[i>>1]+1;
	}
	for(j=1; j<=logN; j++)
		for(i=1; i+(1<<j)-1<=n; i++)
		{
			minn[i][j]=min(minn[i][j-1],minn[i+(1<<j-1)][j-1]);
			maxx[i][j]=max(maxx[i][j-1],maxx[i+(1<<j-1)][j-1]);
		}
#define s log[y-x+1]
	for(i=1; i<=q; i++)
	{
		x=read();
		y=read();
		printf("%d\n",max(maxx[x][s],maxx[y-(1<<s)+1][s])
		       -min(minn[x][s],minn[y-(1<<s)+1][s]));
	}
	return 0;
}
