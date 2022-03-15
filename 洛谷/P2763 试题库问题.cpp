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
struct Edge
{
	int next,to,cap,flow;
} edge[N];
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
int n,k;
#define s 0
#define t (n+k+1)
int dis[N],cur[N];
bitset<N>vis;
inline bool bfs()
{
	memset(dis,0,sizeof(dis));
	memcpy(cur,head,sizeof(head));
	vis.set();

	queue<int>q;
	dis[s]=1;
	q.push(s);
	while(!q.empty())
	{
		int u=q.front();
		q.pop();
		if(u==t)
			return true;
		for(int i=head[u]; i; i=edge[i].next)
		{
			int &v=edge[i].to;
			if(edge[i].cap>edge[i].flow&&!dis[v])
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
	vis.reset(u);
	int res=0;
	for(int &i=cur[u]; i; i=edge[i].next)
	{
		int &v=edge[i].to;
		if(vis[v]&&dis[v]==dis[u]+1&&edge[i].cap>edge[i].flow)
		{
			int f=dinic(v,min(flow,edge[i].cap-edge[i].flow));
			if(f)
			{
				res+=f;
				flow-=f;

				edge[i].flow+=f;
				edge[i^1].flow-=f;

				if(!flow)
				{
					vis.set(u);
					break;
				}
			}
		}
	}
	return res;
}
vector<int>g[N];
signed main()
{
	int m=0;
	read(k,n);
	for(int i=1; i<=k; ++i)
	{
		int val;
		read(val);
		m+=val;
		add_edge(s,i,val);
	}
	for(int i=1; i<=n; ++i)
	{
		add_edge(i+k,t,1);
		int cnt;
		read(cnt);
		while(cnt--)
		{
			int v;
			read(v);
			add_edge(v,i+k,1);
		}
	}
	int flow=0;
	while(bfs())
		flow+=dinic(s,0x7fffffff);
	if(flow!=m)
	{
		printf("No Solution!\n");
		return 0;
	}
	for(int i=2; i<=num_edge; i+=2)
		if(1<=edge[i^1].to&&edge[i^1].to<=k&&edge[i].flow==1)
			g[edge[i^1].to].push_back(edge[i].to-k);
	for(int i=1; i<=k; ++i)
	{
		printf("%d:",i);
		for(auto v:g[i])
			printf(" %d",v);
		putchar('\n');
	}
	return 0;
}


