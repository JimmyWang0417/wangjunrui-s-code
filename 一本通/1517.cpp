#include<cstdio>
#define re register
using namespace std;
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
const int N=8e3+5,oo=0x3f3f3f3f;
int n,p,m,x,y,money[N],head[N],num_edge,
    dfn[N],low[N],min_money[N],
    st[N],co[N],col,top,
    in[N],num,ans;
struct Edge
{
	int next,to;
} edge[N];
bool vis[N];
inline void add_edge(int from,int to)
{
	edge[++num_edge].next=head[from];
	head[from]=num_edge;
	edge[num_edge].to=to;
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
			if(low[*v]<low[u])
				low[u]=low[*v];
		}
		else if((!co[*v])&&low[u]>dfn[*v])
			low[u]=dfn[*v];
	}
	if(low[u]==dfn[u])
	{
		co[u]=++col;
		min_money[col]=money[u];
		while(st[top]!=u)
		{
			if(min_money[col]>money[st[top]])
				min_money[col]=money[st[top]];
			co[st[top--]]=col;
		}
		top--;
	}
}
inline void bfs(int u)
{
	vis[u]=true;
	for(re int i=head[u],v; i; i=edge[i].next)
	{
		v=edge[i].to;
		if(!vis[v])
			bfs(v);
	}
}
int main()
{
	n=read();
	p=read();
	for(re int i=1; i<=n; i++)
		money[i]=oo;
	for(re int i=1; i<=p; i++)
	{
		x=read();
		money[x]=read();
		vis[x]=true;
	}
	m=read();
	for(re int i=1; i<=m; i++)
	{
		x=read();
		y=read();
		add_edge(x,y);
	}
	for(re int i=1; i<=n; i++)
		if(vis[i]&&money[i]!=oo)
			bfs(i);
	for(re int i=1; i<=n; i++)
		if((!vis[i]))
		{
			printf("NO\n%d\n",i);
			return 0;
		}
	for(re int i=1; i<=n; i++)
		if(!dfn[i])
			Tarjan(i);
	for(re int u=1; u<=n; u++)
		for(re int i=head[u]; i; i=edge[i].next)
			if(co[u]!=co[edge[i].to])
				in[co[edge[i].to]]++;
	for(re int i=1; i<=col; i++)
		if(!in[i])
			ans+=min_money[i];
	printf("YES\n%d\n",ans);
	return 0;
}

