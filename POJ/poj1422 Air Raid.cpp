#include <cstdio>
#include <bitset>
#include <cstring>
#define lowbit(x) ((x)&(-(x)))
#define re register
#define ll long long
#define ull unsigned long long
#define rep(i,a,b) for(re int i=a;i<=b;++i)
#define per(i,a,b) for(re int i=a;i>=b;--i)
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
template<typename T>
inline void clear(T*a,int l,int r,int val)
{
	memset(&a[l],val,sizeof(T)*(r-l+1));
}
const int N=1e6+5;
int belong[N];
std::bitset<N>vis;
struct Edge
{
	int next,to;
} edge[N];
int head[N],num_edge;
inline void add_edge(int from,int to)
{
	edge[++num_edge].next=head[from];
	edge[num_edge].to=to;
	head[from]=num_edge;
}
inline bool find(int u)
{
	for(re int i=head[u]; i; i=edge[i].next)
	{
		int &v=edge[i].to;
		if(vis[v])
			continue;
		vis[v]=true;
		if(!belong[v]||find(belong[v]))
		{
			belong[v]=u;
			return true;
		}
	}
	return false;
}
inline void work()
{
	int n,m;
	read(n),read(m);
	for(re int i=1; i<=m; ++i)
	{
		int u,v;
		read(u),read(v);
		add_edge(u,v+n);
	}
	int ans=0;
	for(re int i=1; i<=n; ++i)
	{
		vis.reset();
		if(find(i))
			++ans;
	}
	printf("%d\n",n-ans);
	clear(head,1,n,num_edge=0);
	clear(belong,1,2*n,0);
}
signed main()
{
	int T;
	read(T);
	while(T--)
		work();
	return 0;
}


