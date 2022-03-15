#include<cstdio>
#include<algorithm>
#include<cstring>
#include<stack>
#include<set>
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
const int N=2e5+10,M=2e6+10;
int n,m,num_edge,head[N],dfn[N],low[N],dfstime,ans1,ans2,st[N],top,pointedge,totedge;
struct Edge
{
	int next,to,from;
} edge[M];
inline void add_edge(const int &from,const int &to)
{
	edge[num_edge].next=head[from];
	edge[num_edge].to=to;
	edge[num_edge].from=from;
	head[from]=num_edge++;
}
stack<Edge>stk;
set<int>bcc;
inline void Tarjan(const int &u,const int &fa)
{
	low[u]=dfn[u]=++dfstime;
	st[++top]=u;
	for(re int i=head[u]; i!=-1; i=edge[i].next)
	{
		int &v=edge[i].to;
		if(v==fa)
			continue;
		if(!dfn[v])
		{
			stk.push(edge[i]);
			Tarjan(v,u);
			low[u]=min(low[u],low[v]);
			if(low[v]>dfn[u])
				ans1++;
			if(low[v]>=dfn[u])
			{
				Edge tmp;
				bcc.clear();
				int cnt=0;
				do
				{
					cnt++;
					tmp=stk.top();
					stk.pop();
					bcc.insert(tmp.from);
					bcc.insert(tmp.to);
				}
				while(tmp.from!=u||tmp.to!=v);
				if(cnt>bcc.size())
					ans2+=cnt;
			}
		}
		else if(dfn[v]<dfn[u])
		{
			stk.push(edge[i]);
			low[u]=min(low[u],dfn[v]);
		}
	}
	return;
}
int main()
{
	while(read(n),read(m),n||m)
	{
		memset(head,-1,sizeof(head));
		memset(dfn,0,sizeof(dfn));
		memset(low,0,sizeof(low));
		ans1=ans2=num_edge=top=dfstime=0;
		for(re int i=1,u,v; i<=m; i++)
		{
			read(u);
			read(v);
			add_edge(u,v);
			add_edge(v,u);
		}
		for(re int i=0; i<n; i++)
			if(!dfn[i])
				Tarjan(i,-1);
		printf("%d %d\n",ans1,ans2);
	}
	return 0;
}
