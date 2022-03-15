#include <bits/stdc++.h>
#define lowbit(x) ((x)&(-(x)))
#define re register
#define ll long long
#define ull unsigned long long
#define rep(i,a,b) for(re int i=a;i<=b;++i)
#define per(i,a,b) for(re int i=a;i>=b;--i)
using namespace std;
const int N=2e3+5,M=1e5+5;
int n,m;
struct Edge
{
	int next,to;
} edge[M];
int head[N],num_edge;
int lashead[N],lasnum_edge;
inline void add_edge(int from,int to)
{
	edge[++num_edge].next=head[from];
	edge[num_edge].to=to;
	head[from]=num_edge;
}

int dfn[N],low[N],dfstime;
int belong[N],color;
int st[N],top;
inline void tarjan(int u)
{
	dfn[u]=low[u]=++dfstime;
	st[++top]=u;
	for(int i=head[u]; i; i=edge[i].next)
	{
		int &v=edge[i].to;
		if(!dfn[v])
		{
			tarjan(v);
			low[u]=min(low[u],low[v]);
		}
		else if(!belong[v])
			low[u]=min(low[u],dfn[v]);
	}
	if(dfn[u]==low[u])
	{
		belong[u]=++color;
		while(st[top]!=u)
			belong[st[top--]]=color;
		--top;
	}
}
inline bool check(int pos,bool flag)
{
	memcpy(head,lashead,sizeof(head));
	lasnum_edge=num_edge;

	memset(dfn,0,sizeof(dfn));
	memset(low,0,sizeof(low));
	memset(belong,0,sizeof(belong));
	dfstime=color=top=0;

	if(flag)
		add_edge(pos+n,pos);
	else
		add_edge(pos,pos+n);

	for(int i=1; i<=2*n; ++i)
		if(!dfn[i])
			tarjan(i);

	for(int i=1; i<=n; ++i)
		if(belong[i]==belong[i+n])
			return false;
	return true;
}
inline int rev(int id)
{
	return id<=n?id+n:id-n;
}
char ans[N];
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin>>n>>m;
	for(int i=1; i<=m; ++i)
	{
		static char us[5],vs[5];
		int u,v;
		cin>>u>>us>>v>>vs;
		int x=(us[0]=='Y'?u:u+n),y=(vs[0]=='Y'?v:v+n);
		add_edge(rev(x),y);
		add_edge(rev(y),x);
	}
	lasnum_edge=num_edge;
	memcpy(lashead,head,sizeof(head));
	for(int i=1; i<=n; ++i)
	{
		bool first=check(i,true),second=check(i,false);
		if(first&&second)
			ans[i]='?';
		else if(first)
			ans[i]='Y';
		else if(second)
			ans[i]='N';
		else
		{
			printf("IMPOSSIBLE\n");
			return 0;
		}
	}
	printf("%s\n",ans+1);
	return 0;
}

