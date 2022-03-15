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
const int N=2e5+5;
priority_queue<int>q[N],nowq;
inline int merge(int x,int y)
{
	if(q[x].size()<q[y].size())
		swap(x,y);
	while(!q[y].empty())
	{
		nowq.push(max(q[x].top(),q[y].top()));
		q[x].pop(),q[y].pop();
	}
	while(!nowq.empty())
	{
		q[x].push(nowq.top());
		nowq.pop();
	}
	return x;
}
int n,root[N];
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
int a[N];
inline void dfs(int u)
{
	root[u]=u;
	for(int i=head[u]; i; i=edge[i].next)
	{
		int &v=edge[i].to;
		dfs(v);
		root[u]=merge(root[u],root[v]);
	}
	q[root[u]].push(a[u]);
}
signed main()
{
	read(n);
	for(int i=1; i<=n; ++i)
		read(a[i]);
	for(int i=2;i<=n;++i)
	{
		int fa;
		read(fa);
		add_edge(fa,i);
	}
	dfs(1);
	ll sum=0;
	while(!q[root[1]].empty())
	{
		sum+=q[root[1]].top();
		q[root[1]].pop();
	}
	printf("%lld\n",sum);
	return 0;
}


