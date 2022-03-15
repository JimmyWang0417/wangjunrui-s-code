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
const int N=1e6+5;
struct Edge
{
	int next,from,to,cap,flow;
	Edge(int _next=0,int _from=0,int _to=0,int _cap=0,int _flow=0):next(_next),from(_from),to(_to),cap(_cap),flow(_flow) {}
};
using std::min;
class Dinic
{
	private:
		Edge edge[N<<1];
		int head[N],num_edge=1;
		int dis[N];
		int cur[N];
		std::bitset<N>vis;
	public:
		int n,m,s,t;
		inline void add_edge(int from,int to,int cap=0,int flow=0)
		{
			edge[++num_edge]=Edge(head[from],from,to,cap,flow);
			head[from]=num_edge;
		}
		inline bool bfs()
		{
			vis.reset();
			std::queue<int>q;
			dis[s]=0;
			q.push(s);
			vis[s]=true;
			while(!q.empty())
			{
				int u=q.front();
				q.pop();
				for(re int i=head[u]; i; i=edge[i].next)
				{
					int &v=edge[i].to;
					if(!vis[v]&&edge[i].cap>edge[i].flow)
					{
						vis[v]=true;
						dis[v]=dis[u]+1;
						q.push(v);
					}
				}
			}
			return vis[t];
		}
		inline int dinic(int u,int a)
		{
			if(u==t||!a)
				return a;
			int flow=0;
			for(int &i=cur[u]; i; i=edge[i].next)
			{
				int &v=edge[i].to,f;
				if(dis[v]>dis[u]&&(f=dinic(v,min(a,edge[i].cap-edge[i].flow)))>0)
				{
					flow+=f;
					edge[i].flow+=f;
					edge[i^1].flow-=f;
					a-=f;
					if(!a)
						break;
				}
			}
			return flow;
		}
		inline int maxflow()
		{
			int flow=0;
			while(bfs())
			{
				for(re int i=1; i<=n; ++i)
					cur[i]=head[i];
				flow+=dinic(s,0x7fffffff);
			}
			return flow;
		}
		inline void main()
		{
			read(m,n);
			s=1,t=n;
			for(re int i=1; i<=m; ++i)
			{
				int u,v,w;
				read(u,v,w);
				add_edge(u,v,w);
				add_edge(v,u);
			}
			printf("%d\n",maxflow());
		}
} a;
signed main()
{
	a.main();
	return 0;
}

