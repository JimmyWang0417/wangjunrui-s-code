#include<cstdio>
#include<queue>
using namespace std;
#define r register
queue<int>q;
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
const int N=1e3+5,M=1e5+5,INF=0x7fffffff/3;
struct Edge
{
	int to,next,dis;
} edge[M];
int head[N],tot,n,m,s,a,b,c,MinEdge;
inline void add_edge(int from,int to,int dis)
{
	edge[++tot].next=head[from];
	edge[tot].to=to;
	edge[tot].dis=dis;
	head[from]=tot;
}
int dis[N];
bool PC,vis[N],exist[N];
inline void spfa(int u)
{
	if(PC)return;
	vis[u]=true;
	for(r int i=head[u],v; i; i=edge[i].next)
	{
		v=edge[i].to;
		if(dis[u]+edge[i].dis<dis[v])
		{
			dis[v]=dis[u]+edge[i].dis;
			if(!vis[v])spfa(v);
			if(PC)return;
			else if(vis[v])
			{
				PC=true;
				return;
			}
		}
	}
	vis[u]=0;
}
int main()
{
	n=read();
	m=read();
	s=read();
	for(r int i=1; i<=m; i++)
	{
		a=read();
		b=read();
		c=read();
		add_edge(a,b,c);
	}
	for(r int i=1; i<=n; i++)
	{
		spfa(i);
		if(PC)
		{
			printf("-1\n");
			return 0;
		}
	}
	for(r int i=1; i<=n; i++)
		dis[i]=INF;
	dis[s]=0;
	q.push(s);
	int u;
	while(!q.empty())
	{
		u=q.front();
		q.pop();
		exist[u]=false;
		for(r int i=head[u],v; i; i=edge[i].next)
		{
			v=edge[i].to;
			if(dis[v]>dis[u]+edge[i].dis)
			{
				dis[v]=dis[u]+edge[i].dis;
				if(!exist[v])
				{
					q.push(v);
					exist[v]=true;
				}
			}
		}
	}
	for(r int i=1; i<=n; i++)
		if(dis[i]==INF)
			printf("NoPath\n");
		else
			printf("%d\n",dis[i]);
}
