#include<cstdio>
#include<cctype>
#include<vector>
#include<queue>
#include<cstring>
#define re register
using namespace std;
template<typename T>
inline void read(T &x)
{
	char s=getchar();
	x=0;
	bool flag=false;
	while(!isdigit(s))
	{
		if(s=='-')
			flag=true;
		s=getchar();
	}
	while(isdigit(s))
	{
		x=(x<<1)+(x<<3)+(s^'0');
		s=getchar();
	}
	if(flag)
		x=~x+1;
	return;
}

const int N=2e5+5,K=1e6+5,INF=0x3f3f3f3f;
struct Edge
{
	int next,to,dis;
	Edge() {}
	Edge(int n,int t,int d):next(n),to(t),dis(d) {}
};
Edge edge[N<<1];
int head[N],num_edge;
inline void add_edge(int from,int to,int dis)
{
	edge[++num_edge]=Edge(head[from],to,dis);
	head[from]=num_edge;
}

#define size sze
bool vis[N];
int n,k;
int maxn[N],size[N],sum,root;
inline void getroot(int u,int fa)
{
	size[u]=1;
	maxn[u]=0;
	for(re int i=head[u]; i; i=edge[i].next)
	{
		int &v=edge[i].to;
		if(vis[v]||v==fa)
			continue;
		getroot(v,u);
		size[u]+=size[v];
		maxn[u]=max(maxn[u],size[v]);
	}
	maxn[u]=max(maxn[u],sum-size[u]);
	if(maxn[u]<maxn[root])
		root=u;
}
#undef size
int cnt,dis[N];
vector<pair<int,int> >tmp;
inline void getdis(int u,int fa,int dep)
{
	if(dis[u]>k)
		return;
	tmp.push_back(make_pair(dis[u],dep));
	for(re int i=head[u]; i; i=edge[i].next)
	{
		int &v=edge[i].to,&w=edge[i].dis;
		if(vis[v]||v==fa)
			continue;
		dis[v]=dis[u]+w;
		getdis(v,u,dep+1);
	}
}
int ans=INF;
int judge[K];
queue<int>que;
inline void calc(int u)
{
	for(re int i=head[u]; i; i=edge[i].next)
	{
		int &v=edge[i].to,&w=edge[i].dis;
		if(vis[v])
			continue;
		dis[v]=w;
		tmp.clear();
		getdis(v,u,1);
		for(re int i=0; i<tmp.size(); ++i)
			ans=min(ans,judge[k-tmp[i].first]+tmp[i].second);
		for(re int i=0; i<tmp.size(); ++i)
		{
			judge[tmp[i].first]=min(judge[tmp[i].first],tmp[i].second);
			que.push(tmp[i].first);
		}
	}
	while(!que.empty())
	{
		judge[que.front()]=INF;
		que.pop();
	}
}
inline void solve(int u)
{
	vis[u]=true;
	judge[0]=0;
	calc(u);
	for(re int i=head[u]; i; i=edge[i].next)
	{
		int &v=edge[i].to,&w=edge[i].dis;
		if(vis[v])
			continue;
		maxn[root=0]=sum=sze[v];
		getroot(v,u);
		getroot(root,u);
		solve(root);
	}
}
int main()
{
//	freopen("ans.in","r",stdin);
	read(n),read(k);
	memset(judge,INF,sizeof(judge));
	for(re int i=1; i<n; ++i)
	{
		int u,v,w;
		read(u),read(v),read(w);
		++u,++v;
		add_edge(u,v,w);
		add_edge(v,u,w);
	}
	maxn[root=0]=sum=n;
	getroot(1,0);
	getroot(root,0);
	solve(root);
	printf("%d\n",ans>=n?-1:ans);
	return 0;
}
