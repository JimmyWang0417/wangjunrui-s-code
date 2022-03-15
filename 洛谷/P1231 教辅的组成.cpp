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
const int N=1e6+5;
struct Edge
{
	int next,to,cap,flow;
} edge[N];
int head[N],num_edge=1;
inline void add_edge(int from,int to,int cap,bool flag=true)
{
	edge[++num_edge].next=head[from];
	edge[num_edge].to=to;
	edge[num_edge].flow=0;
	edge[num_edge].cap=cap;
	head[from]=num_edge;
	if(flag)
		add_edge(to,from,0,false);
}
int dis[N],cur[N];
int n1,n2,n3,m1,m2;
#define s 0
#define t (n1+n1+n2+n3+1)
inline bool bfs()
{
	for(int i=s; i<=t; ++i)
	{
		cur[i]=head[i];
		dis[i]=0;
	}
	dis[s]=1;
	queue<int>q;
	q.push(s);
	while(!q.empty())
	{
		int u=q.front();
		q.pop();
		for(int i=head[u]; i; i=edge[i].next)
		{
			int &v=edge[i].to;
			if(!dis[v]&&edge[i].cap>edge[i].flow)
			{
				dis[v]=dis[u]+1;
				if(v==t)
					return true;
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
	int res=0;
	for(int &i=cur[u]; i; i=edge[i].next)
	{
		int &v=edge[i].to;
		if(dis[v]==dis[u]+1&&edge[i].cap>edge[i].flow)
		{
			int f=dinic(v,min(flow,edge[i].cap-edge[i].flow));
			if(f)
			{
				res+=f;
				edge[i].flow+=f;
				edge[i^1].flow-=f;
				flow-=f;
			}
		}
	}
	return res;
}
signed main()
{
	read(n1,n2,n3,m1);
	for(int i=1; i<=n1; ++i)
		add_edge(i,i+n1,1);
	for(int i=1; i<=n2; ++i)
		add_edge(s,i+n1+n1,1);
	for(int i=1; i<=n3; ++i)
		add_edge(i+n1+n1+n2,t,1);
	for(int i=1; i<=m1; ++i)
	{
		int x,y;
		read(x,y);
		add_edge(y+n1+n1,x,1);
	}
	read(m2);
	for(int i=1; i<=m2; ++i)
	{
		int x,y;
		read(x,y);
		add_edge(x+n1,y+n1+n1+n2,1);
	}
	int ans=0;
	while(bfs())
		ans+=dinic(s,0x7fffffff);
	printf("%d\n",ans);
	return 0;
}


