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
const int N=20005;
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
int n,m;
int root;
int dep[N];
inline void dfs(int u,int _fa)
{
	dep[u]=dep[_fa]+1;
	if(dep[u]>dep[root])
		root=u;
	for(int i=head[u]; i; i=edge[i].next)
	{
		int &v=edge[i].to;
		if(v==_fa)
			continue;
		dfs(v,u);
	}
}
signed main()
{
	read(n,m);
	for(int i=2; i<=n; ++i)
	{
		int fa;
		read(fa);
		add_edge(fa,i);
		add_edge(i,fa);
	}
	for(int i=1; i<=m; ++i)
	{
		int fa;
		read(fa);
		add_edge(fa,i+n);
		add_edge(i+n,fa);
	}
	dfs(1,0);
	dfs(root,0);
	printf("%d\n",dep[root]-1);
	return 0;
}


