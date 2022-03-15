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
const int N=2e6+5;
struct Edge
{
	int next,to,dis;
} edge[N*3];
int head[N],num_edge;
inline void add_edge(int from,int to,int dis,bool flag=true)
{
	edge[++num_edge].next=head[from];
	edge[num_edge].to=to;
	edge[num_edge].dis=dis;
	head[from]=num_edge;
	if(flag)
		add_edge(to,from,dis,false);
}
int n,m;
int S,T;
inline int calc(int i,int j)
{
	return (i-1)*m+j;
}
int dis[N];
bool vis[N];
inline void dijkstra()
{
	memset(dis,0x3f,sizeof(dis));
	priority_queue<pair<int,int>,vector<pair<int,int> >,greater<pair<int,int> > >q;
	q.push(make_pair(dis[S]=0,S));
	while(!q.empty())
	{
		int u=q.top().second;
		q.pop();
		if(vis[u])
			continue;
		for(int i=head[u]; i; i=edge[i].next)
		{
			int &v=edge[i].to;
			if(dis[v]>dis[u]+edge[i].dis)
				q.push(make_pair(dis[v]=dis[u]+edge[i].dis,v));
		}
	}
}
signed main()
{
	read(n,m);
	S=0,T=n*m*2;
	for(int i=1; i<m; ++i)
	{
		int val;
		read(val);
		add_edge(S,calc(1,i),val);
	}
	for(int i=2; i<n; ++i)
	{
		for(int j=1; j<m; ++j)
		{
			int val;
			read(val);
			add_edge(calc(i-1,j)+n*m,calc(i,j),val);
		}
	}
	for(int i=1; i<m; ++i)
	{
		int val;
		read(val);
		add_edge(calc(n-1,i)+n*m,T,val);
	}

	for(int i=1; i<n; ++i)
	{
		int val;
		read(val);
		add_edge(calc(i,1)+n*m,T,val);
		for(int j=2; j<m; ++j)
		{
			read(val);
			add_edge(calc(i,j-1),calc(i,j)+n*m,val);
		}
		read(val);
		add_edge(S,calc(i,m-1),val);
	}

	for(int i=1; i<n; ++i)
	{
		for(int j=1; j<m; ++j)
		{
			int val;
			read(val);
			add_edge(calc(i,j),calc(i,j)+n*m,val);
		}
	}
	dijkstra();
	printf("%d\n",dis[T]);
	return 0;
}


