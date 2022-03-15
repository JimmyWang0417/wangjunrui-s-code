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
const int N=20*20*2+5;
const int INF=0x3f3f3f3f;
struct Edge
{
	int next,to;
	int cap,flow;
	int cost;
} edge[N*10];
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
int n,m;
int dis[N];
int cur[N];
bitset<N>exist;
#define s 0
#define t (n*m*2+1)
inline bool spfa()
{
	memcpy(cur,head,sizeof(head));
	memset(dis,INF,sizeof(dis));
	exist.reset();
	dis[s]=0;
	queue<int>q;
	q.push(s);
	while(!q.empty())
	{
		int u=q.front();
		q.pop();
		exist[u]=false;
		for(int i=head[u]; i; i=edge[i].next)
		{
			int &v=edge[i].to;
			if(dis[v]>dis[u]+edge[i].cost&&edge[i].cap>edge[i].flow)
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
	if(u==t||!flow)
		return flow;
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
char bg[25][25];
char ed[25][25];
char cnt[25][25];
int cnt1,cnt2;
#define calc(x,y) ((x-1)*m+y)
signed main()
{
	read(n,m);
	for(int i=1; i<=n; ++i)
	{
		scanf("%s",bg[i]+1);
		for(int j=1; j<=m; ++j)
			cnt1+=(bg[i][j]=='1');
	}
	for(int i=1; i<=n; ++i)
	{
		scanf("%s",ed[i]+1);
		for(int j=1; j<=m; ++j)
			cnt2+=(ed[i][j]=='1');
	}
	if(cnt1!=cnt2)
	{
		puts("-1\n");
		return 0;
	}
	for(int i=1; i<=n; ++i)
		scanf("%s",cnt[i]+1);
	int needflow;
	for(int i=1; i<=n; ++i)
		for(int j=1; j<=m; ++j)
		{
			if(bg[i][j]=='1'&&ed[i][j]=='0')
				add_edge(s,calc(i,j),1,0);
			else if(bg[i][j]=='0'&&ed[i][j]=='1')
			{
				add_edge(calc(i,j)+n*m,t,1,0);
				++needflow;
			}
			int sum=cnt[i][j]-'0';
			add_edge(calc(i,j),calc(i,j)+n*m,(sum+(bg[i][j]!=ed[i][j]))/2,0);
			for(int a=i-1; a<=i+1; ++a)
				for(int b=j-1; b<=j+1; ++b)
				{
					if(a==i&&b==j)
						continue;
					if(a<1||a>n||b<1||b>m)
						continue;
					add_edge(calc(i,j)+n*m,calc(a,b),INF,1);
				}
		}
	int ans=0;
	while(spfa())
	{
		int flow=dinic(s,INF);
		needflow-=flow;
//		printf("%d %d\n",dis[t],flow);
		ans+=dis[t]*flow;
	}
	if(!needflow)
		puts("-1\n");
	else
		printf("%d\n",ans);
	return 0;
}


