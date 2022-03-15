#include<cstdio>
#define re register
using namespace std;
template<typename T>inline void read(T&x)
{
	char s=getchar();
	x=0;
	bool f=false;
	while(!(s>='0'&&s<='9'))
	{
		if(s=='-')
			f=true;
		s=getchar();
	}
	while(s>='0'&&s<='9')
	{
		x=(x<<1)+(x<<3)+s-'0';
		s=getchar();
	}
	if(f)x=(~x)+1;
}
const int N=1e4+5,M=1e5+5;
struct Edge
{
	int next,to;
} edge[M];
int head[N],n,m,r,num_edge;
struct Tree
{
	int sum,size,ans;
} tree[N];
inline void add_edge(int from,int to)
{
	edge[++num_edge].next=head[from];
	head[from]=num_edge;
	edge[num_edge].to=to;
}
inline void Deal_first(int u,int father)
{
	tree[u].size=1;
	for(re int i=head[u],*v; i; i=edge[i].next)
	{
		v=&edge[i].to;
		if((*v)==father)
			continue;
		Deal_first(*v,u);
		tree[u].sum+=tree[*v].size*tree[*v].size;
		tree[u].size+=tree[*v].size;
	}
	tree[u].ans=tree[u].size*tree[u].size-tree[u].sum;
}
int main()
{
	read(n);
	read(r);
	read(m);
	for(re int i=1,x,y; i<n; i++)
	{
		read(x);
		read(y);
		add_edge(x,y);
		add_edge(y,x);
	}
	Deal_first(r,0);
	for(re int i=1,x; i<=m; i++)
	{
		read(x);
		printf("%d\n",tree[x].ans);
	}
	return 0;
}
