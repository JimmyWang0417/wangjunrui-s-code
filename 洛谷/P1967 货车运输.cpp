#include <cmath>
#include <cstdio>
#include <bitset>
#include <cstring>
#include <algorithm>
#define lowbit(x) (x&(-x))
#define re register
#define ll long long
#define ull unsigned long long
#define rep(i,a,b) for(re int i=a;i<=b;++i)
#define per(i,a,b) for(re int i=a;i>=b;--i)
using namespace std;
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
const int N=1e4+5,M=5e4+5,INF=0x3f3f3f3f;
int father[N];
inline int find(int x)
{
	return !father[x]?x:father[x]=find(father[x]);
}
struct Edge
{
	int next,to,dis;
	Edge(int _next=0,int _to=0,int _dis=0):next(_next),to(_to),dis(_dis) {}
} edge[M<<1];
int head[N],num_edge;
inline void add_edge(int from,int to,int dis)
{
	edge[++num_edge]=Edge(head[from],to,dis);
	head[from]=num_edge;
}
inline void unionn(int x,int y,int dis)
{
	int fx=find(x),fy=find(y);
	if(fx==fy)
		return;
	father[fx]=fy;
	add_edge(x,y,dis);
	add_edge(y,x,dis);
}
struct node
{
	int u,v,w;
	inline bool operator <(const node &rhs)const
	{
		return w>rhs.w;
	}
} e[M];
int fa[N][20],minn[N][20],dep[N],Log[N];
inline void dfs(int u)
{
	for(re int i=0; i<Log[dep[u]]; ++i)
	{
		fa[u][i+1]=fa[fa[u][i]][i];
		minn[u][i+1]=min(minn[u][i],minn[fa[u][i]][i]);
	}
	for(re int i=head[u]; i; i=edge[i].next)
	{
		int &v=edge[i].to;
		if(v==fa[u][0])
			continue;
		dep[v]=dep[u]+1;
		fa[v][0]=u;
		minn[v][0]=edge[i].dis;
		dfs(v);
	}
}
inline int query(int x,int y)
{
	int ans=INF;
	if(dep[x]<dep[y])
		swap(x,y);
	for(re int i=Log[dep[x]]; i>=0; --i)
		if(dep[fa[x][i]]>=dep[y])
		{
			ans=min(ans,minn[x][i]);
			x=fa[x][i];
			if(x==y)
				return ans;
		}
//	printf("%d\n",ans);
	for(re int i=Log[dep[x]]; i>=0; --i)
		if(fa[x][i]!=fa[y][i])
		{
			ans=min(ans,min(minn[x][i],minn[y][i]));
			x=fa[x][i],y=fa[y][i];
		}
	return min(ans,min(minn[x][0],minn[y][0]));
}
signed main()
{
	int n,m;
	read(n,m);
	Log[0]=-1;
	for(re int i=1; i<=n; ++i)
		Log[i]=Log[i>>1]+1;
	for(re int i=1; i<=m; ++i)
		read(e[i].u,e[i].v,e[i].w);
	sort(e+1,e+1+m);
	for(re int i=1; i<=m; ++i)
		unionn(e[i].u,e[i].v,e[i].w);
	for(re int i=1; i<=n; ++i)
		if(!dep[i])
		{
			dep[i]=1;
			dfs(i);
		}
//	for(re int i=1; i<=n; ++i)
//	{
//		for(re int j=0; j<=Log[dep[i]]; ++j)
//			printf(" %d",minn[i][j]);
//		putchar('\n');
//	}
	int q;
	read(q);
	while(q--)
	{
		int x,y;
		read(x,y);
		printf("%d\n",find(x)==find(y)?query(x,y):-1);
	}
	return 0;
}


