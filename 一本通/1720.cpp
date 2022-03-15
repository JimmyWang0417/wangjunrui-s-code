#include<cstdio>
#include<algorithm>
#include<cstring>
#define fo(i,a,b) for(int i=a;i<=b;i++)
#define N 1010
#define double double
using namespace std;
int head[N],nxt[N*100],to[N*100],tot=0,vis[N],n,m,flag;
double ans=21474354354321578,date[N*100],num[N],avg,f[N];
void add_edge(int x,int y,double z)
{
	nxt[++tot]=head[x];
	head[x]=tot;
	to[tot]=y;
	date[tot]=z;
}
inline void dg(int x)
{
	vis[x]=1;
	for(int i=head[x]; i; i=nxt[i])
	{
		int y=to[i];
		if(flag) return;
		if(f[y]>f[x]+date[i]-avg)
		{
			f[y]=f[x]+date[i]-avg;
			if(vis[y]) flag=1;
			else dg(y);
		}
	}
	vis[x]=0;
	return;
}
inline bool pd(double m)
{
	memset(f,0,sizeof(f));
	memset(vis,0,sizeof(vis));
	flag=0;
	avg=m;
	fo(i,1,n)
	if(!vis[i])
	{
		dg(i);
		if(flag) return 1;
	}
	return 0;
}
int main()
{
	scanf("%d%d",&n,&m);
	fo(i,1,m)
	{
		int x,y;
		double z;
		scanf("%d %d %lf",&x,&y,&z);
		add_edge(x,y,z);
	}
	double l=0,r=10000000;
	while(l+0.00001<r)
	{
		double m=(l+r)/2;
		if(pd(m)) r=m;
		else l=m;
	}
	if(r>=9999999) printf("PaPaFish is laying egg!\n");
	else printf("%.2lf\n",l);
	return 0;
}
