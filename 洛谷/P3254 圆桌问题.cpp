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
struct Edge
{
	int next,to,cap,flow;
} edge[N];
int head[N],num_edge=1;
inline void add_edge(int from,int to,int cap,bool flag=true)
{
	edge[++num_edge].next=head[from];
	edge[num_edge].to=to;
	edge[num_edge].cap=cap;
	edge[num_edge].flow=0;
	head[from]=num_edge;
	if(flag)
		add_edge(to,from,0,false);
}
int n,m;
#define s 0
#define t (n+m+1)
int cur[N];
int dis[N];
bitset<N>exist;
inline bool bfs()
{
	memset(dis,0,sizeof(dis));
	memcpy(cur,head,sizeof(head));
	exist.reset();

	queue<int>q;
	dis[s]=1;
	q.push(s);
	while(!q.empty())
	{
		int u=q.front();
		q.pop();
		if(u==t)
			return true;
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
	if(u==t)
		return flow;
	exist[u]=true;
	int res=0;
	for(int &i=cur[u]; i; i=edge[i].next)
	{
		int &v=edge[i].to;
		if(!exist[v]&&dis[v]==dis[u]+1&&edge[i].cap>edge[i].flow)
		{
			int f=dinic(v,min(flow,edge[i].cap-edge[i].flow));
			if(f)
			{
				edge[i].flow+=f;
				edge[i^1].flow-=f;

				res+=f;
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
	int sum=0;
	read(m,n);
	for(int i=1; i<=m; ++i)
	{
		int val;
		read(val);
		sum+=val;
		add_edge(s,i,val);
	}
	for(int i=1; i<=m; ++i)
		for(int j=1; j<=n; ++j)
			add_edge(i,j+m,1);
	for(int i=1; i<=n; ++i)
	{
		int val;
		read(val);
		add_edge(i+m,t,val);
	}

	int ans=0;
	while(bfs())
		ans+=dinic(s,0x7fffffff);
//	printf("sum=%d ans=%d\n",sum,ans);
	if(sum!=ans)
	{
		printf("0\n");
		return 0;
	}
	printf("1\n");
	for(int i=1; i<=m; ++i)
	{
		for(int j=1; j<=n; ++j)
		{
#define e (((i-1)*n+j+m)*2)
			if(edge[e].flow==1)
				printf("%d ",j);
		}
		putchar('\n');
	}
	return 0;
}


