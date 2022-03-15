#include <cstdio>
#include <vector>
#include <cstring>
#include <algorithm>
#define re register
#define ll long long
using namespace std;
template <typename T>
inline void read(T &x)
{
	x=0;
	char s=(char)getchar();
	bool flag=false;
	while(s<'0'||s>'9')
	{
		if(s=='-')
			flag=true;
		s=(char)getchar();
	}
	while(s>='0'&&s<='9')
	{
		x=(x<<1)+(x<<3)+(s^'0');
		s=(char)getchar();
	}
	if(flag)
		x=~x+1;
	return;
}
const int N=105;
struct Edge
{
	int next,to;
} edge[N*N];
int head[N],num_edge;
inline void add_edge(int from,int to)
{
	edge[++num_edge].next=head[from];
	edge[num_edge].to=to;
	head[from]=num_edge;
}
int n;
int dfn[N],low[N],dfstime;
bool cut[N],tag[N];
int a,b;
inline void Tarjan(int u,int fa)
{
	low[u]=dfn[u]=++dfstime;
	tag[u]=(u==b);
	for(re int i=head[u]; i; i=edge[i].next)
	{
		int &v=edge[i].to;
		if(v==fa)
			continue;
		if(!dfn[v])
		{
			Tarjan(v,u);
			tag[u]|=tag[v];
			if(low[v]>=dfn[u]&&u!=a&&tag[v])
				cut[u]=true;
			low[u]=min(low[u],low[v]);
		}
		else
			low[u]=min(low[u],dfn[v]);
	}
}
int main()
{
	read(n);
	int u,v;
	while(read(u),read(v),u||v)
	{
		add_edge(u,v);
		add_edge(v,u);
	}
	read(a),read(b);
	Tarjan(a,a);
	for(re int i=1; i<=n; ++i)
		if(cut[i])
		{
			printf("%d\n",i);
			return 0;
		}
	printf("No solution\n");
	return 0;
}
