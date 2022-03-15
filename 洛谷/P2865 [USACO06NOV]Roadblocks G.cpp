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
const int N=2e5+5;
struct Edge
{
	int next,to,dis;
} edge[N];
int head[N],num_edge;
inline void add_edge(int from,int to,int dis)
{
	edge[++num_edge].next=head[from];
	edge[num_edge].to=to;
	edge[num_edge].dis=dis;
	head[from]=num_edge;
}
int n,m;
int dis1[N],dis2[N];
bool vis[N];
inline void dijkstra1(int s)
{
	priority_queue<pair<int,int>,vector<pair<int,int> >,greater<pair<int,int> > >q;
	memset(dis1,0x3f,sizeof(dis1));
	q.push(make_pair(dis1[s]=0,s));
	while(!q.empty())
	{
		int u=q.top().second;
		q.pop();
		if(vis[u])
			continue;
		for(int i=head[u]; i; i=edge[i].next)
		{
			int &v=edge[i].to;
			if(dis1[v]>dis1[u]+edge[i].dis)
				q.push(make_pair(dis1[v]=dis1[u]+edge[i].dis,v));
		}
	}
}
inline void dijkstra2(int s)
{
	priority_queue<pair<int,int>,vector<pair<int,int> >,greater<pair<int,int> > >q;
	memset(dis2,0x3f,sizeof(dis2));
	q.push(make_pair(dis2[s]=0,s));
	while(!q.empty())
	{
		int u=q.top().second;
		q.pop();
		if(vis[u])
			continue;
		for(int i=head[u]; i; i=edge[i].next)
		{
			int &v=edge[i].to;
			if(dis2[v]>dis2[u]+edge[i].dis)
				q.push(make_pair(dis2[v]=dis2[u]+edge[i].dis,v));
		}
	}
}
signed main()
{
	read(n,m);
	for(int i=1; i<=m; ++i)
	{
		int u,v,w;
		read(u,v,w);
		add_edge(u,v,w);
		add_edge(v,u,w);
	}
	dijkstra1(1);
	dijkstra2(n);
	int ans=0x7fffffff;
//	for(int i=1; i<=n; ++i)
//		printf("%d ",dis1[i]);
//	putchar('\n');
//	for(int i=1; i<=n; ++i)
//		printf("%d ",dis2[i]);
//	putchar('\n');
	for(int u=1; u<=n; ++u)
	{
		for(int i=head[u]; i; i=edge[i].next)
		{
			int &v=edge[i].to;
			if(dis1[u]+edge[i].dis+dis2[v]>dis1[n])
				ans=min(ans,dis1[u]+edge[i].dis+dis2[v]);
		}
	}
	printf("%d\n",ans);
	return 0;
}


