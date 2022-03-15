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
	char ss=(char)getchar();
	bool f=false;
	while(!(ss>='0'&&ss<='9'))
	{
		if(ss=='-')
			f=true;
		ss=(char)getchar();
	}
	while(ss>='0'&&ss<='9')
	{
		x=(x<<1)+(x<<3)+ss-'0';
		ss=(char)getchar();
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
const int N=805,M=1e4+5;
int n,m,s,t;
struct Edge
{
	int next,to,cap,flow;
} edge[M<<2];
int head[N],num_edge=1;
inline void add_edge(int from,int to,int cap,bool flag=true)
{
	edge[++num_edge].next=head[from];
	edge[num_edge].to=to;
	edge[num_edge].cap=cap;
	edge[num_edge].flow=0;
	head[from]=num_edge;
	if(flag)
		add_edge(to,from,0,false);
}
int dis[N],cur[N];
inline bool bfs()
{
	std::queue<int>q;
	q.push(s);
	memset(dis,0,sizeof(dis));
	dis[s]=1;
	for(re int i=1; i<=n; ++i)
		cur[i]=head[i];
	while(!q.empty())
	{
		int u=q.front();
		if(u==t)
			return true;
		q.pop();
		for(re int i=head[u]; i; i=edge[i].next)
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
inline int dinic(int u,int flow)
{
	if(u==t||!flow)
		return flow;
	int res=0;
	for(int &i=cur[u]; i; i=edge[i].next)
	{
		int &v=edge[i].to;
		if(dis[v]==dis[u]+1&&edge[i].cap>edge[i].flow)
		{
			int f=dinic(v,std::min(flow,edge[i].cap-edge[i].flow));
			if(f)
			{
				res+=f;
				edge[i].flow+=f;
				edge[i^1].flow-=f;
				flow-=f;
			}
			if(!flow)
				return res;
		}
	}
	return res;
}
std::bitset<N>vis;
int ans;
inline void dfs1(int u)
{
	for(re int i=head[u]; i; i=edge[i].next)
	{
		int &v=edge[i].to;;
		if(!vis[v]&&edge[i].cap>edge[i].flow)
		{
			vis[v]=true;
			++ans;
			dfs1(v);
		}
	}
}
inline void dfs2(int u)
{
	for(re int i=head[u]; i; i=edge[i].next)
	{
		int &v=edge[i].to;
		if(!vis[v]&&edge[i^1].cap>edge[i^1].flow)
		{
			vis[v]=true;
			++ans;
			dfs2(v);
		}
	}
}
signed main()
{
	while(read(n,m,s,t),n||m||s||t)
	{
		for(re int i=1; i<=m; ++i)
		{
			int u,v,w;
			read(u,v,w);
			add_edge(u,v,w);
			add_edge(v,u,w);
		}
//		int sum=0;
		while(bfs())
			/*sum+=*/dinic(s,0x7fffffff);
//		printf("%d\n",sum);
		ans=2;
		vis[s]=vis[t]=true;
		dfs1(s),dfs2(t);
		puts(ans==n?"UNIQUE":"AMBIGUOUS");
		vis.reset();
		memset(head,0,sizeof(head));
		num_edge=1;
	}
	return 0;
}


