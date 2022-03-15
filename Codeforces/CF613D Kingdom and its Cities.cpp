#include <cstdio>
#include <cstring>
#include <algorithm>
#define re register
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
const int N=1e5+5;
int head[N],num_edge;
struct Edge
{
	int next,to;
	Edge() {}
	Edge(int nownext,int nowto):next(nownext),to(nowto) {}
} edge[N<<1];
inline void add_edge(int from,int to)
{
	edge[++num_edge]=Edge(head[from],to);
	head[from]=num_edge;
}
int dep[N],son[N],top[N],size[N],fa[N],dfn[N],dfstime;
inline void dfs1(int u,int father)
{
	fa[u]=father;
	dep[u]=dep[father]+1;
	size[u]=1;
	for(re int i=head[u]; i; i=edge[i].next)
	{
		int &v=edge[i].to;
		if(v==father)
			continue;
		dfs1(v,u);
		size[u]+=size[v];
		if(size[v]>size[son[u]])
			son[u]=v;
	}
}
inline void dfs2(int u,int tp)
{
	dfn[u]=++dfstime;
	top[u]=tp;
	if(!son[u])
		return;
	dfs2(son[u],tp);
	for(re int i=head[u]; i; i=edge[i].next)
	{
		int &v=edge[i].to;
		if(top[v])
			continue;
		dfs2(v,v);
	}
}
inline int LCA(int x,int y)
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
int st[N],tp;
inline void insert(int u)
{
	if(tp<=1)
	{
		st[++tp]=u;
		return;
	}
	int lca=LCA(st[tp],u);
	while(tp>1&&dfn[lca]<=dfn[st[tp-1]])
	{
		add_edge(st[tp-1],st[tp]);
		--tp;
	}
	if(lca!=st[tp])
	{
		add_edge(lca,st[tp]);
		st[tp]=lca;
	}
	st[++tp]=u;
}
int n,m,a[N];
int tag[N];
int ans;
inline void getans(int u)
{
	if(tag[u])
		for(re int i=head[u]; i; i=edge[i].next)
		{
			int &v=edge[i].to;
			getans(v);
			if(tag[v])
			{
				tag[v]=0;
				++ans;
			}
		}
	else
	{
		for(re int i=head[u]; i; i=edge[i].next)
		{
			int &v=edge[i].to;
			getans(v);
			tag[u]+=tag[v];
			tag[v]=0;
		}
		if(tag[u]>1)
		{
			tag[u]=0;
			++ans;
		}
	}
	head[u]=0;
}
inline bool cmp(const int aa,const int b)
{
	return dfn[aa]<dfn[b];
}
inline void work()
{
//	memeset(head+1,num_edge=0,sizeof(int)*n);
	read(m);
	for(re int i=1; i<=m; ++i)
	{
		read(a[i]);
		tag[a[i]]=true;
	}
	for(re int i=1; i<=m; ++i)
		if(tag[fa[a[i]]])
		{
			printf("-1\n");
			while(m)
				tag[a[m--]]=0;
			return;
		}
	ans=0;
	sort(a+1,a+1+m,cmp);
	if(a[1]!=1)
		st[tp=1]=1;
	for(re int i=1; i<=m; ++i)
		insert(a[i]);
	while(tp>0)
	{
		add_edge(st[tp-1],st[tp]);
		--tp;
	}

	getans(1);
	tag[1]=num_edge=0;
	printf("%d\n",ans);
}
int main()
{
	read(n);
	for(re int i=1; i<n; ++i)
	{
		int u,v;
		read(u),read(v);
		add_edge(u,v);
		add_edge(v,u);
	}
	int q;
	dfs1(1,0);
	dfs2(1,1);
	memset(head+1,num_edge=0,sizeof(head));
	read(q);
	while(q--)
		work();
	return 0;
}
