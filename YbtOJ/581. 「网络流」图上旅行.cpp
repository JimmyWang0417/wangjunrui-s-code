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
const int N=2000+5;
const double INF=1e9,eps=1e-9;
int n,m,k;
pair<int,int>e[N];
vector<int>g[N];
vector<pair<int,int> >limit[N];
bool vis[N];
double dp[N];
int dis[N];
int cur[N];
#define s (0)
#define t (m+1)
namespace nmsl
{
	struct Edge
	{
		int next,to;
		double flow,cap;
	} edge[N];
	int head[N],num_edge=1;
	inline void add_edge(int from,int to,double cap,bool flag=true)
	{
//	printf("%d %d %lf\n",from,to,cap);
		edge[++num_edge].next=head[from];
		edge[num_edge].to=to;
		edge[num_edge].cap=cap;
		edge[num_edge].flow=0;
		head[from]=num_edge;
		if(flag)
			add_edge(to,from,0,false);
	}
	inline bool bfs()
	{
		fill(dis+s,dis+t+1,0);
		for(int i=s; i<=t; ++i)
			cur[i]=head[i];
		dis[s]=1;
		queue<int>q;
		q.push(s);
		while(!q.empty())
		{
			int u=q.front();
			if(u==t)
				return true;
			q.pop();
			for(int i=head[u]; i; i=edge[i].next)
			{
				int &v=edge[i].to;
				if(!dis[v]&&edge[i].cap>edge[i].flow)
				{
					dis[v]=dis[u]+1;
					q.push(v);
				}
			}
		}
		return false;
	}
	inline double dinic(int u,double flow)
	{
		if(u==t||!flow)
			return flow;
		double res=0;
		for(int &i=cur[u]; i; i=edge[i].next)
		{
			int &v=edge[i].to;
			if(dis[v]==dis[u]+1&&edge[i].cap>edge[i].flow)
			{
				double f=dinic(v,min(edge[i].cap-edge[i].flow,flow));
				if(f)
				{
					res+=f;
					edge[i].flow+=f;
					edge[i^1].flow-=f;
					flow-=f;
					if(!flow)
						return res;
				}
			}

		}
		return res;
	}
	inline double Dinic()
	{
		double ans=0;
		while(bfs())
			ans+=dinic(s,INF);
		return ans;
	}
	inline void clear()
	{
		memset(head,0,sizeof(head));
		num_edge=1;
	}
}
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
inline bool check(int u,double val)
{
//	printf("%d %lf\n",u,val);
	nmsl::clear();
	for(auto i:limit[u])
		nmsl::add_edge(i.first,i.second,INF);
	double sum=0;
	for(int i=head[u]; i; i=edge[i].next)
	{
		int &v=edge[i].to;
		double w=1+dp[v]-val;
		if(w>0)
		{
			sum+=w;
			nmsl::add_edge(s,i,w);
		}
		else
			nmsl::add_edge(i,t,-w);
	}
	sum-=nmsl::Dinic();
//	putchar('\n');
	return sum>0;
}
inline void calc(int u)
{
	double l=0,r=0,&ans=dp[u];
	for(int i=head[u]; i; i=edge[i].next)
	{
		int &v=edge[i].to;
		r=max(dp[v]+1,r);
	}
	while(r-l>=eps)
	{
		double mid=(l+r)/2;
		if(check(u,mid))
			ans=l=mid;
		else
			r=mid;
	}
}
inline void dfs(int u)
{
	vis[u]=true;
	for(int i=head[u]; i; i=edge[i].next)
	{
		int &v=edge[i].to;
		if(!vis[v])
			dfs(v);
	}
	calc(u);
}
signed main()
{
	freopen("trip.in","r",stdin),freopen("trip.out","w",stdout);
	read(n,m,k);
	for(int i=1; i<=m; ++i)
	{
		int x,y;
		read(x,y);
		add_edge(x,y);
		e[i]=make_pair(x,y);
	}
	for(int i=1; i<=k; ++i)
	{
		int x,y;
		read(x,y);
		if(x==y)
			continue;
		limit[e[x].first].push_back(make_pair(x,y));
	}
	dfs(1);
//	for(int i=1; i<=n; ++i)
//		cout<<dp[i]<<' ';
//	cout<<endl;
	cout<<dp[1]<<endl;
	return 0;
}


