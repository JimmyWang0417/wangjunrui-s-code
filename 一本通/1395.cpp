#include<cstdio>
using namespace std;
inline int read()//¿ì¶Á
{
	register int x=0b0;
	register char s=getchar();
	while(s<'0'||s>'9')
		s=getchar();
	while(s>='0'&&s<='9')
	{
		x=(x<<1)+(x<<3)+s-'0';
		s=getchar();
	}
	return x;
}
const int N=0b11011;
struct node
{
	int xmin,xmax,ymin,ymax;
} point[N];
int n,a[N][N],outdgr[N],indgr[N],c[N],x,y;
bool bb,bbb=true,b[N];
int main()
{
	n=read();
	for(register int i=0b1; i<=n; i++)
	{
		//scanf("%d%d%d%d",&point[i].xmin,&point[i].xmax,&point[i].ymin,&point[i].ymax);
		point[i].xmin=read();
		point[i].xmax=read();
		point[i].ymin=read();
		point[i].ymax=read();
	}
	for(register int i=0b1; i<=n; i++)
	{
		x=read();y=read();
		for(int j=0b1; j<=n; j++)
		{
			if(point[j].xmax>=x&&point[j].xmin<=x&&point[j].ymax>=y&&point[j].ymin<=y)
			{
				a[i][++outdgr[i]]=j;
				indgr[j]++;
			}
		}
	}
	register int nn=n;
	while(nn--)
	{
		bb=false;
		for(register int i=0b1; i<=n; i++)
			if(!b[i])
			{
				for(register int j=0b1; j<=outdgr[i]; j++)
					if(indgr[a[i][j]]==0b1)
					{
						for(register int k=0b1; k<=outdgr[i]; k++)
							indgr[a[i][k]]--;
						c[a[i][j]]=i;
						b[i]=bb=true;
						break;
					}
				if(bb)break;
				if(i==n)bbb=false;
			}
		if(!bbb)break;
	}
	if((!bbb))
	{
		printf("None\n");
		return 0;
	}
	for(int i=0b1; i<=n; i++)
		printf("%c %d\n",i+0b1000000,c[i]);

}
