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
int dep[N];
int n,m,a[N];
int fa[N][25];
inline void dfs(int u,int _fa)
{
	dep[u]=dep[_fa]+1;
	if(a[_fa]>a[u])
		fa[u][0]=_fa;
	else
	{
		int x=_fa;
		for(int i=20; i>=0; --i)
			if(a[fa[x][i]]<=a[u])
				x=fa[x][i];
		fa[u][0]=fa[x][0];
	}
	for(int i=0; i<20; ++i)
		fa[u][i+1]=fa[fa[u][i]][i];
	for(int i=head[u]; i; i=edge[i].next)
	{
		int &v=edge[i].to;
		if(v==_fa)
			continue;
		dfs(v,u);
	}
}
inline int query(int u,int v,int c)
{
	int ans=a[u]>c;
	for(int i=20; i>=0; --i)
		if(a[fa[u][i]]<=c)
			u=fa[u][i];
	if(dep[u]<=dep[v])
		return ans;
	for(int i=20; i>=0; --i)
	if(dep[fa[u][i]]>=dep[v])
	{
		ans+=1<<i;
		u=fa[u][i];
	}
	return ans;
}
signed main()
{
	read(n,m);
	for(int i=1; i<=n; ++i)
		read(a[i]);
	for(int i=1; i<n; ++i)
	{
		int u,v;
		read(u,v);
		add_edge(u,v);
		add_edge(v,u);
	}
	a[0]=0x7fffffff;
	dfs(1,0);
	for(int i=1; i<=m; ++i)
	{
		int u,v,c;
		read(u,v,c);
		printf("%d\n",query(u,v,c));
	}
	return 0;
}


