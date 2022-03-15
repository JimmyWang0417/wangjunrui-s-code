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
int st[N],top;
int belong[N],color;
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
	if(low[u]==dfn[u])
	{
		belong[u]=++color;
		while(st[top]!=u)
			belong[st[top--]]=color;
		--top;
	}
}
int n,A,B,a[N];
unordered_map<int,int>mp;
signed main()
{
	read(n,A,B);
	for(int i=1; i<=n; ++i)
	{
		read(a[i]);
		mp[a[i]]=i;
	}
	for(int i=1; i<=n; ++i)
	{
		if(mp[A-a[i]])
		{
			add_edge(i,mp[A-a[i]]);
			add_edge(mp[A-a[i]]+n,i+n);
		}
		else
			add_edge(i,i+n);
		if(mp[B-a[i]])
		{
			add_edge(i+n,mp[B-a[i]]+n);
			add_edge(mp[B-a[i]],i);
		}
		else
			add_edge(i+n,i);
	}
	for(int i=1; i<=2*n; ++i)
		if(!dfn[i])
			tarjan(i);
	for(int i=1; i<=n; ++i)
		if(belong[i]==belong[i+n])
		{
			puts("NO");
			return 0;
		}
	puts("YES");
	for(int i=1; i<=n; ++i)
		printf(belong[i]<belong[i+n]?"0 ":"1 ");
	putchar('\n');
	return 0;
}


