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
const int N=20*20+5,INF=0x7fffffff;
int n,m;
inline int calc(int x,int y)
{
	return x*(m-1)+y;
}
struct Edge
{
	int next,to,cap,flow;
} edge[N*N<<1];
int head[N],num_edge=1;
inline void add_edge(int from,int to,int cap=INF,bool flag=true)
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
#define t (n*m+1)
int dis[N],cur[N];
inline bool bfs()
{
	memset(dis,0,sizeof(dis));
	std::queue<int>q;
	for(re int i=s; i<=t; ++i)
		cur[i]=head[i];
	dis[s]=1;
	q.push(s);
	while(!q.empty())
	{
		int u=q.front();
		q.pop();
		if(u==t)
			return true;
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
	if(u==t)
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
				if(!flow)
					return res;
			}
		}
	}
	return res;
}
signed main()
{
	ll ans=0;
	read(n,m);
	for(re int i=1; i<=n; ++i)
		for(re int j=1; j<=m; ++j)
		{
			int w;
			read(w);
			if(w>=0)
			{
				ans+=w;
				add_edge(s,calc(i,j),w);
				printf("%d %d\n",s,calc(i,j));
			}
			else
				add_edge(calc(i,j),t),printf("%d %d\n",calc(i,j),t);
			read(w);
			for(re int k=1; k<=w; ++k)
			{
				int x,y;
				read(x,y);
				++x,++y;
				add_edge(calc(x,y),calc(i,j));
				printf("%d %d\n",calc(x,y),calc(i,j));
			}
		}
	for(re int i=1; i<=n; ++i)
		for(re int j=2; j<=m; ++j)
			add_edge(calc(i,j-1),calc(i,j)),printf("%d %d\n",calc(i,j-1),calc(i,j));
//	printf("%lld\n",ans);
	while(bfs())
		ans-=dinic(s,INF);
	printf("%lld\n",ans);
	return 0;
}


