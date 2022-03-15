#include<iostream>
#include<cstring>
#include<cstdio>
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
const int N=110,M=20010;
struct Edge
{
	int next,to;
} edge[M];
int dfstime,num_edge,ans,head[N],n,dfn[N],low[N],root,x,y;
bool cut[N];
inline void add_edge(int from,int to)
{
	edge[++num_edge].next=head[from];
	head[from]=num_edge;
	edge[num_edge].to=to;
}
inline void Tarjan(int u)
{
	dfn[u]=low[u]=++dfstime;
	int cnt=0;
	for(re int i=head[u],v; i; i=edge[i].next)
	{
		v=edge[i].to;
		if(!dfn[v])
		{
			cnt++;
			Tarjan(v);
			low[u]=min(low[u],low[v]);
			cut[u]=cut[u]||(u!=1&&dfn[u]<=low[v])||(u==1&&cnt>1);
		}
		else
			low[u]=min(low[u],dfn[v]);
	}
}
int main()
{
	n=read();
	while(n)
	{
		memset(cut,0,sizeof(cut));
		memset(head,0,sizeof(head));
		ans=num_edge=dfstime=0;
		memset(low,0,sizeof(low));
		memset(dfn,0,sizeof(dfn));
		while(cin>>x&&x)
		{
			while(getchar()!='\n')
			{
				cin>>y;
				add_edge(x,y);
				add_edge(y,x);
			}
		}
		Tarjan(1);
		for(re int i=1; i<=n; i++)
			if(cut[i])
				ans++;
		printf("%d\n",ans);
		n=read();
	}
}
