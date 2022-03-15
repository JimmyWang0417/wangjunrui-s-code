#include<cstdio>
#include<cstring>
#define re register
using namespace std;
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
const int N=1000010;
struct Edge
{
	int next,to;
} edge[N<<1];
int head[N],num_edge=-1,dfstime,from[N],cut[N],
            low[N],dfn[N],n,m,ans;
inline void add_edge(int from,int to)
{
	edge[++num_edge].next=head[from];
	head[from]=num_edge;
	edge[num_edge].to=to;
}
inline void Tarjan(int u)
{
	low[u]=dfn[u]=++dfstime;
	for(re int i=head[u],v; i>-1; i=edge[i].next)
	{
		if(i==(from[u]^1))
			continue;
		if(!dfn[v=edge[i].to])
		{
			from[v]=i;
			Tarjan(v);
			if(low[v]<low[u])
				low[u]=low[v];
			if(low[v]>dfn[u])
				cut[i]=cut[i^1]=true;
		}
		else if(dfn[v]<low[u])
			low[u]=dfn[v];
	}
}
int main()
{
	while(1)
	{
		n=read();
		m=read();
		if(n==0&&m==0)
			return 0;
		num_edge=-1;
		dfstime=ans=0;
		memset(from,-1,sizeof(from)); 
		memset(head,-1,sizeof(head));
		memset(cut,0,sizeof(cut));
		memset(low,0,sizeof(low));
		memset(dfn,0,sizeof(dfn));
		for(re int i=1,x,y; i<=m; i++)
		{
			x=read();
			y=read();
			add_edge(x,y);
			add_edge(y,x);
		}
		Tarjan(1);
		for(re int i=0; i<=num_edge; i++)
			if(cut[i])
				ans++;
		printf("%d\n",ans>>1);
	}
}

