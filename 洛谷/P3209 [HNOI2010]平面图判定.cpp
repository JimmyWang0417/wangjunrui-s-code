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
struct node
{
	int u,v;
} a[N];
int id[N];
inline bool check(int l1,int r1,int l2,int r2)
{
	if(l1==l2||l1==r2||r1==l1||l2==r2)
		return false;
	if(l1<l2&&l2<r1&&r1<r2)
		return true;
	if(l2<l1&&l1<r2&&r2<r1)
		return true;
	return false;
}
bool vis[N];
inline void work()
{
	memset(head,0,sizeof(head));
	memset(dfn,0,sizeof(dfn));
	memset(belong,0,sizeof(belong));
	num_edge=color=dfstime=top=0;
	int n,m;
	read(n,m);
	for(re int i=1; i<=m; ++i)
		read(a[i].u,a[i].v);
	for(re int i=1; i<=n; ++i)
	{
		int x;
		read(x);
		id[x]=i;
	}
	if(m>3*n-6)
	{
		printf("NO\n");
		return;
	}
	for(re int i=1; i<=m; ++i)
	{
		a[i].u=id[a[i].u],a[i].v=id[a[i].v];
		if(a[i].u>a[i].v)
			std::swap(a[i].u,a[i].v);
	}
	for(re int i=1; i<=m; ++i)
		for(re int j=i+1; j<=m; ++j)
			if(check(a[i].u,a[i].v,a[j].u,a[j].v))
			{
				add_edge(i+m,j);
				add_edge(i,j+m);
				add_edge(j,i+m);
				add_edge(j+m,i);
//				printf("%d %d\n%d %d\n%d %d\n%d %d\n",i+m,j,i,j+m,j,i+m,j+m,i);
			}
	for(re int i=1; i<=2*m; ++i)
		if(!dfn[i])
			tarjan(i);
	for(re int i=1; i<=m; ++i)
		if(belong[i]==belong[i+m])
		{
			printf("NO\n");
			return;
		}
	printf("YES\n");
}
signed main()
{
	int T;
	read(T);
	while(T--)
		work();
	return 0;
}

