#include<cstdio>
using namespace std;
inline int read()
{
	register int x=0;
	register char s=getchar();
	while(s<'0'||s>'9')s=getchar();
	while(s>='0'&&s<='9')
	{
		x=(x<<1)+(x<<3)+s-'0';
		s=getchar();
	}
	return x;
}
const int CONSTANT=0b001111101001;
int father[CONSTANT],a[CONSTANT][CONSTANT],sum[CONSTANT],n;
inline int find(int x)
{
	if(father[x]!=x)
		return father[x]=find(father[x]);
	return x;
}
int main()
{
	n=read();
	for(register int i=1; i<=n; i++)
	{
		father[i]=i;
		sum[i]=1;
		a[i][0]=read();
		for(register int j=1; j<=a[i][0]; j++)
			a[i][j]=read();
	}
	for(register int i=n; i>=1; i--)
		for(register int j=1; j<=a[i][0]; j++)
			if(a[i][j]>i)
			{
				int fx=find(i),
				    fy=find(a[i][j]);
				if(fx!=fy)
				{
					father[fy]=fx;
					sum[fx]+=sum[fy];
					if(sum[fx]>n>>1)
					{
						printf("%d\n",i);
						return 0;
					}
				}
			}
}
