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
struct node
{
	int u,v,l,a;
	inline bool operator < (const node&rhs)const
	{
		return a>rhs.a;
	}
} e[N];
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
int dis[N];
bitset<N>vis;
inline void dijkstra()
{
	memset(dis,0x3f,sizeof(dis));
	priority_queue<pair<int,int>,vector<pair<int,int> >,greater<pair<int,int> > >q;
	q.push(make_pair(dis[1]=0,1));
	vis.reset();
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
				q.push(make_pair(dis[v]=dis[u]+edge[i].dis,v));
		}
	}
}
int n,m,q,k,s;
vector<int>G[N];
int fa[N];
inline int find(int x)
{
	return !fa[x]?x:fa[x]=find(fa[x]);
}
int a[N];
int f[N][25];
inline void dfs(int u)
{
	for(int i=0; i<20; ++i)
		f[u][i+1]=f[f[u][i]][i];
//	printf(" %d",u);
	for(auto v:G[u])
	{
		f[v][0]=u;
		dfs(v);
		dis[u]=min(dis[u],dis[v]);
	}
}
inline void kruskal()
{
	sort(e+1,e+1+m);
	memset(fa,0,sizeof(fa));
	for(int i=1; i<=n; ++i)
		a[i]=1e6;
	int root=1;
	for(int i=1; i<=m; ++i)
	{
//		printf("edge=%d %d %d\n",e[i].u,e[i].v,e[i].a);
		int u=find(e[i].u),v=find(e[i].v);
//		printf("%d %d\n",u,v);
		if(u==v)
			continue;
		G[i+n].push_back(u);
		G[i+n].push_back(v);
//		printf(" %d %d %d\n",i+n,u,v);
		fa[u]=fa[v]=i+n;
		a[i+n]=e[i].a;
		root=i+n;
	}
//	printf("%d\n",root);
	dfs(root);
//	for(int i=1; i<=n+m; ++i)
//		printf("%d ",dis[i]);
//	putchar('\n');
	for(int i=1; i<=m; ++i)
		G[i+n].clear();
}
inline int query(int u,int p)
{
	for(int i=20; i>=0; --i)
		if(a[f[u][i]]>p)
			u=f[u][i];
	return u;
}
inline void work()
{
	a[0]=-100;
	read(n,m);
	memset(head,num_edge=0,sizeof(head));
	for(int i=1; i<=m; ++i)
	{
		read(e[i].u,e[i].v,e[i].l,e[i].a);
		add_edge(e[i].u,e[i].v,e[i].l);
		add_edge(e[i].v,e[i].u,e[i].l);
	}
	dijkstra();
	kruskal();
	read(q,k,s);
	int lastans=0;
	while(q--)
	{
		int v,p;
		read(v,p);
		v=(v+k*lastans-1)%n+1;
		p=(p+k*lastans)%(s+1);
//		printf(" %d %d %d\n",v,p,query(v,p));
//		printf(" %d %d\n",f[v][0],a[f[v][0]]);
		printf("%d\n",lastans=dis[query(v,p)]);
	}
}
signed main()
{
//	freopen("return.in","r",stdin);
//	freopen("return.out","w",stdout);
	int T;
	read(T);
	while(T--)
		work();
	return 0;
}

