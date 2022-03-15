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
const int N=1e5+5;
int n,m;
struct Edge
{
	int next,to;
} edge[N*2];
int head[N],num_edge;
inline void add_edge(int from,int to)
{
	edge[++num_edge].next=head[from];
	edge[num_edge].to=to;
	head[from]=num_edge;
}
int a[N];
int size[N],son[N];
inline void inittree(int u,int _fa)
{
	size[u]=1;
	for(int i=head[u]; i; i=edge[i].next)
	{
		int &v=edge[i].to;
		if(v==_fa)
			continue;
		inittree(v,u);
		size[u]+=size[v];
		if(size[son[u]]<size[v])
			son[u]=v;
	}
}
int answer[N],ans,cnt[N];
inline void add(int val)
{
	if(!cnt[val]++)
		++ans;
}
inline void del(int val)
{
	if(!--cnt[val])
		--ans;
}
inline void addtree(int u,int _fa)
{
	add(a[u]);
	for(int i=head[u]; i; i=edge[i].next)
	{
		int &v=edge[i].to;
		if(v==_fa)
			continue;
		addtree(v,u);
	}
}
inline void deltree(int u,int _fa)
{
	del(a[u]);
	for(int i=head[u]; i; i=edge[i].next)
	{
		int &v=edge[i].to;
		if(v==_fa)
			continue;
		deltree(v,u);
	}
}
inline void dfs(int u,int _fa,bool keep)
{
	for(int i=head[u]; i; i=edge[i].next)
	{
		int &v=edge[i].to;
		if(v==_fa||v==son[u])
			continue;
		dfs(v,u,false);
	}
	if(son[u])
		dfs(son[u],u,true);
	add(a[u]);
	for(int i=head[u]; i; i=edge[i].next)
	{
		int &v=edge[i].to;
		if(v==_fa||v==son[u])
			continue;
		addtree(v,u);
	}
	answer[u]=ans;
	if(!keep)
		deltree(u,_fa);
}
signed main()
{
	read(n);
	for(int i=1; i<n; ++i)
	{
		int u,v;
		read(u,v);
		add_edge(u,v);
		add_edge(v,u);
	}
	for(int i=1; i<=n; ++i)
		read(a[i]);
	inittree(1,0);
	dfs(1,0,false);
//	for(int i=1; i<=n; ++i)
//		printf("%d ",answer[i]);
//	putchar('\n');
	read(m);
	for(int i=1; i<=m; ++i)
	{
		int u;
		read(u);
		printf("%d\n",answer[u]);
	}
	return 0;
}

