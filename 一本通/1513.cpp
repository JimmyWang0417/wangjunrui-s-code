#include<cstdio>
#define re register
const int N=1e5+5,M=5e5+5;
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
struct Edge
{
	int next,to;
} edge[M];
int col,num,dfn[N],low[N],in[N],point[N],
    num_edge,co[N],n,m,top,st[N],
    head[N],ans,hh;
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
		point[col]++;
		while(st[top]!=u)
		{
			++point[col];
			co[st[top]]=col;
			top--;
		}
		--top;
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
		add_edge(y,x);
	}
	for(re int i=1; i<=n; i++)
		if(!dfn[i])
			Tarjan(i);
	for(re int i=1; i<=n; i++)
		for(re int j=head[i]; j; j=edge[j].next)
			if(co[i]!=co[edge[j].to])
				in[co[edge[j].to]]++;
	for(re int i=1; i<=col; i++)
		if(!in[i])
		{
			ans=point[i];hh++;
		}
	if(hh!=1)
		ans=0;
	printf("%d\n",ans);
	return 0;
}

