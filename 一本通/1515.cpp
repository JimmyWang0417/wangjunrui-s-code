#include<cstdio>
#define re register
const int N=110,M=10010;
using namespace std;
int n,x,head[N],num_edge,
    dfn[N],low[N],num,
    st[N],co[N],col,top,
    in[N],out[N],
    ans1,ans2;
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
		else if((!co[*v])&&low[u]>dfn[*v])
			low[u]=dfn[*v];
	}
	if(low[u]==dfn[u])
	{
		co[u]=++col;
		while(st[top]!=u)
			co[st[top--]]=col;
		top--;
	}
}
int main()
{
	scanf("%d",&n);
	for(re int i=1; i<=n; i++)
	{
		scanf("%d",&x);
		while(x!=0)
		{
			add_edge(i,x);
			scanf("%d",&x);
		}
	}
	for(re int i=1; i<=n; i++)
		if(!dfn[i])
			Tarjan(i);
	for(re int u=1; u<=n; u++)
		for(re int i=head[u]; i; i=edge[i].next)
			if(co[u]!=co[edge[i].to])
			{
				in[co[edge[i].to]]++;
				out[co[u]]++;
			}
	for(re int i=1; i<=col; i++)
	{
		if(!in[i])
			ans1++;
		if(!out[i])
			ans2++;
	}
	printf("%d\n%d\n",ans1,col==1?0:(ans2>ans1?ans2:ans1));
	return 0;
}

