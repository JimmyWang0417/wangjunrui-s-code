#include<cstdio>
#define re register
using namespace std;
inline int min(int a,int b)
{
	return a<b?a:b;
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
const int N=1510,M=1500*1500+10;
struct Edge
{
	int next,to;
} edge[M];
int head[N],f[N][3],cost[N],n,cnt,root=1,num_edge,m;
bool vis[N];
inline void add_edge(int from,int to)
{
	edge[++num_edge].next=head[from];
	head[from]=num_edge;
	edge[num_edge].to=to;
}
inline void DP(int x,int fa)
{
	int d=0x3f3f3f3f;
	for(re int i=head[x],*y; i; i=edge[i].next)
	{
		y=&edge[i].to;
		if(*y!=fa)
		{
			DP(*y,x);
			f[x][0]+=min(f[*y][1],f[*y][2]);
			f[x][1]+=min(f[*y][1],f[*y][2]);
			d=min(d,f[*y][2]-min(f[*y][1],f[*y][2]));
			f[x][2]+=min(f[*y][0],min(f[*y][1],f[*y][2]));
		}
	}
	f[x][1]+=d;
	f[x][2]+=cost[x];
}
int main()
{
	n=read();
	for(re int i=1,x,y; i<=n; i++)
	{
		x=read();
		cost[x]=read();
		m=read();
		for(re int j=1; j<=m; j++)
		{
			y=read();
			add_edge(x,y);
			vis[y]=1;
		}
	}
	while(vis[root])
		root++;
	DP(root,0);
	printf("%d\n",min(f[root][1],f[root][2]));
}

