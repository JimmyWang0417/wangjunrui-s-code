#include<cstdio>
#include<bitset>
#include<algorithm>
#define re register
#define con const
using namespace std;
template<typename T>
inline void read(T&x)
{
	x=0;
	char s=getchar();
	bool f=false;
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
	if(f)
		x=(~x)+1;
}
const int N=300+1500+10,M=300*1500+10;
bitset<N>vis;
int dfstime,dfn[N],low[N],g[N][N],head[N],num_edge,f[N],st[N],co[N],col,n,m,top,ans;
struct Edge
{
	int next,to;
} edge[M];
inline void add_edge(con int &from,con int &to)
{
	edge[++num_edge].next=head[from];
	head[from]=num_edge;
	edge[num_edge].to=to;
}
inline bool dfs(con int &x)
{
	for(re int i=n+1; i<=n+m; i++)
		if(g[x][i])
		{
			if(vis[i])
				continue;
			vis[i]=true;
			if(!f[i]||dfs(f[i]))
			{
				f[i]=x;
				return true;
			}
		}
	return false;
}
inline void Tarjan(con int &u)
{
	dfn[u]=low[u]=++dfstime;
	st[++top]=u;
	for(re int i=head[u]; i; i=edge[i].next)
	{
		int &v=edge[i].to;
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
int main()
{
	read(n);
	read(m);
	for(re int i=1; i<=n; i++)
	{
		for(re int j=1+n; j<=m+n; j++)
			scanf("%1d",&g[i][j]);
	}
	/*for(re int i=1; i<=n; i++)
	{
		for(re int j=1; j<=m; j++)
		{
			putchar(g[i][j+n]+'0');
		}
		putchar('\n');
	}*/
	for(re int i=1; i<=n; i++)
	{
		ans+=dfs(i);
		vis.reset();
	}
	if(ans<n)
	{
		for(re int i=1; i<=n; i++)
		{
			for(re int j=1; j<=m; j++)
				putchar('1');
			putchar('\n');
		}
		//putchar('9');
		return 0;
	}
	for(re int i=1; i<=n; i++)
		for(re int j=n+1; j<=n+m; j++)
			if(g[i][j])
				f[j]==i?add_edge(i,j):add_edge(j,i);
	for(re int i=n+1; i<=n+m; i++)
		f[i]?add_edge(i,m+n+1):add_edge(n+m+1,i);
	for(re int i=1; i<=n+m+1; i++)
		if(!dfn[i])
			Tarjan(i);
	for(re int i=1; i<=n; i++)
	{
		for(re int j=n+1; j<=n+m; j++)
			if(g[i][j]&&(co[i]==co[j]||f[j]==i))
				putchar('0');
			else putchar('1');
		putchar('\n');
	}
	return 0;
}

