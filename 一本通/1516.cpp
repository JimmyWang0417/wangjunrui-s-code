#include<cstdio>
#define re register
using namespace std;
const int N=1e3+5,M=1e6+5;
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
int de[N],head[N],st[N],co[N],low[N],dfn[N],
    num_edge,top,col,num,n,ans;
struct Edge
{
	int next,to;
} edge[M];
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
		else if((!co[*v])&&(dfn[*v]<low[u]))
			low[u]=dfn[*v];
	}
	if(low[u]==dfn[u])
	{
		co[u]=++col;
		while(st[top]!=u)
		{
			co[st[top]]=col;
			top--;
		}
		--top;
	}
}
int main()
{
	n=read();
	for(re int i=1,j,x; i<=n; i++)
		for(j=1; j<=n; j++)
		{
			x=read();
			if(x==1)
				add_edge(i,j);
		}
	for(re int i=1; i<=n; i++)
		if(!dfn[i])
			Tarjan(i);
	for(re int i=1,j; i<=n; i++)
		for(j=head[i]; j; j=edge[j].next)
			if(co[i]!=co[edge[j].to])
				de[co[edge[j].to]]++;
	for(re int i=1;i<=col;i++)
	if(de[i]==0)
	ans++;
	printf("%d\n",ans);
}
