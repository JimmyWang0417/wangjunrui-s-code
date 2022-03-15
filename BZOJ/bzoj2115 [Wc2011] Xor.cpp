#include <cstdio>
#define re register
#define ll long long
using namespace std;

template <typename T>
inline void read(T&x)
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
}

const int N=5e4+5,M=2e5+5;
struct Edge
{
	int next,to;
	ll dis;
	Edge() {}
	Edge(int n,int t,ll d):next(n),to(t),dis(d) {}
} edge[M];
int head[N],num_edge;
inline void add_edge(int from,int to,ll dis)
{
	edge[++num_edge]=Edge(head[from],to,dis);
	head[from]=num_edge;
}
ll dis[N];
bool vis[N];
ll d[65];
inline void add(ll x)
{
	for(re int i=60; i>=0; --i)
		if((x>>i)&1)
		{
			if(!d[i])
			{
				d[i]=x;
				break;
			}
			else x=x^d[i];
		}
}
inline void dfs(int u,int fa)
{
	vis[u]=true;
	for(re int i=head[u]; i; i=edge[i].next)
	{
		int &v=edge[i].to;
		if(v==fa)
			continue;
		ll &w=edge[i].dis;
		if(!vis[v])
		{
			dis[v]=dis[u]^w;
			dfs(v,u);
		}
		else
			add(dis[u]^dis[v]^w);
	}
}
inline ll getmax(ll x)
{
	ll ans=x;
	for(re int i=60; i>=0; --i)
		if((ans^d[i])>ans)
			ans^=d[i];
	return ans;
}
int n,m;
int main()
{
	read(n),read(m);
	for(re int i=1; i<=m; ++i)
	{
		int u,v;
		ll w;
		read(u),read(v),read(w);
		add_edge(u,v,w);
		add_edge(v,u,w);
	}
	dfs(1,1);
	printf("%lld\n",getmax(dis[n]));
	return 0;
}
