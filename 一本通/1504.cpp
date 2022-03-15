#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
#define re register
const int N=677,M=100010;
const double e=1e-3;
struct Edge
{
	int to,next;
	double dis;
} edge[M],TE[M];
int head[N],E,tot,
    vis[N],in[N],
    flag[800],
    n;
double dis[N],MaxEdge,aver;
bool PC;
char s[M];
inline void add_edge(int next,int to,double dis)
{
	edge[++E].dis=dis;
	edge[E].next=head[next];
	edge[E].to=to;
	head[next]=E;
}
inline void spfa(int u,int h,double aver)
{
	if(PC)
		return;
	vis[u]=h;
	for(re int i=head[u],v; i; i=edge[i].next)
	{
		v=edge[i].to;
		if(dis[u]+edge[i].dis-aver>dis[v])
		{
			dis[v]=edge[i].dis+dis[u]-aver;
			if(dis[v]>MaxEdge)
			{
				PC=true;
				return;
			}
			if(!vis[v])
				spfa(v,h,aver);
			if(PC)
				return;
			else if(vis[v]==h)
			{
				PC=true;
				return;
			}
		}
	}
	vis[u]=0;
}
inline bool solve(double aver)
{
	PC=false;
	fill(dis,dis+tot+1,0);
	fill(vis,vis+tot+1,0);
	for(re int i=1; i<=tot; i++)
	{
		spfa(i,i,aver);
		if(PC)return true;
	}
	return false;
}
int main()
{
	while(scanf("%d",&n),n)
	{
		E=0;
		tot=0;
		MaxEdge=0;
		fill(head,head+700,0);
		fill(flag,flag+700,0);
		for(re int i=1; i<=n; i++)
		{
			scanf("%s",s);
			int len=strlen(s);
			if(len>MaxEdge)
				MaxEdge=(double)len;
			int a=(s[0]-'a')+(s[1]-'a')*26,
			    b=(s[len-2]-'a')+(s[len-1]-'a')*26;
			if(!flag[a])
				flag[a]=++tot;
			int id1=flag[a];
			if(!flag[b])
				flag[b]=++tot;
			int id2=flag[b];
			add_edge(id1,id2,(double)len);
		}
		MaxEdge*=n;
		double l=0,r=1000,best=-1,mid;
		while(l+(e)<r)
		{
			mid=(l+r)/2;
			if(solve(mid))
			{
				best=mid;
				l=mid;
			}
			else r=mid;
		}
		if(best!=-1)
			printf("%.2lf\n",best);
		else
			printf("No solution\n");
	}

}

