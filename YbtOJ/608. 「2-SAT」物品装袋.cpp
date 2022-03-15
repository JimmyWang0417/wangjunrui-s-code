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
inline void clear(T*array,int l,int r,int _val)
{
	memset(&array[l],_val,sizeof(T)*(r-l+1));
}
using namespace std;
const int N=505;
int n,g[N][N];
int pre[N];
int val[N];
bool vis[N];
bool col[N];
struct Edge
{
	int next,to;
} edge[N*N*4];
int head[N],num_edge;
inline void add_edge(int from,int to)
{
	edge[++num_edge].next=head[from];
	edge[num_edge].to=to;
	head[from]=num_edge;
}
int dfn[N],low[N],dfstime;
int belong[N],color;
int st[N],top;
inline void tarjan(int u)
{
	dfn[u]=low[u]=++dfstime;
	st[++top]=u;
	for(int i=head[u]; i; i=edge[i].next)
	{
		int &v=edge[i].to;
		if(!dfn[v])
		{
			tarjan(v);
			low[u]=min(low[u],low[v]);
		}
		else if(!belong[v])
			low[u]=min(low[u],dfn[v]);
	}
	if(dfn[u]==low[u])
	{
		belong[u]=++color;
		while(st[top]!=u)
			belong[st[top--]]=u;
		--top;
	}
}
inline bool check(int A,int B)
{
//	printf("%d %d\n",A,B);
	dfstime=top=0;
	clear(dfn,1,2*n,0);
	clear(belong,1,2*n,color=0);
	clear(head,1,2*n,num_edge=0);
	for(int i=1; i<=n; ++i)
		for(int j=i+1; j<=n; ++j)
		{
			if(g[i][j]>B)
			{
				add_edge(i+n,j);
				add_edge(j+n,i);
				add_edge(i,j+n);
				add_edge(j,i+n);
			}
			else if(g[i][j]>A)
			{
				add_edge(i,j+n);
				add_edge(j,i+n);
			}
		}
	for(int i=1; i<=2*n; ++i)
		if(!dfn[i])
			tarjan(i);
	for(int i=1; i<=n; ++i)
		if(belong[i]==belong[i+n])
			return false;
	return true;
}
inline int solve(int B)
{
	int l=0,r=B,ans=0x3f3f3f3f;
	while(l<=r)
	{
		int mid=(l+r)>>1;
		if(check(mid,B))
		{
			ans=mid;
			r=mid-1;
		}
		else l=mid+1;
	}
	return ans;
}
inline void work()
{
	for(int i=1; i<=n; ++i)
	{
		g[i][i]=0;
		for(int j=i+1; j<=n; ++j)
		{
			read(g[i][j]);
			g[j][i]=g[i][j];
		}
	}
	clear(vis,1,n,0);
	clear(pre,1,n,0);
	int u=1;
	col[1]=0;
	for(int now=1; now<n; ++now)
	{
		vis[u]=true;
		int to=0;
		for(int v=1; v<=n; ++v)
			if(!vis[v])
			{
				if(g[pre[v]][v]<g[u][v])
					pre[v]=u;
			}
		for(int v=1; v<=n; ++v)
			if(!vis[v])
			{
				if(g[pre[v]][v]>g[pre[to]][to])
					to=v;
			}
		col[to]=col[pre[to]]^1;
		val[now]=g[pre[to]][to];
		u=to;
	}
	val[n]=val[n+1]=0;
	for(int i=1; i<=n; ++i)
		for(int j=i+1; j<=n; ++j)
			if(col[i]==col[j])
				val[n+col[i]]=max(val[n+col[i]],g[i][j]);
	int ans=0x7fffffff;
//	for(int i=1; i<=n+1; ++i)
//		printf(" %d",val[i]);
//	putchar('\n');
//	printf(" %d\n",check(0,4));
	for(int i=1; i<=n+1; ++i)
		ans=min(ans,solve(val[i])+val[i]);
	printf("%d\n",ans);
}
signed main()
{
	freopen("florida.in","r",stdin),freopen("florida.out","w",stdout);
	for(int i=1; i<=500; ++i)
		g[0][i]=g[i][0]=-1;
	while(scanf("%d",&n)!=EOF)
		work();
	return 0;
}


