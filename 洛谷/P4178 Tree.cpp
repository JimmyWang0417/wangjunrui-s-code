#include<cstdio>
#include<vector>
#include<algorithm>
#define re register
using namespace std;

template <typename T>
inline void read(T &x)
{
	x=0;
	char s=(char)getchar();
	bool flag=false;
	while(s<'0'||s>'9')
	{
		if(s=='-')
			flag=true;
		s=(char)getchar();
	}
	while(s>='0'&&s<='9')
	{
		x=(x<<1)+(x<<3)+(s^'0');
		s=(char)getchar();
	}
	if(flag)
		x=~x+1;
	return;
}

const int N=4e4+5;
struct Edge
{
	int next,to,dis;
	Edge() {}
	Edge(int n,int t,int d):next(n),to(t),dis(d) {}
} edge[N<<1];
int head[N],num_edge;
inline void add_edge(int from,int to,int dis)
{
	edge[++num_edge]=Edge(head[from],to,dis);
	head[from]=num_edge;
}
int size[N],maxn[N],sum,root;
bool vis[N];
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
	if(maxn[root]>maxn[u])
		root=u;
}
int dis[N];
vector<int>deep;
inline void getdis(int u,int fa)
{
	deep.push_back(dis[u]);
	for(re int i=head[u]; i; i=edge[i].next)
	{
		int &v=edge[i].to,&w=edge[i].dis;
		if(vis[v]||v==fa)
			continue;
		dis[v]=dis[u]+w;
		getdis(v,u);
	}
}
int n,k,ans;
inline int calc(int u,int w)
{
	dis[u]=w;
	deep.clear();
	getdis(u,0);
	stable_sort(deep.begin(),deep.end());
	int res=0,l=0,r=(int)deep.size()-1;
	while(l<r)
	{
		if(deep[l]+deep[r]<=k)
			res+=r-l++;
		else
			--r;
	}
	return res;
}
inline void solve(int u)
{
	ans+=calc(u,0);
	vis[u]=true;
	for(re int i=head[u]; i; i=edge[i].next)
	{
		int &v=edge[i].to,&w=edge[i].dis;
		if(vis[v])
			continue;
		ans-=calc(v,w);
		maxn[root=0]=sum=size[v];
		getroot(v,u);
		getroot(root,u);
		solve(root);
	}
}
int main()
{
	read(n);
	for(re int i=1; i<n; ++i)
	{
		int u,v,w;
		read(u),read(v),read(w);
		add_edge(u,v,w);
		add_edge(v,u,w);
	}
	read(k);
	maxn[ans=root=0]=sum=n;
	getroot(1,0);
	getroot(root,0);
	solve(root);
	printf("%d\n",ans);
	return 0;
}
