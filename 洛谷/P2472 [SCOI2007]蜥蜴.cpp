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
inline void clear(T*a,int l,int r,int val)
{
	memset(&a[l],val,sizeof(T)*(r-l+1));
}
const int N=20*20*2+5,M=N*N*2,INF=0x7fffffff;
struct Edge
{
	int next,to,cap,flow;
} edge[M];
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
int r,c,d;
int s,t;
char str[N];
int mp[N][N];
int dis[N],cur[N];
inline bool bfs()
{
	memset(dis,0,sizeof(dis));
	std::queue<int>q;
	dis[s]=1;
	q.push(s);
	for(re int i=0; i<=2*r*c+1; ++i)
		cur[i]=head[i];
	while(!q.empty())
	{
		int u=q.front();
		q.pop();
		if(u==t)
			return true;
		for(re int i=head[u]; i; i=edge[i].next)
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
			int f=dinic(v,std::min(flow,edge[i].cap-edge[i].flow));
			if(f)
			{
				res+=f;
				edge[i].flow+=f;
				edge[i^1].flow-=f;
				flow-=f;
			}
			if(!flow)
				return res;
		}
	}
	return res;
}
inline bool check(int x,int y)
{
	return (x>=1&&x<=r&&y>=1&&y<=c);
}
inline bool checkdis(int x1,int y1,int x2,int y2)
{
	return ((x2-x1)*(x2-x1)+(y2-y1)*(y2-y1))<=d*d;
}
inline int calc(int x,int y)
{
	return (x-1)*c+y;
}
signed main()
{
	read(r,c,d);
	s=0,t=2*r*c+1;
	for(re int i=1; i<=r; ++i)
	{
		scanf("%s",str+1);
		for(re int j=1; j<=c; ++j)
		{
			mp[i][j]=str[j]-'0';
			if(mp[i][j])
				add_edge(calc(i,j),calc(i,j)+r*c,mp[i][j]);
		}
	}
	int sum=0;
	for(re int i=1; i<=r; ++i)
	{
		scanf("%s",str+1);
		for(re int j=1; j<=c; ++j)
			if(str[j]=='L')
			{
				++sum;
				add_edge(0,calc(i,j),1);
			}
	}
	for(re int i=1; i<=r; ++i)
		for(re int j=1; j<=c; ++j)
			if(mp[i][j])
				for(re int x=1; x<=r; ++x)
					for(re int y=1; y<=c; ++y)
						if(!(i==x&&j==y)&&mp[x][y]&&checkdis(i,j,x,y))
							add_edge(calc(i,j)+r*c,calc(x,y),INF);
	for(re int i=1; i<=r; ++i)
		for(re int j=1; j<=c; ++j)
		{
			if(i-d<1||i+d>r||j-d<1||j+d>c)
				add_edge(calc(i,j)+r*c,t,INF);
		}
	int ans=0;
	while(bfs())
		ans+=dinic(0,INF);
	printf("%d\n",sum-ans);
	return 0;
}


