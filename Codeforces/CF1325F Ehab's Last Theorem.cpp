#include <cstdio>
#include <cstdlib>
#define re register
using namespace std;
template<typename T>
inline void read(T&x)
{
	x=0;
	char s=(char)getchar();
	bool f=false;
	while(!(s>='0'&&s<='9'))
	{
		if(s=='-')
			f=true;
		s=(char)getchar();
	}
	while(s>='0'&&s<='9')
	{
		x=(x<<1)+(x<<3)+s-'0';
		s=(char)getchar();
	}
	if(f)
		x=(~x)+1;
}
const int N=1e5+5,M=4e5+5;
struct Edge
{
	int next,to;
} edge[M];
int head[N],num_edge;
inline void add_edge(int from,int to)
{
	edge[++num_edge].next=head[from];
	edge[num_edge].to=to;
	head[from]=num_edge;
}
int dep[N],fa[N],need;
bool del[N];
int stack[N],top;
inline void dfs(int u,int _fa)
{
	dep[u]=dep[_fa]+1;
	fa[u]=_fa;
	for(re int i=head[u]; i; i=edge[i].next)
	{
		int &v=edge[i].to;
		if(v==_fa)
			continue;
		if(!dep[v])
			dfs(v,u);
		else
		{
			if(dep[u]-dep[v]+1>=need)
			{
				int now=u;
				while((stack[++top]=now)!=v)
					now=fa[now];
				printf("2\n%d\n",top);
				while(top)
					printf("%d ",stack[top--]);
				putchar('\n');
				exit(0);
			}
		}
	}
	if(!del[u])
	{
		for(re int i=head[u]; i; i=edge[i].next)
		{
			int &v=edge[i].to;
			del[v]=true;
		}
	}
}
int main()
{
	int n,m;
	read(n),read(m);
	while(need*need<n)
		++need;
	for(re int i=1; i<=m; ++i)
	{
		int u,v;
		read(u),read(v);
		add_edge(u,v);
		add_edge(v,u);
	}
	dfs(1,0);
	printf("1\n");
	for(re int i=1; need; ++i)
		if(!del[i])
		{
			printf("%d ",i);
			--need;
		}
	putchar('\n');
	return 0;
}
