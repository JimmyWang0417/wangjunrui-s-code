#include<cstdio>
#include<vector>
#include<cstring>
#include<queue>
#define re register
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
const int N=10000+10,M=100000+10,INF=0x7fffffff;
struct Edge
{
	int from,to,cap,flow;
	Edge(int u,int v,int c,int f):from(u),to(v),cap(c),flow(f) {}
};
struct Edmonds_Karp
{
	int n,m;
	vector<Edge>edge;
	vector<int>G[N];
	int a[N],p[N];
	inline void init(int n)
	{
		for(re int i=0; i<n; i++)
			G[i].clear();
		edge.clear();
	}
	inline void add_edge(int from,int to,int cap)
	{
		edge.push_back(Edge(from,to,cap,0));
		edge.push_back(Edge(to,from,0,0));
		int m=edge.size();
		G[from].push_back(m-2);
		G[to].push_back(m-1);
	}
	inline int max_flow(int s,int t)
	{
		int flow=0;
		while(1)
		{
			memset(a,0,sizeof(a));
			queue<int>q;
			q.push(s);
			a[s]=INF;
			while(!q.empty())
			{
				int u=q.front();
				q.pop();
				for(re int i=0; i<G[u].size(); i++)
				{
					Edge & e=edge[G[u][i]];
					if(!a[e.to]&&e.cap>e.flow)
					{
						p[e.to]=G[u][i];
						a[e.to]=min(a[u],e.cap-e.flow);
						q.push(e.to);
					}
				}
				if(a[t])
					break;
			}
			if(!a[t])
				break;
			for(re int u=t; u!=s; u=edge[p[u]].from)
			{
				edge[p[u]].flow+=a[t];
				edge[p[u]^1].flow-=a[t];
			}
			flow+=a[t];
		}
		return flow;
	}
} a;
int n,m,s,t,ans=0;
int main()
{
	read(n);
	read(m);
	for(re int i=1,x,y,z; i<=m; i++)
	{
		read(x);
		read(y);
		a.add_edge(x,y,1);
	}
	for(re int i=1; i<=n; i++)
		for(re int j=1; j<=n; j++)
			ans=max(a.max_flow(i,j),ans);
	printf("%lld\n",ans);
	return 0;
}
