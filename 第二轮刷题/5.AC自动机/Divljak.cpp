#include <cstdio>
#include <queue>
#include <cassert>
#include <algorithm>
#define re register
using namespace std;
const int N=2e6+5,M=1e5+5;
int ch[N][26],nxt[N],tot;
int pos[M];
inline void insert(char *s,int id)
{
	int u=0;
	for(re int i=0; s[i]; ++i)
	{
		int c=s[i]-'a';
		if(!ch[u][c])
			ch[u][c]=++tot;
		u=ch[u][c];
	}
	pos[id]=u;
}
struct Edge
{
	int next,to;
} edge[N];
int head[N],num_edge;
inline void add_edge(int from,int to)
{
	edge[++num_edge].next=head[from];
	edge[num_edge].to=to;
	head[from]=num_edge;
}
inline void build()
{
	queue<int>q;
	for(re int i=0; i<26; ++i)
		if(ch[0][i])
			q.push(ch[0][i]);
	while(!q.empty())
	{
		int u=q.front();
		q.pop();
		for(re int i=0; i<26; ++i)
			if(!ch[u][i])
				ch[u][i]=ch[nxt[u]][i];
			else
			{
				q.push(ch[u][i]);
				nxt[ch[u][i]]=ch[nxt[u]][i];
			}
	}
}
int fa[N],top[N],dep[N],size[N],son[N];
inline void dfs1(int u,int fa_)
{
	fa[u]=fa_;
	size[u]=1;
	dep[u]=dep[fa_]+1;
	for(re int i=head[u]; i; i=edge[i].next)
	{
		int &v=edge[i].to;
		dfs1(v,u);
		size[u]+=size[v];
		if(!son[u]||size[v]>size[son[u]])
			son[u]=v;
	}
}
int dfn[N],dfstime;
inline void dfs2(int u,int topf)
{
	top[u]=topf;
	dfn[u]=++dfstime;
//	printf("%d ",u);
	if(!son[u])return;
	dfs2(son[u],topf);
	for(re int i=head[u]; i; i=edge[i].next)
	{
		int &v=edge[i].to;
		if(v==son[u])
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
int n,q;
char str[N];
int a[N];
int lowbitsum[N];
#define lowbit(x) (x&(-x))
inline void update(int x,int y)
{
//	assert(x>=1);
	for(; x<=dfstime; x+=lowbit(x))
		lowbitsum[x]+=y;
}
inline int query(int x)
{
//	assert(x>=1);
	int res=0;
	for(; x; x-=lowbit(x))
		res+=lowbitsum[x];
	return res;
}
inline bool cmp(const int &x,const int &y)
{
	return dfn[x]<dfn[y];
}
inline void solve1()
{
	int u=0,tp=0;
	for(re int i=0; str[i]; ++i)
	{
		u=ch[u][str[i]-'a'];
		a[++tp]=u;
	}
//	for(re int i=1; i<=tp; ++i)
//		printf("%d ",a[i]);
	sort(a+1,a+1+tp,cmp);
	bool flag=false;
	for(re int i=1; i<=tp; ++i)
	{
		update(dfn[a[i]],1);
		if(flag)
			update(dfn[LCA(a[i],a[i-1])],-1);
		else
			flag=true;
	}
}
inline void solve2()
{
	int x;
	scanf("%d",&x);
	printf("%d\n",query(dfn[pos[x]]+size[pos[x]]-1)-query(dfn[pos[x]]-1));
}
int main()
{
	scanf("%d",&n);
	for(re int i=1; i<=n; ++i)
	{
		scanf("%s",str);
		insert(str,i);
	}
	build();
//	for(re int i=1; i<=tot; ++i)
//		printf("%d %d\n",nxt[i],i);
	for(re int i=1; i<=tot; ++i)
		add_edge(nxt[i],i);
//	printf("%d\n",num_edge);
	dfs1(0,tot+1);
	dfs2(0,0);
//	printf("%d\n",dfstime);
//	for(re int i=0; i<=tot; ++i)
//		printf("%d ",dfn[i]);
	scanf("%d",&q);
	while(q--)
	{
		int opt;
		scanf("%d",&opt);
		if(opt==1)
		{
			scanf("%s",str);
			solve1();
		}
		else if(opt==2)
			solve2();
	}
	return 0;
}
