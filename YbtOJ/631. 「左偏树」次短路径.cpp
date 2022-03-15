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
const int N=1e6+5;
struct Edge
{
	int next,to,dis;
} edge[N];
int head[N],num_edge;
inline void add_edge(int from,int to,int dis)
{
	edge[++num_edge].next=head[from];
	edge[num_edge].to=to;
	edge[num_edge].dis=dis;
	head[from]=num_edge;
}
int n,m;
#define lc(x) tree[x].l
#define rc(x) tree[x].r
struct Tree
{
	int l,r;
	int dist;
	int val;
} tree[N];
int cnt,root[N];
inline void pushup(int x)
{
	tree[x].dist=tree[rc(x)].dist+1;
}
inline int newnode(int val)
{
	int x=++cnt;
	lc(x)=rc(x)=0;
	tree[x].val=val;
	pushup(x);
	return x;
}
inline int merge(int x,int y)
{
	if(!x||!y)
		return x|y;
	if(tree[x].val>tree[y].val)
		swap(x,y);
	rc(x)=merge(rc(x),y);
	if(tree[lc(x)].dist<tree[rc(x)].dist)
		swap(lc(x),rc(x));
	pushup(x);
	return x;
}
int dis[N];
int pre[N];
bool vis[N];
inline void dijkstra()
{
	memset(dis,0x3f,sizeof(dis));
	dis[1]=0;
	priority_queue<pair<int,int>,vector<pair<int,int> >,greater<pair<int,int> > >q;
	q.push(make_pair(0,1));
	while(!q.empty())
	{
		int u=q.top().second;
		q.pop();
		if(vis[u])
			continue;
		vis[u]=true;
		for(int i=head[u]; i; i=edge[i].next)
		{
			int &v=edge[i].to;
			if(dis[v]>dis[u]+edge[i].dis)
			{
				dis[v]=dis[u]+edge[i].dis;
				pre[v]=u;
				q.push(make_pair(dis[v],v));
			}
		}
	}
//	for(int i=1; i<=n; ++i)
//		printf("%d ",dis[i]);
}
vector<int>g[N];
int fa[N][25];
int dep[N];
inline void initdfs(int u)
{
	fa[u][0]=pre[u];
	dep[u]=dep[pre[u]]+1;
	for(int i=0; i<20; ++i)
		fa[u][i+1]=fa[fa[u][i]][i];
	for(auto v:g[u])
		initdfs(v);
}
inline int LCA(int u,int v)
{
	if(dep[u]<dep[v])
		swap(u,v);
	for(int i=20; i>=0; --i)
		if(dep[fa[u][i]]>=dep[v])
			u=fa[u][i];
	if(u==v)
		return u;
	for(int i=20; i>=0; --i)
		if(fa[u][i]!=fa[v][i])
		{
			u=fa[u][i];
			v=fa[v][i];
		}
	return fa[u][0];
}
vector<int>del[N];
int ans[N];
inline void dfs(int u)
{
	for(int i=head[u]; i; i=edge[i].next)
	{
		int &v=edge[i].to;
		if(v==pre[u]||u==pre[v])
			continue;
		int x=newnode(dis[u]+dis[v]+edge[i].dis);
		root[u]=merge(root[u],x);
		del[LCA(u,v)].push_back(x);
//		printf("%d %d %d\n",u,v,LCA(u,v));
	}
	for(auto v:g[u])
	{
		dfs(v);
		root[u]=merge(root[u],root[v]);
	}
	for(auto v:del[u])
		vis[v]=true;
	while(root[u]&&vis[root[u]])
		root[u]=merge(lc(root[u]),rc(root[u]));
	if(root[u])
		ans[u]=tree[root[u]].val-dis[u];
}
signed main()
{
	freopen("pal.in","r",stdin),freopen("pal.out","w",stdout);
	read(n,m);
	for(int i=1; i<=m; ++i)
	{
		int u,v,w;
		read(u,v,w);
		add_edge(u,v,w);
		add_edge(v,u,w);
	}
	dijkstra();
	for(int i=2; i<=n; ++i)
		g[pre[i]].push_back(i);
	memset(vis,0,sizeof(vis));
	initdfs(1);
	for(int i=1; i<=n; ++i)
		ans[i]=-1;
	dfs(1);
	for(int i=2; i<=n; ++i)
		printf("%d\n",ans[i]);
	return 0;
}


