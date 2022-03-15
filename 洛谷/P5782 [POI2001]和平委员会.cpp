#include <bits/stdc++.h>
#define lowbit(x) ((x)&(-(x)))
#define re register
#define ll long long
#define ull unsigned long long
#define rep(i,a,b) for(re int i=a;i<=b;++i)
#define per(i,a,b) for(re int i=a;i>=b;--i)
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
template<typename T,typename ...T1>
inline void read(T&x,T1&...x1)
{
	read(x);
	read(x1...);
}
template<typename T>
inline void clear(T*a,int l,int r,int val)
{
	memset(&a[l],val,sizeof(T)*(r-l+1));
}
const int N=1e6+5;
struct Edge
{
	int next,to;
} edge[N];
int head[N],num_edge;
inline void add_edge(int from,int to)
{
	edge[++num_edge].next=head[from];
	edge[num_edge].to=to;
	head[from]=num_edge;
}
int dfn[N],low[N],dfstime;
int belong[N],color;
int st[N],top;
using std::min;
inline void tarjan(int u)
{
	low[u]=dfn[u]=++dfstime;
	st[++top]=u;
	for(re int i=head[u]; i; i=edge[i].next)
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
	if(low[u]==dfn[u])
	{
		belong[u]=++color;
		while(st[top]!=u)
			belong[st[top--]]=color;
		--top;
	}
}
inline int rev(int x)
{
	if(x&1)
		return x+1;
	else
		return x-1;
}
signed main()
{
	int n,m;
	read(n,m);
	for(re int i=1; i<=m; ++i)
	{
		int u,v;
		read(u,v);
		add_edge(u,rev(v));
		add_edge(v,rev(u));
	}
	for(re int i=1; i<=n*2; ++i)
		if(!dfn[i])
			tarjan(i);
	for(re int i=1; i<=n; ++i)
		if(belong[i*2]==belong[i*2-1])
		{
			printf("NIE\n");
			return 0;
		}
	for(re int i=1; i<=n; ++i)
		printf("%d\n",belong[i*2-1]<belong[i*2]?i*2-1:i*2);
	return 0;
}
