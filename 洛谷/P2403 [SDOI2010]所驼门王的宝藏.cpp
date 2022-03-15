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
using namespace std;
const int N=2e6+1e5+5;
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
//	printf("%d %d\n",from,to);
}
int n,r,c;
map<pair<int,int>,int>mp;
struct node
{
	int x,y,t;
} a[N];
int low[N],dfn[N],dfstime;
int belong[N],col,sum[N];
int st[N],top;
inline void tarjan(int u)
{
	st[++top]=u;
	dfn[u]=low[u]=++dfstime;
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
		belong[u]=++col;
		while(st[top]!=u)
			belong[st[top--]]=col;
		--top;
	}
}
int dp[N],in[N];
signed main()
{
//	freopen("ans.in","r",stdin);
	read(n,r,c);
	for(int i=1; i<=n; ++i)
	{
		int &x=a[i].x,&y=a[i].y,&t=a[i].t;
		read(x,y,t);
		add_edge(x+n,i);
		add_edge(y+r+n,i);
		if(t==1)
			add_edge(i,x+n);
		else if(t==2)
			add_edge(i,y+r+n);
		mp[make_pair(x,y)]=i;
	}
	for(int i=1; i<=n; ++i)
	{
		int &x=a[i].x,&y=a[i].y,&t=a[i].t;
		if(t==3)
		{
			if(mp[make_pair(x-1,y)])
				add_edge(i,mp[make_pair(x-1,y)]);
			if(mp[make_pair(x+1,y)])
				add_edge(i,mp[make_pair(x+1,y)]);
			if(mp[make_pair(x,y-1)])
				add_edge(i,mp[make_pair(x,y-1)]);
			if(mp[make_pair(x,y+1)])
				add_edge(i,mp[make_pair(x,y+1)]);


			if(mp[make_pair(x-1,y-1)])
				add_edge(i,mp[make_pair(x-1,y-1)]);
			if(mp[make_pair(x+1,y+1)])
				add_edge(i,mp[make_pair(x+1,y+1)]);
			if(mp[make_pair(x+1,y-1)])
				add_edge(i,mp[make_pair(x+1,y-1)]);
			if(mp[make_pair(x-1,y+1)])
				add_edge(i,mp[make_pair(x-1,y+1)]);
		}
	}
	for(int i=1; i<=n+r+c; ++i)
		if(!dfn[i])
			tarjan(i);
	for(int i=1; i<=n; ++i)
		++sum[belong[i]];
	int cnt=0;
	for(int u=1; u<=n+r+c; ++u)
		for(int i=head[u]; i; i=edge[i].next)
		{
			int &v=edge[i].to;
			if(belong[u]!=belong[v])
			{
				a[++cnt].x=belong[u],a[cnt].y=belong[v];
				++in[belong[v]];
			}
		}
	memset(head,num_edge=0,sizeof(head));
	for(int i=1; i<=cnt; ++i)
		add_edge(a[i].x,a[i].y);
	queue<int>q;
	for(int i=1; i<=col; ++i)
		if(!in[i])
		{
			q.push(i);
			dp[i]=sum[i];
		}
	int ans=0;
	while(!q.empty())
	{
		int u=q.front();
		q.pop();
		ans=max(ans,dp[u]);
		for(re int i=head[u]; i; i=edge[i].next)
		{
			int &v=edge[i].to;
			dp[v]=max(dp[v],dp[u]+sum[v]);
			if(!--in[v])
				q.push(v);
		}
	}
	printf("%d\n",ans);
	return 0;
}

