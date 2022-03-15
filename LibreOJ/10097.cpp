#include<cstdio>
#include<queue>
#define re register
using namespace std;
inline int change(int x)
{
	return x%2==1?x+1:x-1;
}
queue<int>q;
const int N=8010<<1,M=20010<<2;
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
} edge[M],e[M];
int n,m,head[N],dfn[N],low[N],
    co[N],col,st[N],top,
    a,b,num_edge,dfstime,
    op[N],in[N];
inline void add_edge(int from,int to,int head[])
{
	edge[++num_edge].next=head[from];
	edge[num_edge].to=to;
	head[from]=num_edge;
}
inline int min(int a,int b)
{
	return a<b?a:b;
}
inline void Tarjan(int u)
{
	dfn[u]=low[u]=++dfstime;
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
		while(st[top]!=u)
			co[st[top--]]=col;
		top--;
	}
}
bool ans[N];
int mark[N],first[N];
int main()
{
	n=read();
	n<<=1;
	m=read();
	for(re int i=1; i<=m; i++)
	{
		a=read();
		b=read();
		add_edge(a,change(b),head);
		add_edge(b,change(a),head);
	}
	for(re int i=1; i<=n; i++)
		if(!dfn[i])
			Tarjan(i);
	for(re int i=1; i<=n; i+=2)
	{
		if(co[i]==co[i+1])
		{
			printf("NIE\n");
			return 0;
		}
		op[co[i]]=co[i+1];
		op[co[i+1]]=co[i];
	}
	for(re int u=1; u<=n; u++)
		for(re int i=head[u],v; i; i=edge[i].next)
		{
			v=edge[i].to;
			if(co[u]!=co[v])
			{
				add_edge(co[v],co[u],first);
				in[co[u]]++;
			}
		}
	for(re int i=1; i<=col; i++)
		if(!in[i])
			q.push(i);
	while(!q.empty())
	{
		int u=q.front();
		q.pop();
		if(!mark[u])
		{
			mark[u]=1;
			mark[op[u]]=-1;
		}
		for(re int i=first[u],v; i; i=edge[i].next)
		{
			v=edge[i].to;
			in[v]--;
			if(!in[v])
				q.push(v);
		}
	}
	for(re int i=1; i<=n; i+=2)
		if(mark[co[i]]==1)
			ans[i]=true;
	for(re int i=1; i<=n; i+=2)
		if(ans[i])
			printf("%d\n",i);
		else
			printf("%d\n",i+1);
	return 0;
}

