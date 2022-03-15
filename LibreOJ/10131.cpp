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
template<typename T>
inline void swap(T&a,T&b)
{
	T c=a;
	a=b;
	b=c;
}
const int N=1e5+5,M=4e5+5;
struct Edge
{
	int next,to;
} edge[M];
int dep[N],head[N],num_edge,f[N][25],
    ans[N],val[N],n,m,sum;
inline void add_edge(int from,int to)
{
	edge[++num_edge].next=head[from];
	head[from]=num_edge;
	edge[num_edge].to=to;
}
inline void Deal_first(int u,int father)
{
	dep[u]=dep[father]+1;
	for(re int i=0; i<=20; i++)
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
inline int LCA(int x,int y)
{
	if(dep[x]<dep[y])
		swap(x,y);
	for(re int i=21; i>=0; i--)
	{
		if(dep[f[x][i]]>=dep[y])
			x=f[x][i];
		if(x==y)
			return x;
	}
	for(re int i=21; i>=0; i--)
		if(f[x][i]!=f[y][i])
		{
			x=f[x][i];
			y=f[y][i];
		}
	return f[x][0];
}
inline void dfs(int u,int father)
{
	ans[u]=val[u];
	for(re int i=head[u],v; i; i=edge[i].next)
	{
		v=edge[i].to;
		if(v==father)
			continue;
		dfs(v,u);
		ans[u]+=ans[v];
	}
	return;
}
int main()
{
	read(n);
	read(m);
	for(re int i=1,x,y; i<n; i++)
	{
		read(x);
		read(y);
		add_edge(x,y);
		add_edge(y,x);
	}
	Deal_first(1,0);
	for(re int i=1,x,y; i<=m; i++)
	{
		read(x);
		read(y);
		val[x]++;
		val[y]++;
		val[LCA(x,y)]-=2;
	}
	dfs(1,0);
	for(re int i=2; i<=n; i++)
		sum+=(ans[i]==0?m:(ans[i]==1?1:0)); 
	printf("%d\n",sum);
	return 0;
}

