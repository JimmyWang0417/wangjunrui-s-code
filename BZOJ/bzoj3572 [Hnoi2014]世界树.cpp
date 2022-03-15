#include<cstdio>
#include<vector>
#include<queue>
#define size sze
using namespace std;
const int N=3e5+5,LOGN=20;
struct Edge
{
	int next,to;
	Edge() {}
	Edge(int x,int y):next(x),to(y) {}
} edge[N<<1];
int head[N],num_edge;
inline void add_edge(int from,int to)
{
	edge[++num_edge]=Edge(head[from],to);
	head[from]=num_edge;
}


int n,m,val[N],delta[N];
int dep[N],dfn[N],size[N],fa[N][LOGN+1];
pair<int,int>f[N];
inline bool cmp(const int &u,const int &v)
{
	return dfn[u]<dfn[v];
}
inline void build()
{
	
}
int main()
{
}
