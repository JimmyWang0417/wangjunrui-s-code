#include<cstdio>
#include<vector>
#include<algorithm>
#include<queue>
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
const int N=1e6+10,INF=0x3f3f3f3f;
struct Edge
{
	int from,to,cap,flow;
	Edge(co int u,co int v,co int c,co int f):from(u),to(v),cap(c),flow(f) {}
};
struct Edmonds_Karp
{
	int n,m;
	vector<Edge>edge;
	vector<int>g[N];
	int a[N],p[N];
	inline void init(int n)
	{
		for(re int i=0; i<n; i++)
			g[i].clear();
		edge.clear();
		return;
	}
	inline void read_EK()
	{
		read(m);
		read(n);
		for(re int i=1,u,v,w; i<=m; i++)
		{
			read(u);
			read(v);
			read(w);
			add_edge(u,v,w);
		}
		return;
	}
	inline void add_edge(co int from,co int to,co int cap)
	{
		edge.push_back(Edge(from,to,cap,0));
		edge.push_back(Edge(to,from,0,0));
		int m=edge.size();
		g[from].push_back(m-2);
		g[to].push_back(m-1);
		return;
	}
	inline int max_flow(co int s,co int t)
	{
		int flow=0;
		while(1)
		{
			memset(a,0,sizeof(a));
			//printf("%d",a[1]);
			queue<int>q;
			q.push(s);
			a[s]=INF;
			while(!q.empty())
			{
				int u=q.front();
				q.pop();
				for(re int i=0; i<g[u].size(); i++)
				{
					Edge &e=edge[g[u][i]];
					if(!a[e.to]&&e.cap>e.flow)
					{
						p[e.to]=g[u][i];
						a[e.to]=min(a[u],e.cap-e.flow);
						q.push(e.to);
					}
				}
				if(a[t])
					break;
			}
			if(!a[t])
				break;
			flow+=a[t];
			for(re int u=t; u!=s; u=edge[p[u]].from)
			{
				edge[p[u]].flow+=a[t];
				edge[p[u]^1].flow-=a[t];
			}
			//printf("%d\n",a[t]);
		}
		return flow;
	}
} e;
int main()
{
	e.read_EK();
	printf("%d\n",e.max_flow(1,e.n));
	return 0;
}

