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
const int N=105,INF=0x7fffffff;
int m,n;
struct Edge
{
	int next,from,to,cap,flow;
	Edge(int _next=0,int _from=0,int _to=0,int _cap=0,int _flow=0):next(_next),from(_from),to(_to),cap(_cap),flow(_flow) {}
} edge[N*N];
int head[N],num_edge=1;
inline void add_edge(int from,int to,int cap,bool flag=true)
{
	edge[++num_edge]=Edge(head[from],from,to,cap);
	head[from]=num_edge;
	if(flag)
		add_edge(to,from,0,false);
}
#define s 0
#define t (m+n+1)
int dis[N],cur[N];
inline bool bfs()
{
	std::queue<int>q;
	q.push(s);
	memset(dis,0,sizeof(dis));
	dis[s]=1;
	for(re int i=s; i<=t; ++i)
		cur[i]=head[i];
	while(!q.empty())
	{
		int u=q.front();
		if(u==t)
			return true;
		q.pop();
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
signed main()
{
	read(m,n);
	ll ans=0;
	for(re int i=1; i<=m; ++i)
	{
		int val;
		read(val);
		add_edge(s,i,val);
		ans+=val;
		char tools[10000];
		memset(tools,0,sizeof tools);
		scanf("%[^\n]",tools);
//		printf("%s\n",tools);
//		printf("%s\n",tools);
		int ulen=0,tool;
		while (sscanf(tools+ulen,"%d",&tool)==1)//???????scanf???????????????????????????
		{
			//tool???????????????????????
			//????§µ???????????????????§Υ??θε?????????????
			add_edge(i,tool+m,INF);
//			printf(" %d %d\n",i,tool); 
			if (tool==0)
				ulen++;
			else
			{
				while (tool)
				{
					tool/=10;
					ulen++;
				}
			}
			ulen++;
		}
	}
	for(re int i=1; i<=n; ++i)
	{
		int val;
		read(val);
		add_edge(i+m,t,val);
	}
	while(bfs())
		ans-=dinic(s,INF);
//	for(re int i=1; i<=n+m; ++i)
//		printf("%d ",dis[i]);
//	putchar('\n');
	for(re int i=1; i<=m; ++i)
		if(dis[i])
			printf("%d ",i);
	putchar('\n');
	for(re int i=1; i<=n; ++i)
		if(dis[i+m])
			printf("%d ",i);
	printf("\n%lld\n",ans);
	return 0;
}
