#include<cstdio>
#include<queue>
using namespace std;
#define INF 999999999
#define N 1000003
#define re register
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
inline int min(const int&a,const int &b)
{
	return a<b?a:b;
}
inline int max(const int&a,const int&b)
{
	return a>b?a:b;
}
struct Edge
{
	int next,to,dis;
} edge[N*3];
int num_edge,head[N],n,dis[N],minn,maxx,u,v,w;
bool exist[N];
inline void add_edge(int from,int to,int dis)
{
	edge[++num_edge].next=head[from];
	head[from]=num_edge;
	edge[num_edge].to=to;
	edge[num_edge].dis=dis;
}
inline int SPFA(const int&start)
{
	queue<int>q;
	for(re int i=minn; i<=maxx; i++)
		dis[i]=-INF;
	dis[start]=0;
	exist[start]=true;
	q.push(start);
	do
	{
		int u=q.front();
		q.pop();
		for(re int i=head[u]; i; i=edge[i].next)
		{
			int *v=&edge[i].to,*w=&edge[i].dis;
			if(dis[*v]<dis[u]+(*w))
			{
				dis[*v]=dis[u]+(*w);
				if(!exist[*v])
				{
					exist[*v]=true;
					q.push(*v);
				}
			}
		}
		exist[u]=false;
	}
	while(!q.empty());
	return dis[maxx];
}
int main()
{
	n=read();
	minn=INF;
	maxx=-1;
	for(re int i=1; i<=n; i++)
	{
		u=read();
		v=read();
		w=read();
		add_edge(u,v+1,w);
		maxx=max(v+1,maxx);
		minn=min(u,minn);
	}
	for(re int i=minn; i<=maxx; i++)
	{
		add_edge(i,i+1,0);
		add_edge(i+1,i,-1);
	}
	printf("%d\n",SPFA(minn));
	return 0;
}

