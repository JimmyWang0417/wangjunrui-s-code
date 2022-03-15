#include <bits/stdc++.h>
#define lowbit(x) ((x)&(-(x)))
#define re register
#define ll long long
#define ull unsigned long long
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
const int N=2005;
const int INF=0x3f3f3f3f;
struct Edge
{
	int next,to;
	int cap,flow;
	int cost;
} edge[N];
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
int cur[N],dis[N];
#define s 0
#define t (2*n+1)
bool exist[N];
int n,a[N];
inline bool spfa()
{
	memcpy(cur,head,sizeof(int)*(t-s+1));
	clear(dis,s,t,-INF);
	clear(exist,s,t,0);
	queue<int>q;
	q.push(s);
	dis[s]=0;
	while(!q.empty())
	{
		int u=q.front();
		q.pop();
		exist[u]=false;
		for(int i=head[u]; i; i=edge[i].next)
		{
			int &v=edge[i].to;
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
	return dis[t]>-INF/2;
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
vector<int>ga[N],gb[N];
int ba[N],bb[N];
int rta,rtb;
int ida[N],idb[N];
int cnta,cntb;
int rka[N],rkb[N];
inline void dfs1(int u,int top,int id)
{
	ida[u]=id;
	for(auto v:ga[u])
	{
		if(ida[v])
			continue;
		if(ba[v]==-1)
			dfs1(v,top,id);
		else
		{
			ba[top]-=ba[v];
			++cnta;
			rka[cnta]=v;
			dfs1(v,v,cnta);
		}
	}
}
inline void dfs2(int u,int top,int id)
{
	idb[u]=id;
	for(auto v:gb[u])
	{
		if(idb[v])
			continue;
		if(bb[v]==-1)
			dfs2(v,top,id);
		else
		{
			bb[top]-=bb[v];
			++cntb;
			rkb[cntb]=v;
			dfs2(v,v,cntb);
		}
	}
}
signed main()
{
	freopen("w.in","r",stdin),freopen("w.out","w",stdout);
	read(n,rta,rtb);
	for(int i=1; i<=n; ++i)
	{
		read(a[i]);
		ba[i]=bb[i]=-1;
	}
	for(int i=1; i<n; ++i)
	{
		int x,y;
		read(x,y);
		ga[x].push_back(y);
		ga[y].push_back(x);
	}
	for(int i=1; i<n; ++i)
	{
		int x,y;
		read(x,y);
		gb[x].push_back(y);
		gb[y].push_back(x);
	}
	int q0,q1;
	read(q0);
	for(int i=1; i<=q0; ++i)
	{
		int pos;
		read(pos),read(ba[pos]);
	}
	read(q1);
	for(int i=1; i<=q1; ++i)
	{
		int pos;
		read(pos),read(bb[pos]);
	}
	cnta=cntb=1;
	rka[1]=rta,rkb[1]=rtb;
	dfs1(rta,rta,cnta);
	dfs2(rtb,rtb,cntb);
	for(int i=1; i<=cnta; ++i)
		add_edge(s,i,ba[rka[i]],0);
	for(int i=1; i<=cntb; ++i)
		add_edge(i+cnta,t,bb[rkb[i]],0);
	for(int i=1; i<=n; ++i)
		add_edge(ida[i],idb[i]+cnta,1,a[i]);
	int ans=0;
	while(spfa())
		ans+=dis[t]*dinic(s,INF);
	for(int i=head[s]; i; i=edge[i].next)
	{
		if(edge[i].flow!=edge[i].cap)
		{
			printf("-1\n");
			return 0;
		}
	}
	for(int i=head[t]; i; i=edge[i].next)
	{
		if(edge[i^1].flow!=edge[i^1].cap)
		{
			printf("-1\n");
			return 0;
		}
	}
	printf("%d\n",ans);
	return 0;
}


