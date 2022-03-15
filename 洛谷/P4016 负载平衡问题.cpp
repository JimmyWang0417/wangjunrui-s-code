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
const int N=1e5+5;
const int INF=0x3f3f3f3f;
int n,a[N];
struct Edge
{
	int next,to,flow,cap,cost;
} edge[N];
int head[N],num_edge=1;
inline void add_edge(int from,int to,int cap,int cost,bool flag=true)
{
	edge[++num_edge].next=head[from];
	edge[num_edge].to=to;
	edge[num_edge].cap=cap;
	edge[num_edge].flow=0;
	edge[num_edge].cost=cost;
	head[from]=num_edge;
	if(flag)
		add_edge(to,from,0,-cost,false);
}
int cur[N];
int dis[N];
bitset<N>exist;
#define s 0
#define t (n+1)
inline bool spfa()
{
	memset(dis,INF,sizeof(dis));
	memcpy(cur,head,sizeof(head));
	exist.reset();

	queue<int>q;
	dis[s]=0;
	q.push(s);
	while(!q.empty())
	{
		int u=q.front();
		q.pop();
		exist[u]=false;
		for(int i=head[u]; i; i=edge[i].next)
		{
			int &v=edge[i].to;
			if(edge[i].cap>edge[i].flow&&dis[v]>dis[u]+edge[i].cost)
			{
				dis[v]=dis[u]+edge[i].cost;
				if(!exist[v])
				{
					exist[v]=true;
					q.push(v);
				}
			}
		}
	}
	return dis[t]<INF/2;
}
inline int dinic(int u,int flow)
{
	if(u==t)
		return flow;
	if(!flow)
		return 0;
	exist[u]=true;
	int res=0;
	for(int &i=cur[u]; i; i=edge[i].next)
	{
		int &v=edge[i].to;
		if(!exist[v]&&dis[v]==dis[u]+edge[i].cost&&edge[i].cap>edge[i].flow)
		{
			int f=dinic(v,min(flow,edge[i].cap-edge[i].flow));
			if(f)
			{
				edge[i].flow+=f;
				edge[i^1].flow-=f;
				flow-=f;
				res+=f;
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
	read(n);
	int sum=0;
	for(int i=1; i<=n; ++i)
	{
		read(a[i]);
		sum+=a[i];
	}
	sum/=n;

	for(int i=1; i<=n; ++i)
	{
		a[i]-=sum;
		if(a[i]>0)
			add_edge(s,i,a[i],0);
		else if(a[i]<0)
			add_edge(i,t,-a[i],0);
		add_edge(i,(i%n+1),INF,1);
		add_edge((i%n+1),i,INF,1);
	}

	int ans=0;
	while(spfa())
		ans+=dis[t]*dinic(s,INF);
	printf("%d\n",ans);
	return 0;
}


