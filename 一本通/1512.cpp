#include<cstdio>
#include<cstring>
#include<queue>
#define re register
using namespace std;
#define N 1010
#define M 1000010
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
int n,ml,md,dis[N],num_edge,a,b,c,head[N];
bool vis[N],PC;
queue<int>q;
struct Edge
{
	int next,to,dis;
} edge[M<<2];
inline void add_edge(int from,int to,int dis)
{
	edge[++num_edge].next=head[from];
	edge[num_edge].to=to;
	edge[num_edge].dis=dis;
	head[from]=num_edge;
}
inline void SPFA(int u)
{
	if(PC)return;
	vis[u]=true;
	for(re int i=head[u],*v,*w; i; i=edge[i].next)
	{
		v=&edge[i].to;
		w=&edge[i].dis;
		if(dis[*v]<dis[u]+(*w))
		{
			dis[*v]=dis[u]+(*w);
			if(vis[*v])
			{
				PC=true;
				return;
			}
			else
				SPFA(*v);
			if(PC)
				return;
		}
	}
	vis[u]=false;
}
inline bool dfs(int x)
{
	if(x==1)return true;
	vis[x]=true;
	for(re int i=head[x],*v; i; i=edge[i].next)
	{
		v=&edge[i].to;
		if(!vis[*v])
			if(dfs(*v))
				return true;
	}
	return false;
}
int main()
{
	n=read();
	ml=read();
	md=read();
	for(re int i=1; i<=ml; i++)
	{
		a=read();
		b=read();
		c=read();
		add_edge(b,a,-c);
	}
	for(re int i=1; i<=md; i++)
	{
		a=read();
		b=read();
		c=read();
		add_edge(a,b,c);
	}
	for(re int i=1; i<=n; i++)
	{
		SPFA(i);
		if(PC)
		{
			printf("-1\n");
			return 0;
		}
	}
	memset(vis,0,sizeof(vis));
	if(!dfs(n))
	{
		printf("-2\n");
		return 0;
	}
	memset(vis,0,sizeof(vis));
	memset(dis,128,sizeof(dis));
	q.push(n);
	dis[n]=0;
	while(!q.empty())
	{
		int u=q.front();
		q.pop();
		vis[u]=false;
		for(re int i=head[u],*v,*w; i; i=edge[i].next)
		{
			v=&edge[i].to;
			w=&edge[i].dis;
			if(dis[*v]<dis[u]+(*w))
			{
				dis[*v]=dis[u]+(*w);
				if(!vis[*v])
				{
					vis[*v]=true;
					q.push(*v);
				}
			}
		}
	}
	printf("%d\n",~(dis[1]-1));
	return 0;
}
