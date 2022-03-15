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
const int INF=0x7fffffff;
struct Edge
{
	int next,to,flow,cap;
} edge[N*10];
int head[N],num_edge=1;
inline void add_edge(int from,int to,int cap,bool flag=true)
{
	edge[++num_edge].next=head[from];
	edge[num_edge].to=to;
	edge[num_edge].flow=0;
	edge[num_edge].cap=cap;
	head[from]=num_edge;
	if(flag)
		add_edge(to,from,0,false);
}
int S,T;
int dis[N],cur[N];
inline bool bfs()
{
	memset(dis,0,sizeof(dis));
	memcpy(cur,head,sizeof(head));
	queue<int>q;
	q.push(S);
	dis[S]=1;
	while(!q.empty())
	{
		int u=q.front();
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
	return dis[T];
}
inline int dinic(int u,int flow)
{
	if(u==T)
		return flow;
	int res=0;
	for(int &i=cur[u]; i; i=edge[i].next)
	{
		int &v=edge[i].to;
		if(dis[v]==dis[u]+1&&edge[i].cap>edge[i].flow)
		{
			int f=dinic(v,min(flow,edge[i].cap-edge[i].flow));
			if(f)
			{
				res+=f;
				flow-=f;
				edge[i].flow+=f;
				edge[i^1].flow-=f;
				if(!flow)
					break;
			}
		}
	}
	return res;
}
inline int maxflow()
{
	int res=0;
	while(bfs())
		res+=dinic(S,INF);
	return res;
}
int n,m;
int in[N],out[N];
inline void work()
{
	num_edge=1;
	int s=n+m+1,t=n+m+2;
	S=n+m+3,T=n+m+4;
	clear(head,1,n+m+4,0);
	clear(in,1,n+m+2,0);
	clear(out,1,n+m+2,0);
	for(int i=1; i<=m; ++i)
	{
		int val;
		read(val);
		in[t]+=val,out[i+n]+=val;
		add_edge(i+n,t,INF-val);
	}
	for(int i=1; i<=n; ++i)
	{
		int C,D;
		read(C,D);
		add_edge(s,i,D);
		while(C--)
		{
			int x,l,r;
			read(x,l,r);
			++x;
			in[x+n]+=l,out[i]+=l;
			add_edge(i,x+n,r-l);
		}
	}
	int sum=0;
	for(int i=1; i<=n+m+2; ++i)
	{
		if(in[i]==out[i])
			continue;
		if(in[i]>out[i])
		{
			add_edge(S,i,in[i]-out[i]);
			sum+=in[i]-out[i];
		}
		else
			add_edge(i,T,out[i]-in[i]);
	}
	add_edge(t,s,INF);
	if(maxflow()<sum)
	{
		printf("-1\n\n");
		return;
	}
	int flow=edge[num_edge^1].flow;
	edge[num_edge].flow=edge[num_edge].cap=edge[num_edge^1].flow=edge[num_edge^1].cap=0;
	S=s,T=t;
	printf("%d\n\n",flow+maxflow());
}
signed main()
{
	while(scanf("%d%d",&n,&m)!=EOF)
		work();
	return 0;
}


