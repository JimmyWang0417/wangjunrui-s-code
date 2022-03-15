#include<cstdio>
using namespace std;
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
int n,head[201],tail[201],f[201][201],ans=0;
int main()
{
	register int i,j,k,len;
	n=read();
	for(i=1; i<=n; i++)
		head[i+n]=head[i]=read();
	for(i=1; i<2*n; i++)
		tail[i]=head[i+1];
	tail[2*n]=head[1];
	for(i=1; i<2*n; i++)
		f[i][i]=0;
	for(len=2; len<=n; len++)
		for(i=1; i<=2*n-len+1; i++)
		{
			j=i+len-1;
			for(k=i; k<j; k++)
				f[i][j]=max(f[i][j],f[i][k]+f[k+1][j]+head[i]*tail[k]*tail[j]);
		}
	for(i=1; i<=n; i++)
		ans=max(ans,f[i][i+n-1]);
	printf("%d\n",ans);
}
