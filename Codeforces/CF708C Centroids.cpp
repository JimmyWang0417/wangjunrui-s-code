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
const int N=4e5+5;
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
int n,size[N],son[N];
int f[N][2],g[N],pos[N];
inline void dfs1(int u,int _fa)
{
	size[u]=1;
	for(int i=head[u]; i; i=edge[i].next)
	{
		int &v=edge[i].to;
		if(v==_fa)
			continue;
		dfs1(v,u);
		size[u]+=size[v];
		if(size[v]>size[son[u]])
			son[u]=v;
		int now=0;
		if(size[v]<=n/2)
			now=size[v];
		else
			now=f[v][0];
		if(f[u][0]<now)
		{
			f[u][1]=f[u][0];
			f[u][0]=now;
			pos[u]=v;
		}
		else if(f[u][1]<now)
			f[u][1]=now;
	}
}
bool ans[N];
inline void dfs2(int u,int _fa)
{
	if(n-size[u]>n/2)
		ans[u]=n-size[u]-g[u]<=n/2;
	else if(size[son[u]]>n/2)
		ans[u]=size[son[u]]-f[son[u]][0]<=n/2;
	else ans[u]=true;

	for(int i=head[u]; i; i=edge[i].next)
	{
		int &v=edge[i].to;
		if(v==_fa)
			continue;
		int &now=g[v];
		if(n-size[u]>n/2)
			now=g[u];
		else
			now=n-size[u];
		if(pos[u]==v)
			now=max(now,f[u][1]);
		else
			now=max(now,f[u][0]);
		dfs2(v,u);
	}
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
	dfs1(1,0);
	dfs2(1,0);
	for(int i=1; i<=n; ++i)
		printf("%d ",ans[i]);
	putchar('\n');
	return 0;
}


