#include<cstdio>
#include<iostream>
#define re register
using namespace std;
inline void read(int&x)
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
const int N=5e5+5;
struct Edge
{
	int next,to;
} edge[N<<1];

int Log[N];
int head[N],num_edge,dep[N],f[N][20],n,m;
inline void add_edge(re int from,re int to)
{
	edge[++num_edge].next=head[from];
	edge[num_edge].to=to;
	head[from]=num_edge;
}
inline void Deal_first(int u,int father)
{
	dep[u]=dep[father]+1;
	for(re int i=0; i<=Log[dep[u]]; i++)
		f[u][i+1]=f[f[u][i]][i];
	for(re int i=head[u],v; i; i=edge[i].next)
	{
		v=edge[i].to;
		if(v==father)
			continue;
		f[v][0]=u;
		Deal_first(v,u);
	}
	return;
}
inline int LCA(re int x,re int y)
{
	if(dep[x]<dep[y])
		swap(x,y);
	for(re int i=Log[dep[x]]; i>=0; i--)
	{
		if(dep[f[x][i]]>=dep[y])
			x=f[x][i];
		if(x==y)
			return x;
	}
	for(re int i=Log[dep[x]]; i>=0; i--)
		if(f[x][i]!=f[y][i])
		{
			x=f[x][i];
			y=f[y][i];
		}
	return f[x][0];
}
#define max(x,y)(dep[x]>dep[y]?x:y)
#define dist(x,y,z)(dep[x]+dep[y]-(dep[z]<<1))
int main()
{
	read(n);
	read(m);
	re int i,a,b,c,fa,fb,fc,x,y,ans;
	for(i=1; i<n; i++)
	{
		read(x);
		read(y);
		add_edge(x,y);
		add_edge(y,x);
	}
	Log[0]=-1;
	for(int i=1; i<=n; i++)
		Log[i]=Log[i>>1]+1;
	Deal_first(1,0);
	for(i=1; i<=m; i++)
	{
		read(a);
		read(b);
		read(c);
		fa=LCA(a,b);
		fb=LCA(a,c);
		fc=LCA(b,c);
		printf("%d %d\n",max(fa,max(fb,fc)),
		       (dist(a,b,fa)+dist(a,c,fb)+dist(b,c,fc))>>1);
	}
	return 0;
}

