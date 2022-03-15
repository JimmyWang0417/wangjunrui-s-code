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
int n,k;
struct Edge
{
	int next,to,dis;
} edge[N*2];
int head[N],num_edge;
inline void add_edge(int from,int to,int dis)
{
	edge[++num_edge].next=head[from];
	edge[num_edge].to=to;
	edge[num_edge].dis=dis;
	head[from]=num_edge;
}
int root;
int maxsize[N],size[N];
bitset<N>exist;
vector<int>g[N];
inline void dfs1(int u,int _fa)
{
	for(int i=head[u]; i; i=edge[i].next)
	{
		int &v=edge[i].to;
		if(v==_fa)
			continue;
		dfs1(v,u);
		size[u]+=size[v];
		maxsize[u]=max(maxsize[u],size[v]);
	}
	maxsize[u]=max(maxsize[u],k-size[u]);
	if(maxsize[u]<=(k/2))
		root=u;
}
int color;
inline void dfs2(int u,int _fa)
{
	if(exist[u])
		g[color].push_back(u);
	for(int i=head[u]; i; i=edge[i].next)
	{
		int &v=edge[i].to;
		if(v==_fa)
			continue;
		dfs2(v,u);
	}
}
signed main()
{
	freopen("pair.in","r",stdin);
	freopen("pair.out","w",stdout);
	read(n,k);
	for(int i=1; i<n; ++i)
	{
		int u,v,w;
		read(u,v,w);
		add_edge(u,v,w);
		add_edge(v,u,w);
	}
	for(int i=1; i<=k; ++i)
	{
		int u;
		read(u);
		size[u]=exist[u]=1;
	}
	dfs1(1,0);
	priority_queue<pair<int,int> >q;
	if(exist[root])
	{
		++color;
		g[color].push_back(root);
		q.push(make_pair(1,color));
	}
	for(int i=head[root]; i; i=edge[i].next)
	{
		int &v=edge[i].to;
		++color;
		dfs2(v,root);
		q.push(make_pair(g[color].size(),color));
	}
	for(int i=1; i*2<=k; ++i)
	{
		int x=q.top().second;
		q.pop();
		int y=q.top().second;
		q.pop();
		printf("%d %d\n",g[x].back(),g[y].back());
		g[x].pop_back(),g[y].pop_back();
		if(!g[x].empty())
			q.push(make_pair(g[x].size(),x));
		if(!g[y].empty())
			q.push(make_pair(g[y].size(),y));
	}
	return 0;
}


