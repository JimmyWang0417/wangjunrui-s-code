#include <cmath>
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
const int N=1000000+5;
struct Edge
{
	int next,to;
	Edge() {}
	Edge(int nownext,int nowto):next(nownext),to(nowto) {}
} edge[N<<1];
int head[N],num_edge;
inline void add_edge(int from,int to)
{
	edge[++num_edge]=Edge(head[from],to);
	head[from]=num_edge;
}
int dfstime;
int dfn[N],dep[N],size[N],fa[N],top[N],son[N];
inline void dfs1(int u,int fa_)
{
	fa[u]=fa_;
	size[u]=1;
	for(re int i=head[u]; i; i=edge[i].next)
	{
		int &v=edge[i].to;
		if(v==fa_)
			continue;
//		mindis[v]=min(mindis[u],(ll)edge[i].dis);
		dep[v]=dep[u]+1;
		dfs1(v,u);
		size[u]+=size[v];
		if(size[son[u]]<size[v])
			son[u]=v;
	}
}
inline void dfs2(int u,int topf)
{
	top[u]=topf;
	dfn[u]=++dfstime;
	if(!son[u])
		return;
	dfs2(son[u],topf);
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
vector<int>aux[N];
inline void add(int x,int y)
{
	aux[x].push_back(y);
	return;
}
inline void insert(int u)
{
	if(tp<=1)
	{
		st[++tp]=u;
		return;
	}
	int lca=LCA(st[tp],u);
//	printf("%d %d %d\n",lca,st[tp],u);
	while(tp>1&&dfn[lca]<=dfn[st[tp-1]])
	{
		add(st[tp-1],st[tp]);
		--tp;
	}
	if(lca!=st[tp])
	{
		add(lca,st[tp]);
		st[tp]=lca;
	}
	st[++tp]=u;
}
#define dist(x,y) (abs(dep[y]-dep[x]))
int tag[N];
int n,m,q,a[N];
inline bool cmp(const int &rhsx,const int &rhsy)
{
	return dfn[rhsx]<dfn[rhsy];
}
ll ans;
int ansmin,ansmax;
int maxx[N],minn[N];
ll sum[N];
inline void dp(int u)
{
	minn[u]=tag[u]?0:0x3f3f3f3f;
	sum[u]=0ll;
	maxx[u]=0;
	for(re int i=0; i<aux[u].size(); ++i)
	{
		int &v=aux[u][i];
		int w=dist(u,v);
		dp(v);
		if(tag[u])
		{
			ans+=w*tag[v]*tag[u]+sum[u]*tag[v]+sum[v]*tag[u];
			ansmin=min(ansmin,minn[u]+w+minn[v]);
			ansmax=max(ansmax,maxx[u]+w+maxx[v]);
		}
		minn[u]=min(minn[u],w+minn[v]);
		maxx[u]=max(maxx[u],w+maxx[v]);
		tag[u]+=tag[v];
		sum[u]+=sum[v]+w*tag[v];
	}
	aux[u].clear();
}
inline void work()
{
	read(m);
	for(re int i=1; i<=m; ++i)
	{
		read(a[i]);
		tag[a[i]]=1;
	}
	sort(a+1,a+1+m,cmp);
//	for(re int i=1; i<=m; ++i)
//		printf("%d ",a[i]);
	if(a[1]!=1)
		st[tp=1]=1;
	for(re int i=1; i<=m; ++i)
		insert(a[i]);
	while(tp>0)
	{
		add(st[tp-1],st[tp]);
		--tp;
	}
//	for(re int i=1; i<=n; ++i)
//	{
//		printf("\n%d:",i);
//		for(re int j=0; j<aux[i].size(); ++j)
//			printf(" %d",aux[i][j]);
//	}
//	putchar('\n');
	ansmin=0x3f3f3f3f;
	ans=0ll;
	ansmax=0;
	dp(1);
	printf("%lld %d %d\n",ans,ansmin,ansmax);
	memset(tag,0,sizeof(int)*n);
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
	dfs1(1,0);
	dfs2(1,1);
//	for(re int i=1; i<=n; ++i)
//		printf("%d %d %d %d\n",dfn[i],top[i],size[i],son[i]);
	read(q);
	while(q--)
		work();
	return 0;
}
