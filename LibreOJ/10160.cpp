#include<cstdio>
#define re register
using namespace std;
inline int max(int a,int b)
{
	return a>b?a:b;
}
const int N=6001;
struct Edge
{
	int next,to;
} edge[N];
int n,head[N],num_edge,f[N][2],
happy[N],x,y,root;
bool vis[N];
inline void add_edge(int from,int to)
{
	edge[++num_edge].next=head[from];
	head[from]=num_edge;
	edge[num_edge].to=to;
}
inline void DP(int u)
{
	for(re int i=head[u],v; i; i=edge[i].next)
	{
		v=edge[i].to;
		DP(v);
		f[u][0]+=max(f[v][0],f[v][1]);
		f[u][1]+=f[v][0];
	}
	f[u][1]+=happy[u];
}
int main()
{
	scanf("%d",&n); 
	for(re int i=1;i<=n;i++)
	scanf("%d",&happy[i]);
	while(scanf("%d%d",&x,&y)==2,x!=0||y!=0)
	{
		add_edge(y,x);
		vis[x]=true;
		}
	root=1;
	while(vis[root])
	root++;
	DP(root);
	printf("%d\n",max(f[root][1],f[root][0]));
	return 0;
}

