#include <bits/stdc++.h>
#define lowbit(x) ((x)&(-(x)))
#define re register
#define ll long long
#define ull unsigned long long
#define rep(i,a,b) for(re int i=a;i<=b;++i)
#define per(i,a,b) for(re int i=a;i>=b;--i)
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
template<typename T,typename ...T1>
inline void read(T&x,T1&...x1)
{
	read(x);
	read(x1...);
}
template<typename T>
inline void clear(T*array,int l,int r,int val)
{
	memset(&array[l],val,sizeof(T)*(r-l+1));
}
using namespace std;
const int N=2e5+5;
int n,m,q;
struct Edge
{
	int next,to;
} edge[N*2];
int head[N],num_edge=1;
inline void add_edge(int from,int to)
{
	edge[++num_edge].next=head[from];
	edge[num_edge].to=to;
	head[from]=num_edge;
}
int dfn[N],low[N],dfstime;
int st[N],top;
int belong[N],color;
inline void tarjan(int u,int lasedge)
{
	dfn[u]=low[u]=++dfstime;
	st[++top]=u;
//	printf("%d %d\n",u,_fa);
	for(int i=head[u]; i; i=edge[i].next)
	{
		if(i==(lasedge^1))
			continue;
		int &v=edge[i].to;
		if(!dfn[v])
		{
			tarjan(v,i);
			low[u]=min(low[u],low[v]);
		}
		else
			low[u]=min(low[u],dfn[v]);
	}
	if(dfn[u]==low[u])
	{
		belong[u]=++color;
		while(st[top]!=u)
			belong[st[top--]]=color;
		--top;
	}
}
vector<int>g[N];
int Log[N];
int dep[N];
int fa[N][25];
inline void dfs(int u,int _fa)
{
	dep[u]=dep[_fa]+1;
	fa[u][0]=_fa;
	for(int i=0; i<Log[dep[u]]; ++i)
		fa[u][i+1]=fa[fa[u][i]][i];
	for(auto v:g[u])
	{
		if(v==_fa)
			continue;
		dfs(v,u);
	}
}
int father[N],col[N];
inline int find(int x)
{
	return father[x]==x?x:father[x]=find(father[x]);
}
inline int getlca(int u,int v)
{
	if(dep[u]<dep[v])
		swap(u,v);
	for(int i=Log[dep[u]]; i>=0; --i)
		if(dep[fa[u][i]]>=dep[v])
			u=fa[u][i];
	if(u==v)
		return u;
	for(int i=Log[dep[u]]; i>=0; --i)
		if(fa[u][i]!=fa[v][i])
		{
			u=fa[u][i];
			v=fa[v][i];
		}
	return fa[u][0];
}
inline void work()
{
	int u,v;
	read(u,v);
	u=belong[u],v=belong[v];
	int lca=getlca(u,v);
	if(!lca)
	{
		printf("No\n");
		exit(0);
	}
	if(u==v)
		return;
	if((col[find(u)]==2&&u!=lca)||(col[find(v)]==1&&v!=lca))
	{
		printf("No\n");
		exit(0);
	}
	if(u!=lca)
		col[find(u)]=1;
	if(v!=lca)
		col[find(v)]=2;
	while(find(u)!=find(lca))
	{
		if(find(fa[find(u)][0])!=find(lca))
		{
			if(col[find(fa[find(u)][0])]==2)
			{
				printf("No\n");
				exit(0);
			}
			father[find(u)]=find(fa[find(u)][0]);
			col[find(u)]=1;
		}
		u=find(fa[find(u)][0]);
	}
	while(find(v)!=find(lca))
	{
		if(find(fa[find(v)][0])!=find(lca))
		{
			if(col[find(fa[find(v)][0])]==1)
			{
				printf("No\n");
				exit(0);
			}
			father[find(v)]=find(fa[find(v)][0]);
			col[find(v)]=2;
		}
		v=find(fa[find(v)][0]);
	}
}
signed main()
{
	read(n,m,q);
	for(int i=1; i<=m; ++i)
	{
		int u,v;
		read(u,v);
		add_edge(u,v);
		add_edge(v,u);
	}
	for(int i=1; i<=n; ++i)
		if(!dfn[i])
			tarjan(i,0);
	for(int i=1; i<=color; ++i)
		father[i]=i;
	for(int u=1; u<=n; ++u)
		for(int i=head[u]; i; i=edge[i].next)
		{
			int &v=edge[i].to;
			if(belong[u]==belong[v])
				continue;
			g[belong[u]].push_back(belong[v]);
		}
	Log[0]=-1;
	for(int i=1; i<=color; ++i)
		Log[i]=Log[i>>1]+1;
	for(int i=1; i<=color; ++i)
		if(!dep[i])
			dfs(i,0);
	while(q--)
		work();
	printf("Yes\n");
	return 0;
}
