#include <cstdio>
#include <algorithm>
#define re register
using namespace std;
template<typename T>
inline void read(T&x)
{
	x=0;
	char s=(char)getchar();
	bool f=false;
	while(!(s>='0'&&s<='9'))
	{
		if(s=='-')
			f=true;
		s=(char)getchar();
	}
	while(s>='0'&&s<='9')
	{
		x=(x<<1)+(x<<3)+s-'0';
		s=(char)getchar();
	}
	if(f)
		x=(~x)+1;
}
const int N=1e5+5,M=5e5+5;
struct Edge
{
	int next,to;
} edge[M];
int head[N],num_edge;
inline void add_edge(int from,int to)
{
	edge[++num_edge].next=head[from];
	edge[num_edge].to=to;
	head[from]=num_edge;
}
int st[N],top;
int dfn[N],low[N],dfstime,belong[N],color;
inline void Tarjan(int u)
{
	st[++top]=u;
	dfn[u]=low[u]=++dfstime;
	for(re int i=head[u]; i; i=edge[i].next)
	{
		int &v=edge[i].to;
		if(!dfn[v])
		{
			Tarjan(v);
			low[u]=min(low[u],low[v]);
		}
		else if(!belong[v])
			low[u]=min(low[u],dfn[v]);
	}
	if(low[u]==dfn[u])
	{
		++color;
		while(st[top]!=u)
			belong[st[top--]]=color;
		belong[st[top--]]=color;
	}
}
int n,m;
int q[N],qs;
int in[N];
int main()
{
	read(n),read(m);
	for(re int i=1; i<=m; ++i)
	{
		int u,v;
		read(u),read(v);
		add_edge(u,v);
	}
//	memset(head+1,num_edge=0,sizeof(int)*n);
	for(re int i=1; i<=n; ++i)
		if(!dfn[i])
			Tarjan(i);
	for(re int u=1; u<=n; ++u)
		for(re int i=head[u]; i; i=edge[i].next)
		{
			int &v=edge[i].to;
			if(belong[u]!=belong[v])
				++in[belong[v]];
		}
	int ans=0;
	for(re int i=1; i<=color; ++i)
		if(!in[i])
			++ans;
	printf("%d\n",ans);
	return 0;
}
