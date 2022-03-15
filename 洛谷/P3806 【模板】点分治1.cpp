#include<cstdio>
#include<queue>
#include<algorithm>
#define re register
using namespace std;

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
	return;
}

const int N=1e4+5,M=1e2+5,K=1e7+5;
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


struct problem
{
	int k;
	bool ans;
} q[M];
#define size sze

int maxk;

bool vis[N];
int size[N],dis[N],maxn[N],root,sum;
inline void getroot(int u,int fa)
{
	size[u]=1;
	maxn[u]=0;
	for(re int i=head[u]; i; i=edge[i].next)
	{
		int &v=edge[i].to;
		if(v==fa||vis[v])
			continue;
		getroot(v,u);
		size[u]+=size[v];
		if(size[v]>maxn[u])
			maxn[u]=size[v];
	}
	maxn[u]=max(maxn[u],sum-size[u]);
	if(maxn[u]<maxn[root])
		root=u;
	return;
}
int tmp[N],cnt;
inline void getdis(int u,int fa)
{
	if(dis[u]>maxk)
		return;
	tmp[++cnt]=dis[u];
	for(re int i=head[u]; i; i=edge[i].next)
	{
		int &v=edge[i].to,&w=edge[i].dis;
		if(v==fa||vis[v])
			continue;
		dis[v]=dis[u]+w;
		getdis(v,u);
	}
}
int n,m;
bool judge[K];
queue<int>que;
inline void calc(int u)
{
	for(re int i=head[u]; i; i=edge[i].next)
	{
		int &v=edge[i].to,&w=edge[i].dis;
		if(vis[v])
			continue;
		dis[v]=w;
		cnt=0;
		getdis(v,u);
		for(re int j=1; j<=cnt; ++j)
			for(re int k=1; k<=m; ++k)
				if(q[k].k>=tmp[j])
					q[k].ans|=judge[q[k].k-tmp[j]];
		for(re int j=1; j<=cnt; ++j)
		{
			judge[tmp[j]]=true;
			que.push(tmp[j]);
		}
	}
	while(!que.empty())
	{
		judge[que.front()]=false;
		que.pop();
	}
}
inline void solve(int u)
{
	vis[u]=judge[0]=true;
	calc(u);
	for(re int i=head[u]; i; i=edge[i].next)
	{
		int &v=edge[i].to;
		if(vis[v])
			continue;
		maxn[root=0]=sum=size[v];
		getroot(v,u);
		getroot(root,u);
		solve(root);
	}
}

int main()
{
	read(n),read(m);
	for(re int i=1; i<n; ++i)
	{
		int u,v,w;
		read(u),read(v),read(w);
		add_edge(u,v,w);
		add_edge(v,u,w);
	}
	for(re int i=1; i<=m; ++i)
	{
		read(q[i].k);
		maxk=max(maxk,q[i].k);
	}
	maxn[root=0]=sum=n;
	getroot(1,0);
	getroot(root,0);
	solve(root);
	for(re int i=1; i<=m; ++i)
		if(q[i].ans)
			printf("AYE\n");
		else
			printf("NAY\n");
	return 0;
}
#undef size
