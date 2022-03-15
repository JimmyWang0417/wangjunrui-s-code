#include<cstdio>
#include<cstring>
#define re register
#define max(x,y) ((x)>(y)?(x):(y))
using namespace std;



template<typename T>
inline void read(T&x)
{
	x=0;
	char s=(char)getchar();
	bool flag=false;
	while(!(s>='0'&&s<='9'))
	{
		if(s=='-')
			flag=true;
		s=(char)getchar();
	}
	while(s>='0'&&s<='9')
	{
		x=(x<<1)+(x<<3)+s-'0';
		s=(char)getchar();
	}
	if(flag)
		x=(~x)+1;
}




const int N=2e4+5;
struct Edge
{
	int next,to,dis;
	Edge() {}
	Edge(int x,int y,int z):next(x),to(y),dis(z) {}
};
Edge edge[N<<1];
int head[N],num_edge;
inline void add_edge(int from,int to,int dis)
{
	edge[++num_edge]=Edge(head[from],to,dis);
	head[from]=num_edge;
}




#define size sze
int f[N],size[N],sum,deep[3],dis[N],root,ans;
bool vis[N];
inline void getroot(int u,int fa)
{
	size[u]=1;
	f[u]=0;
	for(re int i=head[u]; i; i=edge[i].next)
	{
		int &v=edge[i].to;
		if(vis[v]||v==fa)
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
	++deep[dis[u]];
	for(re int i=head[u]; i; i=edge[i].next)
	{
		int &v=edge[i].to,&w=edge[i].dis;
		if(vis[v]||v==fa)
			continue;
		dis[v]=(dis[u]+w)%3;
		getdeep(v,u);
	}
}
inline int calc(int u,int val)
{
	memset(deep,0,sizeof(deep));
	dis[u]=val;
	getdeep(u,0);
	return deep[1]*deep[2]*2+deep[0]*deep[0];
}
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
		root=0;
		sum=size[v];
		getroot(v,u);
		solve(root);
	}
}




inline int gcd(int m,int n)
{
	if(n==0)
		return m;
	return gcd(n,m%n);
}
int n;
int main()
{
	read(n);
	for(re int i=1; i<n; ++i)
	{
		int u,v,w;
		read(u),read(v),read(w);
		w%=3;
		add_edge(u,v,w);
		add_edge(v,u,w);
	}
//	for(re int i=1; i<=num_edge; ++i)
//		printf("%d %d %d\n",edge[i].next,edge[i].to,edge[i].dis);
	sum=n;
	f[0]=0x7fffffff;
	getroot(1,0);
	solve(root);
//	printf("%d\n",ans);
	int Gcd=gcd(n*n,ans);
	printf("%d/%d\n",ans/Gcd,n*n/Gcd);
	return 0;
}
