#include<cstdio>
#include<algorithm>
#include<cstring>
#include<queue>
#define re register
using namespace std;
inline int read()
{
	char s=getchar();
	int x=0;
	while(!(s>='0'&&s<='9'))
		s=getchar();
	while(s>='0'&&s<='9')
	{
		x=(x<<1)+(x<<3)+s-'0';
		s=getchar();
	}
	return x;
}
inline int min(int x,int y)
{
	return x<y?x:y;
}
const int N=1e5+5,M=1e6+5;
struct Edge
{
	int next,to;
} edge[M];
int n,m,mo,
    x[M],y[M],
    tot,
    de[N],head[N],
    ue[N],si[N],
    num,top,col,
    dfn[N],low[N],st[N],co[N],
    t,w,ans,dis[N],nu[M],
	e[N],anss;
queue<int>q;
inline void add_edge(int x,int y)
{
	edge[++tot].next=head[x];
	head[x]=tot;
	edge[tot].to=y;
}
inline void Tarjan(int u)
{
	dfn[u]=low[u]=++num;
	st[++top]=u;
	for(re int i=head[u],*v; i; i=edge[i].next)
	{
		v=&edge[i].to;
		if(!dfn[*v])
		{
			Tarjan(*v);
			low[u]=min(low[u],low[*v]);
		}
		else if(!co[*v])
			low[u]=min(low[u],dfn[*v]);
	}
	if(low[u]==dfn[u])
	{
		co[u]=++col;
		++si[col];
		while(st[top]!=u)
		{
			++si[col];
			co[st[top]]=col;
			--top;
		}
		--top;
	}
}
inline bool rule(int a,int b)
{
	return x[a]!=x[b]?x[a]<x[b]:y[a]<y[b];
}
inline void Remove()
{
	for(re int i=1; i<=m; i++)
	{
		nu[i]=i;
		x[i]=co[x[i]];
		y[i]=co[y[i]];
	}
	sort(nu+1,nu+1+m,rule);
}
inline void Build()
{
	tot=0;
	memset(head,0,sizeof(head));
	memset(edge,0,sizeof(edge));
	for(re int i=1,z; i<=m; i++)
	{
		z=nu[i];
		if(x[z]!=y[z]&&(x[z]!=x[nu[i-1]]||y[z]!=y[nu[i-1]]))
		{
			++de[y[z]];
			add_edge(x[z],y[z]);
		}
	}
}
inline void Reset()
{
	for(re int i=1; i<=col; i++)
		if(!de[i])
		{
			q.push(i);
			dis[i]=si[i];
			e[i]=1;
			if(dis[ans]<dis[i])
				ans=i;
		}
}
inline void Topo()
{
	while(!q.empty())
	{
		int u=q.front();
		q.pop();
		for(re int i=head[u],v; i; i=edge[i].next)
		{
			v=edge[i].to;
			--de[v];
			if(dis[v]<dis[u]+si[v])
			{
				dis[v]=dis[u]+si[v];
				e[v]=0;
				if(dis[ans]<dis[v])
					ans=v;
			}
			if(dis[v]==dis[u]+si[v])
				e[v]=(e[v]+e[u])%mo;
			if(!de[v])
				q.push(v);
		}
	}
}
inline void Ask()
{
	for(re int i=1; i<=n; i++)
		if(dis[i]==dis[ans])
			anss=(anss+e[i])%mo;
}
int main()
{
	n=read();
	m=read();
	mo=read();
	for(re int i=1; i<=m; i++)
	{
		x[i]=read();
		y[i]=read();
		add_edge(x[i],y[i]);
	}
	for(re int i=1; i<=n; i++)
		if(!dfn[i])
			Tarjan(i);
	Remove();
	Build();
	Reset();
	Topo();
	Ask();
	printf("%d\n%d\n",dis[ans],anss);
}

