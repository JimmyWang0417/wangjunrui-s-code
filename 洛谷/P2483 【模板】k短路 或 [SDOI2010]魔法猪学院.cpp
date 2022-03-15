#include <queue>
#include <cstdio>
#include <vector>
#include <cstring>
#include <algorithm>
#define re register
using namespace std;
const int N=5e3+5,M=2e5+5;
struct Tree
{
	int ed,dist;
	int l,r;
	double val;
} tree[6*M];
int root[N],cnt;
inline int newnode(int ed,double val)
{
	tree[++cnt].val=val;
	tree[cnt].ed=ed;
	return cnt;
}
#define lc(x) tree[x].l
#define rc(x) tree[x].r
inline int merge(int x,int y)
{
	if(!x||!y)
		return x|y;
	if(tree[x].val>tree[y].val)
		swap(x,y);
	int now;
	tree[now=++cnt]=tree[x];
	rc(now)=merge(rc(now),y);
	if(tree[lc(now)].dist<tree[rc(now)].dist)
		swap(lc(now),rc(now));
	tree[now].dist=tree[rc(now)].dist+1;
	return now;
}
struct Edge
{
	int next,to;
	double dis;
};
int pre[N];
double dis[N];
bool vis[N];
struct Queue
{
	int u;
	double d;
	Queue(int _u=0,double _d=0.0):u(_u),d(_d) {}
	inline bool operator > (const Queue&rhs)const
	{
		return d>rhs.d;
	}
	inline bool operator < (const Queue&rhs)const
	{
		return d<rhs.d;
	}
} seq[N];
int n,m;
double E;
struct way
{
	int head[N],num_edge;
	Edge edge[M];
	inline void add_edge(int from,int to,double _dis)
	{
		edge[++num_edge].next=head[from];
		edge[num_edge].to=to;
		edge[num_edge].dis=_dis;
		head[from]=num_edge;
	}
	inline void dijkstra(int st)
	{
		memset(dis,127,sizeof(dis));
		dis[st]=0.0;
		priority_queue<Queue,vector<Queue>,greater<Queue> >q;
		q.push(Queue(st,0.0));
		while(!q.empty())
		{
			int u=q.top().u;
			q.pop();
			if(vis[u])
				continue;
			vis[u]=true;
			for(re int i=head[u]; i; i=edge[i].next)
			{
				int &v=edge[i].to;
				double &w=edge[i].dis;
				if(dis[v]>dis[u]+w)
				{
					dis[v]=dis[u]+w;
					pre[v]=i;
					q.push(Queue(v,dis[v]));
				}
			}
		}
	}
} G,R;
int main()
{
	scanf("%d%d%lf",&n,&m,&E);
	for(re int i=1; i<=m; ++i)
	{
		int u,v;
		double w;
		scanf("%d%d%lf",&u,&v,&w);
		G.add_edge(u,v,w);
		R.add_edge(v,u,w);
	}
	R.dijkstra(n);
	for(re int i=1; i<=n; ++i)
		seq[i]=Queue(i,dis[i]);
	stable_sort(seq+1,seq+1+n);
	for(re int a=1; a<=n; ++a)
	{
		int u=seq[a].u;
		if(u==n)
			continue;
		for(re int i=G.head[u]; i; i=G.edge[i].next)
		{
			if(i!=pre[u])
				root[u]=merge(root[u],newnode(G.edge[i].to,dis[G.edge[i].to]+G.edge[i].dis-dis[u]));
		}
		root[u]=merge(root[u],root[G.edge[pre[u]].to]);
	}
	priority_queue<Queue,vector<Queue>,greater<Queue> >q;
	if(root[1])
		q.push(Queue(root[1],tree[root[1]].val));
	int ans=0;
	if(E>=dis[1])
	{
		E-=dis[1];
		++ans;
	}
	while(!q.empty()&&E>0.0)
	{
		Queue u=q.top();
		q.pop();
		if(E<u.d+dis[1])
			break;
		E-=u.d+dis[1];
		++ans;
		if(lc(u.u))
			q.push(Queue(lc(u.u),u.d-tree[u.u].val+tree[lc(u.u)].val));
		if(rc(u.u))
			q.push(Queue(rc(u.u),u.d-tree[u.u].val+tree[rc(u.u)].val));
		if(root[tree[u.u].ed])
			q.push(Queue(root[tree[u.u].ed],u.d+tree[root[tree[u.u].ed]].val));
	}
	printf("%d\n",ans);
	return 0;
}
