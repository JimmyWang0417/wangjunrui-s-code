#include<cstdio>
#include<vector>
#include<queue>
#include<algorithm>
#include<cstring>
#define re register
#define co const
using namespace std;
template<typename T>
inline void read(T&x)
{
	x=0;
	char s=getchar();
	bool f=false;
	while(!(s>='0'&&s<='9'))
	{
		if(s=='-')
			f=true;
		s=getchar();
	}
	while(s>='0'&&s<='9')
	{
		x=(x<<1)+(x<<3)+s-'0';
		s=getchar();
	}
	if(f)
		x=(~x)+1;
}
const int N=5010,M=50010,INF=0x3f3f3f3f;
struct Edge
{
	int from,to,cap,flow,cost;
	Edge(co int &u,co int &v,co int &c,co int &f,co int &cos):from(u),to(v),cap(c),flow(f),cost(cos) {}
};
struct MCMF
{
	int n,m,p[N],a[N],dis[N];
	vector<Edge>edge;
	vector<int>g[N];
	queue<int>q;
	bool exist[N];
	inline void init(const int &n)
	{
		this->n=n;
		for(re int i=1; i<=n; i++)
			g[i].clear();
		edge.clear();
	}
	inline void add_edge(co int &from,co int &to,co int &cap,co int &cost)
	{
		edge.push_back(Edge(from,to,cap,0,cost));
		edge.push_back(Edge(to,from,0,0,-cost));
		m=edge.size();
		g[from].push_back(m-2);
		g[to].push_back(m-1);
	}
	inline bool spfa(co int &s,co int &t,int &flow,long long &cost)
	{
		memset(dis,INF,sizeof(dis));
		//printf("%d\n",dis[1]);
		dis[s]=0;
		p[s]=0;
		a[s]=INF;
		q.push(s);
		int u;
		while(!q.empty())
		{
			u=q.front();
			q.pop();
			exist[u]=false;
			//printf("%d\n",a[u]);
			for(re int i=0; i<g[u].size(); i++)
			{
				//printf("%d\n",i);
				Edge &e=edge[g[u][i]];
				if(e.cap>e.flow&&dis[e.to]>dis[u]+e.cost)
				{
					dis[e.to]=dis[u]+e.cost;
					p[e.to]=g[u][i];
					a[e.to]=min(a[u],e.cap-e.flow);
					if(!exist[e.to])
					{
						q.push(e.to);
						exist[e.to]=true;
					}
				}
			}
		}
		if(dis[t]==INF)
			return false;
		flow+=a[t];
		cost+=(long long)dis[t]*a[t];
		for(re int u=t; u!=s; u=edge[p[u]].from)
		{
			edge[p[u]].flow+=a[t];
			edge[p[u]^1].flow-=a[t];
		}
		return true;
	}
	inline void mincos_max_flow(co int &s,co int &t,long long &cost,int &flow)
	{
		cost=flow=0;
		while(spfa(s,t,flow,cost));
	}
} a;
int n,m,s,t;
int main()
{
	read(n);
	read(m);
	read(s);
	read(t);
	long long cost;
	int flow;
	for(re int i=1,u,v,w,f; i<=m; i++)
	{
		read(u);
		read(v);
		read(w);
		read(f);
		a.add_edge(u,v,w,f);
	}
	a.mincos_max_flow(s,t,cost,flow);
	printf("%d %lld\n",flow,cost);
	return 0;
}
