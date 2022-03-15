#include<cstdio>
#include<algorithm>
#define re register
#define co const
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
	return;
}
co int Size=25,N=1e4+10,M=1e5+10;
int f[N][Size],val[N][Size];
struct Edge
{
	int next,to,dis;
} edge[M<<1];
struct node
{
	int u,v,w;
	inline bool operator <(const node &a)const
	{
		return w<a.w;
	}
} e[M];
int n,m,dep[N],head[N],num_edge,father[N],q;
inline void add_edge(co int & from,co int & to,co int & dis)
{
	edge[++num_edge].next=head[from];
	edge[num_edge].to=to;
	edge[num_edge].dis=dis;
	head[from]=num_edge;
}
inline void Deal_first(int u,int father)
{
	dep[u]=dep[father]+1;
	for(re int i=0; i<=19; i++)
	{
		f[u][i+1]=f[f[u][i]][i];
		val[u][i+1]=max(val[u][i],val[f[u][i]][i]);
	}
	for(re int i=head[u]; i; i=edge[i].next)
	{
		int &v=edge[i].to;
		if((v)!=father)
		{
			f[v][0]=u;
			val[v][0]=edge[i].dis;
			Deal_first(v,u);
		}
	}
	return;
}
inline int LCA(int x,int y)
{
	if(dep[x]<dep[y])
		swap(x,y);
	int maxx=~0x7fffffff;
	for(re int i=20; i>=0; i--)
	{
		if(dep[f[x][i]]>=dep[y])
		{
			maxx=max(maxx,val[x][i]);
			x=f[x][i];
		}
		if(x==y)
			return maxx;
	}
	for(re int i=20; i>=0; i--)
	{
		if(f[x][i]!=f[y][i])
		{
			maxx=max(maxx,max(val[x][i],val[y][i]));
			x=f[x][i];
			y=f[y][i];
		}
	}
	return max(maxx,max(val[x][0],val[y][0]));
}
inline int find(int x)
{
	return father[x]==x?x:father[x]=find(father[x]);
}
int main()
{
	read(n);
	read(m);
	for(re int i=1; i<=m; i++)
	{
		read(e[i].u);
		read(e[i].v);
		read(e[i].w);
	}
	stable_sort(e+1,e+1+m);
	for(re int i=1; i<=n; i++)
		father[i]=i;
	for(re int i=1,fx,fy; i<=m; i++)
	{
		fx=find(e[i].u);
		fy=find(e[i].v);
		if(fx!=fy)
		{
			father[fx]=fy;
			add_edge(e[i].u,e[i].v,e[i].w);
			add_edge(e[i].v,e[i].u,e[i].w);
		}
	}
	Deal_first(1,0);
	/*for(re int i=1; i<=n; i++)
		printf("%d ",dep[i]);*/
	/*for(re int i=1; i<=n; i++)
	{
		for(re int j=0; j<=19; j++)
			printf("%d ",val[i][j]);
		putchar('\n');
	}*/
	read(q);
	re int s,t;
	while(q--)
	{
		read(s);
		read(t);
		int x=LCA(s,t);
		printf("%d\n",x==(~0x7fffffff)?0:x);
	}
	return 0;
}

