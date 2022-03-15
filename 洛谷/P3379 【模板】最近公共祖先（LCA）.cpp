#include<cstdio>
#define re register
using namespace std;
inline void swap(int &a,int &b)
{
	int c=a;
	a=b;
	b=c;
}
inline int read()
{
	char s=getchar();
	bool f=false;
	int x=0;
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
	return f?-x:x;
}
const int N=5e5+5;
struct Edge
{
	int next,to;
} edge[N<<1];
int n,m,s,head[N],dep[N],f[N][21],num_edge,x,y;
inline void add_edge(int from,int to)
{
	edge[++num_edge].next=head[from];
	head[from]=num_edge;
	edge[num_edge].to=to;
}
inline void Deal_first(int u,int father)
{
	dep[u]=dep[father]+1;
	for(re int i=0; i<=19; i++)
		f[u][i+1]=f[f[u][i]][i];
	for(re int i=head[u],*v; i; i=edge[i].next)
	{
		v=&edge[i].to;
		if((*v)!=father)
		{
			f[*v][0]=u;
			Deal_first(*v,u);
		}
	}
	return;
}
inline int LCA(int x,int y)
{
	if(dep[x]<dep[y])
		swap(x,y);
	for(re int i=20; i>=0; i--)
	{
		if(dep[f[x][i]]>=dep[y])
			x=f[x][i];
		if(x==y)
			return x;
	}
	for(re int i=20; i>=0; i--)
		if(f[x][i]!=f[y][i])
		{
			x=f[x][i];
			y=f[y][i];
		}
	return f[x][0];
}
int main()
{
	n=read();
	m=read();
	s=read();
	for(re int i=1; i<n; i++)
	{
		x=read();
		y=read();
		add_edge(x,y);
		add_edge(y,x);
	}
	Deal_first(s,0);
	for(re int i=1; i<=m; i++)
	{
		x=read();
		y=read();
		printf("%d\n",LCA(x,y));
	}
	return 0;
}

