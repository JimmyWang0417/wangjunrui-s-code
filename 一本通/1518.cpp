#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#define re register
using namespace std;
const int N=5e5+5;
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
inline int min(int a,int b)
{
	return a<b?a:b;
}
int n,m,money[N],allmoney[N],
    co[N],col,st[N],top,dfn[N],low[N],num,num_edge,
    head[N],s;
queue<int>q;
struct Edge
{
	int next,to;
} edge[N];
inline void add_edge(int from,int to)
{
	edge[++num_edge].next=head[from];
	edge[num_edge].to=to;
	head[from]=num_edge;
}
inline void Tarjan(int u)
{
	dfn[u]=low[u]=++num;
	st[++top]=u;
	for(re int i=head[u],v; i; i=edge[i].next)
	{
		v=edge[i].to;
		if(!dfn[v])
		{
			Tarjan(v);
			low[u]=min(low[u],low[v]);
		}
		else if(!co[v])
			low[u]=min(low[u],dfn[v]);
	}
	if(low[u]==dfn[u])
	{
		co[u]=++col;
		allmoney[col]+=money[u];
		while(st[top]!=u)
		{
			allmoney[col]+=money[st[top]];
			co[st[top]]=col;
			top--;
		}
		top--;
	}
}
int x[N],y[N],nu[N],de[N],ans,dis[N];
inline bool comp(int a,int b)
{
	return x[a]!=x[b]?(x[a]<x[b]):y[a]<y[b];
}
int main()
{
	n=read();
	m=read();
	for(re int i=1; i<=m; i++)
	{
		x[i]=read();
		y[i]=read();
		add_edge(x[i],y[i]);
	}
	for(re int i=1; i<=n; i++)
		money[i]=read();
	for(re int i=1; i<=n; i++)
		if(!dfn[i])
			Tarjan(i);
	for(re int i=1; i<=m; i++)
	{
		nu[i]=i;
		x[i]=co[x[i]];
		y[i]=co[y[i]];
	}
	sort(nu+1,nu+1+col,comp);
	memset(head,0,sizeof(head));
	memset(edge,0,sizeof(edge));
	num_edge=0;
	for(re int i=1,tot=0; i<=m; i++)
		if(x[nu[i]]!=y[nu[i]]&&(x[nu[i]]!=x[nu[i-1]]||y[nu[i]]!=y[nu[i-1]]))
		{
			++de[y[nu[i]]];
			add_edge(x[nu[i]],y[nu[i]]);
		}
	memset(dis,0,sizeof(dis));
	s=read();
	q.push(co[s]);
	dis[co[s]]=allmoney[co[s]];
	while(!q.empty())
	{
		int u=q.front();
		q.pop();
		for(re int i=head[u],v; i; i=edge[i].next)
		{
			v=edge[i].to;
			--de[v];
			if(dis[v]<dis[u]+allmoney[v])
				dis[v]=dis[u]+allmoney[v];
			if(de[v]==0)
				q.push(v);
		}
	}
	s=read();
	for(re int i=1,x; i<=s; i++)
	{
		x=read();
		if(dis[co[x]]>ans)
			ans=dis[co[x]];
	}
	printf("%d\n",ans);
	return 0;
}

