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
inline void clear(T*array,int l,int r,int val)
{
	memset(&array[l],val,sizeof(T)*(r-l+1));
}
using namespace std;
const int N=2005;
int n,m;
struct Edge
{
	int next,to;
} edge[N*N];
int head[N],num_edge;
inline void add_edge(int from,int to)
{
	edge[++num_edge].next=head[from];
	edge[num_edge].to=to;
	head[from]=num_edge;
}
bitset<N>vis,g[N];
int prelink[N];
inline bool find(int u)
{
	while(1)
	{
		int v=(g[u]&vis)._Find_first();
		if(v>m)
			break;
		vis.reset(v);
		if(!prelink[v]||find(prelink[v]))
		{
			prelink[v]=u;
			return true;
		}
	}
	return false;
}
int low[N],dfn[N],dfstime;
int st[N],top;
int belong[N],color;
inline void tarjan(int u)
{
	st[++top]=u;
	dfn[u]=low[u]=++dfstime;
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
	if(low[u]==dfn[u])
	{
		belong[u]=++color;
		while(st[top]!=u)
			belong[st[top--]]=color;
		--top;
	}
}
char str[N];
signed main()
{
	freopen("fantasy.in","r",stdin);
	freopen("fantasy.out","w",stdout);
	read(n,m);
	for(int i=1; i<=n; ++i)
	{
		scanf("%s",str+1);
		for(int j=1; j<=m; ++j)
			if(str[j]=='1')
				g[i].set(j);
	}
	int ans=0;
	for(int i=1; i<=n; ++i)
	{
		vis.set();
		if(find(i))
			++ans;
	}
	if(ans<n)
	{
		for(int i=1; i<=n; ++i,putchar('\n'))
			for(int j=1; j<=m; ++j)
				putchar('1');
		return 0;
	}
	for(int i=1; i<=n; ++i)
		for(int j=1; j<=m; ++j)
			if(g[i][j])
				prelink[j]==i?add_edge(i,j+n):add_edge(j+n,i);
	for(int i=1; i<=m; ++i)
		prelink[i]?add_edge(i+n,n+m+1):add_edge(n+m+1,i+n);
	for(int i=1; i<=n; ++i)
		if(!dfn[i])
			tarjan(i);
	for(int i=1; i<=n; ++i,putchar('\n'))
		for(int j=1; j<=m; ++j)
			putchar((g[i][j]&&(i==prelink[j]||belong[i]==belong[j+n]))?'0':'1');
	return 0;
}


