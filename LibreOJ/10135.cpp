#include<cstdio>
#define re register
using namespace std;
template<typename T>inline void read(T&x)
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
	if(f)x=(~x)+1;
}
const int N=4e4+5;
struct Edge
{
	int next,to;
} edge[N<<1];
int head[N],num_edge,dep[N],f[N][25],n,m,root;
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
inline bool LCA(int x,int y)
{
	for(re int i=19; ~i; i--)
		if(dep[f[x][i]]>=dep[y])
		{
			x=f[x][i];
			if(dep[x]==dep[y])
				return x==y;
		}
	return x==y;
}
int main()
{
	read(n);
	for(re int i=1,a,b; i<=n; i++)
	{
		read(a);
		read(b);
		if(b==-1)
		{
			root=a;
			continue;
		}
		add_edge(a,b);
		add_edge(b,a);
	}
	Deal_first(root,0);
	read(m);
	for(re int i=1,x,y; i<=m; i++)
	{
		read(x);
		read(y);
		if(dep[x]>dep[y])
		{
			if(LCA(x,y))
				printf("2\n");
			else
				printf("0\n");
		}
		else if(dep[x]<dep[y])
		{
			if(LCA(y,x))
				printf("1\n");
			else
				printf("0\n");
		}
		else
			printf("0\n");
	}
	return 0;
}

