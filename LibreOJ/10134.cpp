#include<cstdio>
#define re register
using namespace std;
template<typename T>
inline void read(T&x)
{
	x=0;
	char s=getchar();
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
	if(f)
		x=(~x)+1;
}
template<typename fuck_ccf>inline void swap(fuck_ccf&a,fuck_ccf&b)
{
	fuck_ccf c=a;
	a=b;
	b=c;
}
const int N=100001,M=1000001;
int n,m,head[N],num_edge,dep[N],dis[N],f[N][90];
struct Edge
{
	int next,to,dis;
} edge[M];
inline void add_edge(int from,int to,int dis)
{
	edge[++num_edge].next=head[from];
	head[from]=num_edge;
	edge[num_edge].to=to;
	edge[num_edge].dis=dis;
}
inline void Deal_first(int u,int father,int w)
{
	dep[u]=dep[father]+1;
	dis[u]=dis[father]+w;
	for(re int i=0; i<=21; i++)
		f[u][i+1]=f[f[u][i]][i];
	for(re int i=head[u],v,ww; i; i=edge[i].next)
	{
		v=edge[i].to;
		ww=edge[i].dis;
		if(v!=father)
		{
			f[v][0]=u;
			Deal_first(v,u,ww);
		}
	}
	return;
}
inline int LCA(int x,int y)
{
	if(dep[x]<dep[y])
		swap(x,y);
	for(re int i=19; i>=0; i--)
	{
		if(dep[f[x][i]]>=dep[y])
		{
			x=f[x][i];

		}
		if(x==y)
			return x;
	}
	for(re int i=19; i>=0; i--)
		if(f[x][i]!=f[y][i])
		{
			x=f[x][i];
			y=f[y][i];
		}
	return f[x][0];
}
#define dist(x,y)(dis[x]+dis[y]-(dis[LCA(x,y)]<<1))
int main()
{
	read(n);
	read(m);
	for(re int i=1,x,y,z; i<n; i++)
	{
		read(x);
		read(y);
		read(z);
		add_edge(x,y,z);
		add_edge(y,x,z);
	}
	Deal_first(1,0,0);
	for(re int i=1,x,y; i<=m; i++)
	{
		read(x);
		read(y);
		printf("%d\n", dis[x]+dis[y]-(dis[LCA(x,y)] * 2));
	}
	return 0;
}
