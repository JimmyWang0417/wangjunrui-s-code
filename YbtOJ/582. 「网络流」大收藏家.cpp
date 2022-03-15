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
const int N=3e4+5;
struct Edge
{
	int next,to,flow,cap;
} edge[N*5];
int head[N],num_edge=1;
inline void add_edge(int from,int to,int cap,bool flag=true)
{
	edge[++num_edge].next=head[from];
	edge[num_edge].to=to;
	edge[num_edge].cap=cap;
	edge[num_edge].flow=0;
	head[from]=num_edge;
	if(flag){
		add_edge(to,from,0,false);
//		printf("%d %d %d\n",from,to,cap);
	}
}
int s,t;
int cnt;
int dis[N];
int cur[N];
inline bool bfs()
{
	memcpy(cur,head,sizeof(cur));
	clear(dis,0,cnt,0);
	dis[s]=1;
	queue<int>q;
	q.push(s);
	while(!q.empty())
	{
		int u=q.front();
		if(u==t)
			return true;
		q.pop();
		for(int i=head[u]; i; i=edge[i].next)
		{
			int &v=edge[i].to;
			if(!dis[v]&&edge[i].cap>edge[i].flow)
			{
				dis[v]=dis[u]+1;
				q.push(v);
			}
		}
	}
	return false;
}
inline int dinic(int u,int flow)
{
	if(u==t||!flow)
		return flow;
	int res=0;
	for(int &i=cur[u]; i; i=edge[i].next)
	{
		int &v=edge[i].to;
		if(dis[v]==dis[u]+1&&edge[i].cap>edge[i].flow)
		{
			int f=dinic(v,min(edge[i].cap-edge[i].flow,flow));
			if(f)
			{
				res+=f;
				edge[i].flow+=f;
				edge[i^1].flow-=f;
				flow-=f;
				if(!flow)
					return res;
			}
		}

	}
	return res;
}
int n,m;
int a[N];
int las[N];
inline void work()
{
	read(n,m);
	for(int i=1; i<=n; ++i)
	{
		read(a[i]);
		add_edge(s,i,1);
		add_edge(i,las[i]=i+n,a[i]);
	}
	cnt=2*n;
	for(int i=1; i<=m; ++i)
	{
		int x,y;
		read(x,y);
		add_edge(las[x],las[y],1);
		add_edge(las[y],las[x],1);
		++cnt;
		add_edge(las[x],cnt,a[x]);
		las[x]=cnt;
		++cnt;
		add_edge(las[y],cnt,a[y]);
		las[y]=cnt;
	}
	int ans=0;
	t=las[1];
	while(bfs())
		ans+=dinic(s,0x3f3f3f3f);
	printf("%d\n",ans);
	clear(head,0,cnt,0);
	num_edge=1;
}
signed main()
{
	freopen("collection.in","r",stdin),freopen("collection.out","w",stdout);
	int T;
	read(T);
	while(T--)
		work();
	return 0;
}

