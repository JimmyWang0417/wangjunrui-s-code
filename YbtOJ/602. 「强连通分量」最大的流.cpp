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
const int N=1e4+5,base=3005;
int n,m;
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
bool sgn[N];
int belong[N],color;
int st[N],top;
inline void tarjan(int u,int _fa)
{
	st[++top]=u;
	dfn[u]=low[u]=++dfstime;
	for(int i=head[u]; i; i=edge[i].next)
	{
		if(sgn[i])
			continue;
		int &v=edge[i].to;
		if(v==_fa)
			continue;
		if(!dfn[v])
		{
			tarjan(v,u);
			low[u]=min(low[u],low[v]);
		}
		else
			low[u]=min(low[u],dfn[v]);
	}
	if(dfn[u]==low[u])
	{
		belong[u]=++color;
		while(st[top]!=u)
			belong[st[top--]]=color;
		--top;
	}
}
ull hashval[N];
inline void solve(int pos)
{
	memset(dfn,dfstime=0,sizeof(dfn));
	memset(low,0,sizeof(low));
	sgn[pos]=sgn[pos+1]=true;
	color=0;
	for(int i=1; i<=n; ++i)
		if(!dfn[i])
			tarjan(i,0);
	for(int i=1; i<=n; ++i)
		hashval[i]=hashval[i]*base+belong[i];
	for(int i=1; i<=n; ++i)
		sgn[pos]=sgn[pos+1]=false;
}
int f[N];
inline int find(int u)
{
	return !f[u]?u:f[u]=find(f[u]);
}
signed main()
{
	read(n,m);
	for(int i=1; i<=m; ++i)
	{
		int u,v;
		read(u,v);
		add_edge(u,v);
		add_edge(v,u);
		u=find(u),v=find(v);
		if(u==v)
			continue;
		f[u]=v;
	}
	for(int i=1; i<=num_edge; i+=2)
		solve(i);
	solve(num_edge+1);
	int ans=0;
	for(int i=1; i<n; ++i)
		for(int j=i+1; j<=n; ++j)
		{
			if(find(i)!=find(j))
				continue;
			if(belong[i]!=belong[j])
				++ans;
			else if(hashval[i]!=hashval[j])
				ans+=2;
			else
				ans+=3;
		}
	printf("%d\n",ans);
	return 0;
}


