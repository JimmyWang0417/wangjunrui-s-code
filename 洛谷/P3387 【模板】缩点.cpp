#include<cstdio>
#include<queue>
#define re register
using namespace std;
queue<int>q;
template<typename T>
inline void read(T&x)
{
	x=0;
	char s=getchar();
	bool f=false;
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
	if(f)
		x=(~x)+1;
}
template<typename T>
inline T min(T&a,T&b)
{
	return a<b?a:b;
}
const int N=1e4+5,M=1e5+5;
struct Edge
{
	int next,to;
} edge[M],e[M];
int dfn[N],low[N],dfstime,belong[N],belongsum,
    head[N],num_edge,st[N],top,sum[N],
    point[N],n,m,h[N],in[N],dis[N],maxx;
inline void add_edge(int from,int to)
{
	edge[++num_edge].next=head[from];
	edge[num_edge].to=to;
	head[from]=num_edge;
}
inline void add_e(int from,int to)
{
	e[++num_edge].next=h[from];
	e[num_edge].to=to;
	h[from]=num_edge;
}
inline void Tarjan(int u)
{
	dfn[u]=low[u]=++dfstime;
	st[++top]=u;
	for(re int i=head[u],*v; i; i=edge[i].next)
	{
		v=&edge[i].to;
		if(!dfn[*v])
		{
			Tarjan(*v);
			low[u]=min(low[*v],low[u]);
		}
		else if(!belong[*v])
			low[u]=min(low[u],dfn[*v]);
	}
	if(low[u]==dfn[u])
	{
		belong[u]=++belongsum;
		sum[belongsum]=point[u];
		while(st[top]!=u)
		{
			belong[st[top]]=belongsum;
			sum[belongsum]+=point[st[top--]];
		}
		top--;
	}
}
int main()
{
	read(n);
	read(m);
	for(re int i=1; i<=n; i++)
		read(point[i]);
	for(re int i=1,x,y; i<=m; i++)
	{
		read(x);
		read(y);
		add_edge(x,y);
	}
	for(re int i=1; i<=n; i++)
		if(!dfn[i])
			Tarjan(i);
	num_edge=0;
	for(re int u=1; u<=n; u++)
		for(re int e=head[u],*v; e; e=edge[e].next)
		{
			v=&edge[e].to;
			if(belong[u]!=belong[*v])
			{
				add_e(belong[u],belong[*v]);
				in[belong[*v]]++;
			}
		}
	for(re int i=1; i<=belongsum; i++)
		if(!in[i])
			q.push(i);
	for(re int i=1; i<=belongsum; i++)
		dis[i]=sum[i];
	while(!q.empty())
	{
		int u=q.front();
		q.pop();
		for(re int i=h[u],*v; i; i=e[i].next)
		{
			v=&e[i].to;
			if(dis[*v]<dis[u]+sum[*v])
			{
				dis[*v]=dis[u]+sum[*v];

			}
			if(!(--in[*v]))
				q.push(*v);
		}
	}
	for(re int i=1; i<=belongsum; i++)
		if(dis[i]>maxx)
			maxx=dis[i];
	printf("%d\n",maxx);
	return 0;
}

