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
const int N=1e6+5;
const double INF=1e9,eps=1e-7;
struct Edge
{
	int next,to,cap,flow;
	double cost;
} edge[N];
int head[N],num_edge=1;
inline void add_edge(int from,int to,int cap,double cost,bool flag=true)
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
int n;
int cur[N];
double dis[N];
bool exist[N];
#define s 0
#define t (2*n+1)
inline bool spfa()
{
	clear(exist,s,t,false);
	for(re int i=s; i<=t; ++i)
	{
		cur[i]=head[i];
		dis[i]=-INF;
	}
	std::queue<int>q;
	q.push(s);
	dis[s]=0;
	while(!q.empty())
	{
		int u=q.front();
		q.pop();
		exist[u]=false;
		for(re int i=head[u]; i; i=edge[i].next)
		{
			int &v=edge[i].to;
//			printf("%d %d ",dis[v],dis[u]+edge[i].cost);
			if(dis[v]<dis[u]+edge[i].cost&&edge[i].cap>edge[i].flow)
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
//	for(re int i=s; i<=t; ++i)
//		printf("%LF ",dis[i]);
//	putchar('\n');
	return dis[t]>-INF;
}
double ans=0;
inline int dinic(int u,int flow)
{
	if(u==t)
	{
		ans+=(double)dis[t]*flow;
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
					return res;
				}
			}
		}
	}
	return res;
}
int a[1005][1005],b[1005][1005];
inline bool check(double val)
{
	memset(head,0,sizeof(head));
	num_edge=1;
	for(re int i=1; i<=n; ++i)
		for(re int j=1; j<=n; ++j)
		{
			add_edge(i,j+n,1,a[i][j]-val*b[i][j]);
//			printf("%d %d %LF\n",i,j+n,a[i][j]-val*b[i][j]);
		}
	for(re int i=1; i<=n; ++i)
	{
		add_edge(s,i,1,0);
		add_edge(i+n,t,1,0);
//		printf("%d %d\n%d %d\n",s,i,i+n,t);
	}
	ans=0;
	int res=0;
	while(spfa())
		res+=dinic(s,0x7fffffff);
//	printf("%.6LF %d\n",ans,res);
//	putchar('\n');
//	printf("%d ",num_edge);
	return ans>=1e-10;
}
inline double abs(double x)
{
	if(x<0)
		return -x;
	else
		return x;
}
using std::cin;
signed main()
{
	std::ios::sync_with_stdio(false);
	cin>>n;
	for(re int i=1; i<=n; ++i)
		for(re int j=1; j<=n; ++j)
			cin>>a[i][j];
	for(re int i=1; i<=n; ++i)
		for(re int j=1; j<=n; ++j)
			cin>>b[i][j];
	double l=0,r=1e5,answer=0;
	while(r-l>=eps)
	{
		double mid=(l+r)/2.0;
//		printf("%LF %LF %LF ",l,mid,r);
		if(check(mid))
		{
			answer=mid;
			l=mid;
		}
		else
			r=mid;
	}
	printf("%.6lf\n",answer);
	return 0;
}

