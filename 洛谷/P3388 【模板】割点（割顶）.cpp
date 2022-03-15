#include<iostream>
#include<cstring>
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
const int N=20010,M=100010<<1;
struct Edge
{
	int next,to;
} edge[M];
int dfstime,num_edge,ans,head[N],n,dfn[N],low[N],root,x,y,m;
bool cut[N];
inline void add_edge(int from,int to)
{
	edge[++num_edge].next=head[from];
	head[from]=num_edge;
	edge[num_edge].to=to;
}
inline void Tarjan(int u,int root)
{
	dfn[u]=low[u]=++dfstime;
	int cnt=0;
	for(re int i=head[u],v; i; i=edge[i].next)
	{
		v=edge[i].to;
		if(!dfn[v])
		{
			cnt++;
			Tarjan(v,root);
			low[u]=min(low[u],low[v]);
			cut[u]=cut[u]||(u!=root&&dfn[u]<=low[v])||(u==root&&cnt>1);
		}
		else
			low[u]=min(low[u],dfn[v]);
	}
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
		add_edge(y,x);
	}
	for(re int i=1; i<=n; i++)
		if(!dfn[i])
			Tarjan(i,i);
	for(re int i=1; i<=n; i++)
		if(cut[i])
			ans++;
	printf("%d\n",ans);
	for(re int i=1; i<=n; i++)
		if(cut[i])
			printf("%d ",i);
	putchar('\n');
}
