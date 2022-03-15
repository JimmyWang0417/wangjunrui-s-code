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
const int N=3e5+5,M=3e5+5;
int n,m;
struct Edge
{
	int next,to;
} edge[N*2];
int head[N],num_edge;
inline void add_edge(int from,int to)
{
	edge[++num_edge].next=head[from];
	edge[num_edge].to=to;
	head[from]=num_edge;
}
int size[N],son[N];
int dfn[N],dfstime;
int top[N];
int fa[N],dep[N];
inline void initdfs1(int u,int _fa)
{
	fa[u]=_fa;
	dep[u]=dep[_fa]+1;
	size[u]=1;
	for(int i=head[u]; i; i=edge[i].next)
	{
		int &v=edge[i].to;
		if(v==_fa)
			continue;
		initdfs1(v,u);
		size[u]+=size[v];
		if(size[son[u]]<size[v])
			son[u]=v;
	}
}
inline void initdfs2(int u,int topf)
{
	dfn[++dfstime]=topf;
	top[u]=topf;
	if(son[u])
		initdfs2(son[u],topf);
	for(int i=head[u]; i; i=edge[i].next)
	{
		int &v=edge[i].to;
		if(top[v])
			continue;
		initdfs2(v,v);
	}
}
inline int getlca(int x,int y)
{
	while(top[x]!=top[y])
	{
		if(dep[top[x]]<dep[top[y]])
			swap(x,y);
		x=fa[top[x]];
	}
	if(dep[x]>dep[y])
		swap(x,y);
	return x;
}
#define _fa fa[u]
int cnt1[M*2],tmp[M*2],*cnt2=&tmp[M];
vector<int>addg1[N],addg2[N],delg1[N],delg2[N];
inline void addtree(int u)
{
	for(auto v:addg1[u])
		++cnt1[v];
	for(auto v:addg2[u])
		++cnt2[v];
	for(auto v:delg1[u])
		--cnt1[v];
	for(auto v:delg2[u])
		--cnt2[v];

	for(int i=head[u]; i; i=edge[i].next)
	{
		int &v=edge[i].to;
		if(v==_fa)
			continue;
		addtree(v);
	}
}
inline void deltree(int u)
{
	for(auto v:addg1[u])
		--cnt1[v];
	for(auto v:addg2[u])
		--cnt2[v];
	for(auto v:delg1[u])
		++cnt1[v];
	for(auto v:delg2[u])
		++cnt2[v];

	for(int i=head[u]; i; i=edge[i].next)
	{
		int &v=edge[i].to;
		if(v==_fa)
			continue;
		deltree(v);
	}
}
int answer[N];
int a[N];
inline void dfs(int u,bool keep)
{
	for(int i=head[u]; i; i=edge[i].next)
	{
		int &v=edge[i].to;
		if(v==_fa||v==son[u])
			continue;
		dfs(v,false);
	}
	if(son[u])
		dfs(son[u],true);
	for(auto v:addg1[u])
		++cnt1[v];
	for(auto v:addg2[u])
		++cnt2[v];
	for(auto v:delg1[u])
		--cnt1[v];
	for(auto v:delg2[u])
		--cnt2[v];
	for(int i=head[u]; i; i=edge[i].next)
	{
		int &v=edge[i].to;
		if(v==son[u]||v==_fa)
			continue;
		addtree(v);
	}
	answer[u]=cnt1[dep[u]+a[u]]+cnt2[dep[u]-a[u]];
	if(!keep)
		deltree(u);
}
signed main()
{
	read(n,m);
	for(int i=1; i<n; ++i)
	{
		int u,v;
		read(u,v);
		add_edge(u,v);
		add_edge(v,u);
	}
	initdfs1(1,0);
	initdfs2(1,1);
	for(int i=1; i<=n; ++i)
		read(a[i]);
	for(int i=1; i<=m; ++i)
	{
		int x,y;
		read(x,y);
		int lca=getlca(x,y),T=dep[x]+dep[y]-(dep[lca]*2);
//		printf("%d %d %d\n",x,y,lca);
		addg1[x].push_back(dep[x]);
		addg2[y].push_back(dep[y]-T);
		delg1[lca].push_back(dep[x]);
		delg2[fa[lca]].push_back(dep[y]-T);
	}
	dfs(1,0);
	for(int i=1; i<=n; ++i)
		printf("%d ",answer[i]);
	putchar('\n');
	return 0;
}


