#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <queue>
#include <vector>
#define re register
#define ll long long
#define ull unsigned long long
#define rep(i,a,b) for(re int i=a;i<=b;++i)
#define per(i,a,b) for(re int i=a;i>=b;--i)
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
template<typename T,typename ...T1>
inline void read(T&x,T1&...x1)
{
	read(x);
	read(x1...);
}
const int N=1e5+5,M=5e5+5;
struct Edge
{
	int next,to;
} edge1[M<<1],edge2[M<<1];
int head1[N],head2[N];
int num_edge1,num_edge2;
inline void add_edge1(int from,int to)
{
	edge1[++num_edge1].next=head1[from];
	edge1[num_edge1].to=to;
	head1[from]=num_edge1;
}
inline void add_edge2(int from,int to)
{
	edge2[++num_edge2].next=head2[from];
	edge2[num_edge2].to=to;
	head2[from]=num_edge2;
}
int dis1[N],dis2[N];
bool vis1[N],vis2[N];
int n,m;
int w[N];
inline void dijkstra1()
{
	memset(dis1,0x3f,sizeof(dis1));
	priority_queue<pair<int,int> >q;
	dis1[1]=w[1];
	q.push(make_pair(-dis1[1],1));
	while(!q.empty())
	{
		int u=q.top().second;
//		printf("\n%d :",u);
		q.pop();
		if(vis1[u])
			continue;
		vis1[u]=true;
		for(re int i=head1[u]; i; i=edge1[i].next)
		{
			int &v=edge1[i].to;
//			printf("%d ",v);
			if(dis1[v]>min(dis1[u],w[v]))
			{
				dis1[v]=min(dis1[u],w[v]);
				q.push(make_pair(-dis1[v],v));
			}
		}
	}
}
inline void dijkstra2()
{
	memset(dis2,~0x3f,sizeof(dis2));
	priority_queue<pair<int,int> >q;
	q.push(make_pair(dis2[n]=w[n],n));
	while(!q.empty())
	{
		int u=q.top().second;
//		printf("    %d\n",u);
		q.pop();
		if(vis2[u])
			continue;
		vis2[u]=true;
		for(re int i=head2[u]; i; i=edge2[i].next)
		{
			int &v=edge2[i].to;
			if(dis2[v]<max(dis2[u],w[v]))
			{
				dis2[v]=max(dis2[u],w[v]);
				q.push(make_pair(dis2[v],v));
			}
		}
	}
}
signed main()
{
	read(n,m);
	for(re int i=1; i<=n; ++i)
		read(w[i]);
	for(re int i=1; i<=m; ++i)
	{
		int u,v,z;
		read(u,v,z);
		add_edge1(u,v);
		add_edge2(v,u);
		if(z==2)
		{
			add_edge1(v,u);
			add_edge2(u,v);
		}
	}
	dijkstra1();
	dijkstra2();
//	for(re int i=1; i<=n; ++i)
//		printf("%d %d\n",dis1[i],dis2[i]);
	int ans=0;
	for(re int i=1; i<=n; ++i)
		ans=max(ans,dis2[i]-dis1[i]);
	printf("%d\n",ans);
	return 0;
}
