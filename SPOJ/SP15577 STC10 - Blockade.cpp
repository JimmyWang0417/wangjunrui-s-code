#include <cstdio>
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
const int N=1e5+5,M=1e6+5;
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
int n,m;
int low[N],dfn[N],size[N],dfstime;
ll ans[N];
inline void Tarjan(int u,int fa)
{
	int sum=0;
	size[u]=1;
	low[u]=dfn[u]=++dfstime;
	for(re int i=head[u]; i; i=edge[i].next)
	{
		int &v=edge[i].to;
		if(v==fa)
			continue;
		if(!dfn[v])
		{
			Tarjan(v,u);
			size[u]+=size[v];
			if(low[v]>=dfn[u])
			{
				ans[u]+=1ll*size[v]*sum;
				sum+=size[v];
			}
			low[u]=min(low[u],low[v]);
		}
		else low[u]=min(low[u],dfn[v]);
	}
	ans[u]+=1ll*sum*(n-sum-1);
}
int main()
{
	read(n),read(m);
	for(re int i=1; i<=m; ++i)
	{
		int u,v;
		read(u),read(v);
		add_edge(u,v);
		add_edge(v,u);
	}
	Tarjan(1,1);
	for(re int i=1; i<=n; ++i)
		printf("%lld\n",(ans[i]+n-1)<<1);
	return 0;
}
