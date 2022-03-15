#include <bits/stdc++.h>
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
template<typename T,typename ...T1>
inline void read(T&x,T1&...x1)
{
	read(x);
	read(x1...);
}
template<typename T>
inline void clear(T*array,int l,int r,int val)
{
	memset(&array[l],val,sizeof(T)*(r-l+1));
}
using namespace std;
const int N=1e5+5,M=N;
const int INF=0x3f3f3f3f;
int n,k;
int a[1005][1005];
#define calc(i,j) ((i-1)*n+j)
struct Edge
{
	int next,to,flow,cap,cost;
} edge[M];
int head[N],num_edge=1;
inline void add_edge(int from,int to,int cap,int cost,bool flag=true)
{
	edge[++num_edge].next=head[from];
	edge[num_edge].to=to;
	edge[num_edge].cap=cap;
	edge[num_edge].cost=cost;
	head[from]=num_edge;
	if(flag)
		add_edge(to,from,0,-cost,false);
}
#define s 0
#define t n*n*2+1
int cur[N];
int dis[N];
bool exist[N];
inline bool spfa()
{
	memset(dis,~0x3f3f3f3f,sizeof(dis));
	memset(exist,false,sizeof(exist));
	memcpy(cur,head,sizeof(head));
	std::queue<int>q;
	q.push(s);
	dis[s]=0;
	exist[s]=true;
	while(!q.empty())
	{
		int u=q.front();
		q.pop();
		exist[u]=false;
		for(re int i=head[u]; i; i=edge[i].next)
		{
			int &v=edge[i].to;
			if(edge[i].cap>edge[i].flow&&dis[v]<dis[u]+edge[i].cost)
			{
				dis[v]=dis[u]+edge[i].cost;
				if(!exist[v])
				{
					q.push(v);
					exist[v]=true;
				}
			}
		}
	}
//	for(int i=s; i<=t; ++i)
//		printf("%d ",dis[i]);
//	putchar('\n');
	return dis[t]>~0x3f3f3f3f/2;
}
using std::pair;
using std::make_pair;
ll ans=0;
inline int dinic(int u,int flow)
{
	if(u==t)
	{
		ans+=dis[t]*flow;
		return flow;
	}
	exist[u]=true;
	int res=0;
	for(int &i=cur[u]; i; i=edge[i].next)
	{
		int &v=edge[i].to;
		if(!exist[v]&&dis[v]==dis[u]+edge[i].cost&&edge[i].cap>edge[i].flow)
		{
			int f=dinic(v,std::min(flow,edge[i].cap-edge[i].flow));
			if(f)
			{
				res+=f;
				edge[i].flow+=f;
				edge[i^1].flow-=f;
				flow-=f;
				if(!flow)
				{
					exist[u]=false;
					break;
				}
			}
		}
	}
	return res;
}
signed main()
{
	read(n,k);
	add_edge(s,calc(1,1),k,0);
	for(int i=1; i<=n; ++i)
	{
		for(int j=1; j<=n; ++j)
		{
			int val;
			read(val);
			add_edge(calc(i,j),calc(i,j)+n*n,1,val);
			add_edge(calc(i,j),calc(i,j)+n*n,INF,0);
			if(j<n)
				add_edge(calc(i,j)+n*n,calc(i,j+1),INF,0);
			if(i<n)
				add_edge(calc(i,j)+n*n,calc(i+1,j),INF,0);
		}
	}
	add_edge(n*n*2,t,INF,0);
	while(spfa())
		dinic(s,INF);
	printf("%lld\n",ans);
	return 0;
}


