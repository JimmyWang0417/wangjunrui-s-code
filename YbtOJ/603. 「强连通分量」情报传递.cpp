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
const int N=1e5+5,M=33340;
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
int n,m,t;
int dfn[N],low[N],dfstime;
int belong[N],color;
int st[N],top;
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
		++color;
		belong[u]=color;
		while(st[top]!=u)
		{
			belong[st[top]]=color;
			--top;
		}
		--top;
	}
}
struct node
{
	int u,v;
} e[N];
bitset<M+5>f[N];
int in[N];
vector<int>g[N];
inline void work(int L,int R)
{
	memset(f,0,sizeof(f));
	R=min(R,color);
	for(int i=L; i<=R; ++i)
		f[i].set(i-L);
	for(int u=1; u<=n; ++u)
	{
		for(int i=head[u]; i; i=edge[i].next)
		{
			int &v=edge[i].to;
			if(belong[u]==belong[v])
				continue;
			++in[belong[u]];
		}
	}
	queue<int>q;
	for(int i=1; i<=color; ++i)
		if(!in[i])
			q.push(i);
	while(!q.empty())
	{
		int u=q.front();
		q.pop();
		for(auto v:g[u])
		{
			f[v]|=f[u];
			if(!--in[v])
				q.push(v);
		}
	}
	for(int i=1; i<=t; ++i)
		if(L<=belong[e[i].v]&&belong[e[i].v]<=R)
		{
			if(f[belong[e[i].u]][belong[e[i].v]-L])
			{
				printf("NO\n");
				exit(0);
			}
		}
}
signed main()
{
	freopen("gplt.in","r",stdin);
	freopen("gplt.out","w",stdout);
	read(n);
	read(m);
	for(int i=1; i<=m; ++i)
	{
		int u,v;
		read(u,v);
		add_edge(u,v);
	}
	for(int i=1; i<=n; ++i)
		if(!dfn[i])
			tarjan(i);
	read(t);
	for(int i=1; i<=t; ++i)
		read(e[i].u,e[i].v);
	for(int u=1; u<=n; ++u)
	{
		for(int i=head[u]; i; i=edge[i].next)
		{
			int &v=edge[i].to;
			if(belong[u]==belong[v])
				continue;
			g[belong[v]].push_back(belong[u]);
		}
	}
	for(int l=1; l<=n; l+=M)
		work(l,l+M-1);
	printf("YES\n%d\n",m);
	for(int u=1; u<=n; ++u)
	{
		for(int i=head[u]; i; i=edge[i].next)
		{
			int &v=edge[i].to;
			printf("%d %d\n",u,v);
		}
	}
	return 0;
}


