#include<cstdio>
#include<cstring>
#include<algorithm>
#define re register
#define ll long long
#define ull unsigned ll
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
}
const int N=1e4+5;
int head[N],num_edge;
struct Edge
{
	int next,to,dis;
} edge[N<<1];
inline void add_edge(int from,int to,int dis)
{
	edge[++num_edge].next=head[from];
	edge[num_edge].to=to;
	edge[num_edge].dis=dis;
	head[from]=num_edge;
}
#define size sze
int n,k,dis[N],f[N],size[N],root,deep[N],sum;
bool vis[N];
inline void getroot(int u,int fa)
{
	size[u]=1;
	f[u]=0;
	for(re int i=head[u]; i; i=edge[i].next)
	{
		int &v=edge[i].to;
		if(vis[v]||fa==v)
			continue;
		getroot(v,u);
		size[u]+=size[v];
		f[u]=max(f[u],size[v]);
	}
	f[u]=max(f[u],sum-size[u]);
	if(f[u]<f[root])
		root=u;
}
inline void getdeep(int u,int fa)
{
	deep[++deep[0]]=dis[u];
	for(re int i=head[u]; i; i=edge[i].next)
	{
		int &v=edge[i].to,&w=edge[i].dis;
		if(vis[v]||fa==v)
			continue;
		dis[v]=dis[u]+w;
		getdeep(v,u);
	}
}
inline ll calc(int u,int val)
{
	dis[u]=val;
	deep[0]=0;
	getdeep(u,0);
//	for(re int i=1; i<=deep[0]; ++i)
//		printf("%d ",deep[i]);
//	putchar('\n');
	stable_sort(deep+1,deep+1+deep[0]);
	ll res=0;
	int l=1,r=deep[0];
	while(l<r)
	{
		if(deep[l]+deep[r]<=k)
		{
			res+=r-l;
			++l;
		}
		else
			--r;
	}
	return res;
}
ll ans;
inline void solve(int u)
{
//	printf("%d\n",u);
	ans+=calc(u,0);
	vis[u]=true;
	for(re int i=head[u]; i; i=edge[i].next)
	{
		int &v=edge[i].to,&w=edge[i].dis;
		if(vis[v])
			continue;
		ans-=calc(v,w);
		sum=size[v];
		root=0;
		getroot(v,0);
		solve(root);
	}
}
inline void clear_all()
{
	root=num_edge=0;
	ans=0ll;
	memset(head,0,sizeof(int)*(n+1));
	memset(vis,false,sizeof(bool)*(n+1));
//	printf("%d\n",sizeof(bool));
}
int main()
{
	while(read(n),read(k),n&&k)
	{
		for(re int i=1; i<n; ++i)
		{
			int u,v,w;
			read(u);
			read(v);
			read(w);
			add_edge(u,v,w);
			add_edge(v,u,w);
		}
		sum=n;
		root=0;
		f[0]=0x7fffffff;
		getroot(1,0);
//	for(re int i=1; i<=n; ++i)
//		printf("%d ",f[i]);
		solve(root);
		printf("%lld\n",ans);
		clear_all();
	}
	return 0;
}
#undef size
