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
using namespace std;
#define ui unsigned int
#define s wdnmd
ui s;
inline ui get(ui x)
{
	x ^= x << 13;
	x ^= x >> 17;
	x ^= x << 5;
	return s = x;
}
const int N=5e5+5;
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
int n,q;
int Log[N];
int dep[N],dist[N],son[N];
int fa[N][20];
inline void dfs1(int u,int _fa)
{
	dep[u]=dep[_fa]+1;
	fa[u][0]=_fa;
	for(int i=0; i<Log[dep[u]]; ++i)
		fa[u][i+1]=fa[fa[u][i]][i];
	for(int i=head[u]; i; i=edge[i].next)
	{
		int &v=edge[i].to;
		dfs1(v,u);
		if(dist[son[u]]<dist[v])
			son[u]=v;
	}
	dist[u]=dist[son[u]]+1;
}
int up[N],down[N];
int dfn[N],dfstime;
int top[N];
inline void dfs2(int u,int p,int topf)
{
	dfn[u]=++dfstime;
	up[dfn[u]]=p;
	down[dfn[u]]=u;
	top[u]=topf;

	if(!son[u])
		return;
	dfs2(son[u],fa[p][0],topf);

	for(int i=head[u]; i; i=edge[i].next)
	{
		int &v=edge[i].to;
		if(v==son[u])
			continue;
		dfs2(v,v,v);
	}
}
inline int jump(int u,int k)
{
	if(!k)
		return u;
	u=fa[u][Log[k]];
	k-=1<<Log[k];

	k-=dep[u]-dep[top[u]];
	u=top[u];
	if(k>=0)
		return up[dfn[u]+k];
	else
		return down[dfn[u]-k];
}
signed main()
{
	read(n,q,s);
	Log[0]=-1;
	for(int i=1; i<=n; ++i)
		Log[i]=Log[i>>1]+1;
	int root=1;
	for(int i=1; i<=n; ++i)
	{
		int _fa;
		read(_fa);
		if(!_fa)
			root=i;
		else
			add_edge(_fa,i);
	}
//	printf("%d\n",root);
	dfs1(root,0);
	dfs2(root,root,root);
//	for(int i=1; i<=n; ++i)
//		printf("%d\n",dep[i]);
	ll ans=0;
	int lastans=0;
	for(int i=1; i<=q; ++i)
	{
		int u=(get(s)^lastans)%n+1,k=(get(s)^lastans)%dep[u];
		lastans=jump(u,k);
//		printf("%d %d %d\n",u,k,lastans);
		ans^=(ll)i*lastans;
	}
	printf("%lld\n",ans);
	return 0;
}


