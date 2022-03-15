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
const int N=5e3+5,M=1e4+5;
inline int min(int a,int b)
{
	return a<b?a:b;
}
struct Edge
{
	int next,to,op;
} edge[M<<1];
int dfn[N],low[N],
    stack[N],con[N],
    belong[N],head[N],
    prt[N],
    n,m,num_edge,top,bcc,ans,cnt;
bool vis[M<<1];
inline void add_edge(int x,int y)
{
	edge[++num_edge].next=head[x];
	edge[num_edge].to=y;
	head[x]=num_edge;
	edge[num_edge].op=num_edge+1;
	edge[++num_edge].next=head[y];
	edge[num_edge].to=x;
	head[y]=num_edge;
	edge[num_edge].op=num_edge-1;
}
inline void Tarjan(int u)
{
	dfn[u]=low[u]=++cnt;
	stack[++top]=u;
	for(re int i=head[u],v; i; i=edge[i].next)
		if(!vis[edge[i].op])
		{
			vis[i]=true;
			v=edge[i].to;
			if(!dfn[v])
			{
				Tarjan(v);
				low[u]=min(low[u],low[v]);
			}
			else
				low[u]=min(low[u],dfn[v]);
		}
		else vis[i]=1;
	if(low[u]==dfn[u])
	{
		int i;
		bcc++;
		do
		{
			i=stack[top--];
			belong[i]=bcc;
		}
		while(i!=u);
	}
}
inline void statis()
{
	re int i,j,k;
	for(i=1; i<=n; i++)
		for(k=head[i];k;k=edge[k].next)
			if(vis[edge[k].op])
			{
				vis[k]=0;
				j=edge[k].to;
				if(belong[i]!=belong[j])
				{
					con[belong[i]]++;
					con[belong[j]]++;
				}
			}
			else
				vis[k]=0;
	for(i=1; i<=bcc; i++)
		if(con[i]==1)
			ans++;
	printf("%d\n",(ans+1)/2);
}
int main()
{
	n=read();
	m=read();
	for(re int i=1,x,y; i<=m; i++)
	{
		x=read();
		y=read();
		add_edge(x,y);
	}
	Tarjan(1);
	statis();
}

