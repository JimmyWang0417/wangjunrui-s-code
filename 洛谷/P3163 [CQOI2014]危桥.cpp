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
const int N=105,INF=0x7fffffff;
char str[N][N];
int n,a1,a2,an,b1,b2,bn;
struct Edge
{
	int next,to,cap,flow;
} edge[N*N];
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
#define s 0
#define t (n+1)
int dis[N];
int cur[N];
inline bool bfs()
{
	std::queue<int>q;
	q.push(s);
	memset(dis,0,sizeof(dis));
	dis[s]=1;
	for(re int i=s; i<=t; ++i)
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
inline void work()
{
	++a1,++a2,++b1,++b2;
	an<<=1,bn<<=1;
	for(re int i=1; i<=n; ++i)
	{
		scanf("%s",str[i]+1);
		for(re int j=1; j<=n; ++j)
			if(str[i][j]=='O')
				add_edge(i,j,2);
			else if(str[i][j]=='N')
				add_edge(i,j,INF);
	}
	add_edge(s,a1,an),add_edge(s,b1,bn);
	add_edge(a2,t,an),add_edge(b2,t,bn);
	int ans1=0;
	while(bfs())
		ans1+=dinic(s,INF);
	memset(head,0,sizeof(head));
	num_edge=1;
	for(re int i=1; i<=n; ++i)
		for(re int j=1; j<=n; ++j)
			if(str[i][j]=='O')
				add_edge(i,j,2);
			else if(str[i][j]=='N')
				add_edge(i,j,INF);
	add_edge(s,a1,an),add_edge(s,b2,bn);
	add_edge(a2,t,an),add_edge(b1,t,bn);
	int ans2=0;
	while(bfs())
		ans2+=dinic(s,INF);
	printf(ans1==an+bn&&ans2==an+bn?"Yes\n":"No\n");
	memset(head,0,sizeof(head));
	num_edge=1;
}
signed main()
{
	while(scanf("%d%d%d%d%d%d%d",&n,&a1,&a2,&an,&b1,&b2,&bn)!=EOF)
		work();
	return 0;
}


