#include <cstdio>
#define ll long long
#define re register
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
const int N=2e5+5;
struct Edge
{
	int next,to;
} edge[N<<1];
int head[N],num_edge;
inline void add_edge(int from,int to)
{
	edge[++num_edge].next=head[from];
	edge[num_edge].to=to;
	head[from]=num_edge;
}
int dfn[N],low[N],dfstime,dep[N];
inline void dfs(int u,int _fa)
{
	dep[u]=dep[_fa]+1;
	dfn[u]=++dfstime;
	for(re int i=head[u]; i; i=edge[i].next)
	{
		int &v=edge[i].to;
		if(v==_fa)
			continue;
		dfs(v,u);
	}
	low[u]=dfstime;
}
#define lowbit(x) (x&(-x))
int n,m,a[N];
int c[N];
inline void add(int x,int y)
{
	for(; x<=n; x+=lowbit(x))
		c[x]+=y;
}
inline int query(int x)
{
	int res=0;
	for(; x; x^=lowbit(x))
		res+=c[x];
	return res;
}
int main()
{
	read(n),read(m);
	for(re int i=1; i<=n; ++i)
		read(a[i]);
	for(re int i=1; i<n; ++i)
	{
		int u,v;
		read(u),read(v);
		add_edge(u,v);
		add_edge(v,u);
	}
	dfs(1,0);
	while(m--)
	{
		int opt;
		read(opt);
		if(opt==1)
		{
			int u,val;
			read(u),read(val);
			if(dep[u]&1)
			{
				add(dfn[u],val);
				add(low[u]+1,-val);
			}
			else
			{
				add(dfn[u],-val);
				add(low[u]+1,val);
			}
		}
		else if(opt==2)
		{
			int u;
			read(u);
			printf("%d\n",a[u]+(dep[u]&1?query(dfn[u]):-query(dfn[u])));
		}
	}
	return 0;
}
