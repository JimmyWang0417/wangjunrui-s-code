#include<cstdio>
#include<algorithm>
#define re register
#define mod 1000
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
const int N=6e6+10,M=6e6+10;
int size[N],dfn[N],low[N],dfstime,n,m,Q,head[N],num_edge,root[N];
bool cut[N];
long long ans;
struct Edge
{
	int next,to;
} edge[M];
struct node
{
	int u,v;
} a[M>>1];
inline void add_edge(const int &from,const int &to)
{
	edge[num_edge].next=head[from];
	head[from]=num_edge;
	edge[num_edge++].to=to;
}
inline void Tarjan(const int &u,const int &e)
{
	size[u]=1;
	low[u]=dfn[u]=++dfstime;
	for(re int i=head[u]; i!=-1; i=edge[i].next)
	{
		if(e==i)
			continue;
		int &v=edge[i].to;
		//printf("%d\n",v);
		if(!dfn[v])
		{
			root[v]=root[u];
			Tarjan(v,i^1);
			size[u]=(size[u]+size[v]);
			if(low[v]<low[u])
				low[u]=low[v];
			if(low[v]>dfn[u])
				cut[i]=cut[i^1]=true;
		}
		else if(dfn[v]<low[u])
			low[u]=dfn[v];
	}
	return;
}
int main()
{
	read(n);
	read(m);
	read(Q);
	fill(head,head+1+n,-1);
	for(re int i=0; i<m; i++)
	{
		read(a[i].u);
		read(a[i].v);
		add_edge(a[i].u,a[i].v);
		add_edge(a[i].v,a[i].u);
	}
	for(re int i=0; i<n; i++)
		if(!dfn[i])
		{
			root[i]=i;
			Tarjan(i,-1);
			ans+=(size[i]*(n-size[i]));
		}
	/*for(re int i=0;i<n;i++)
	printf("%d ",size[i]);*/
	int x;
	ans>>=1;
	ans%=mod;
	while(Q--)
	{
		read(x);
		if(!cut[x<<1])
		{
			printf("%lld\n",ans);
			continue;
		}
		int s1=min(size[a[x].u],size[a[x].v]);
		int s2=size[root[a[x].u]]-s1;
		printf("%lld\n",(ans+(s1*s2))%mod);
	}
	//printf("%lld\n",ans);
	return 0;
}
