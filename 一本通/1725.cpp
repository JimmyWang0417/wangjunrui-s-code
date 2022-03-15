#include<cstdio>
#include<algorithm>
#include<queue>
#define re register
#define co const
using namespace std;
template<typename T>
inline void read(T&x)
{
	x=0;
	char s=getchar();
	bool f=false;
	while(!(s>='0'&&s<='9'))
	{
		if(s=='-')
			f=true;
		s=getchar();
	}
	while(s>='0'&&s<='9')
	{
		x=(x<<1)+(x<<3)+s-'0';
		s=getchar();
	}
	if(f)
		x=(~x)+1;
}
const int N=1000010,INF=0x3f3f3f3f;
struct Edge
{
	int next,to,dis;
} edge[N];
int head[N],n,m,num_edge,T,dis[N],cnt[N];
bool exist[N];
inline void add_edge(co int from,co int to,co int dis)
{
	edge[++num_edge].next=head[from];
	edge[num_edge].to=to;
	edge[num_edge].dis=dis;
	head[from]=num_edge;
}
inline bool spfa()
{
	queue<int>q;
	for(re int i=0; i<=n; i++)
	{
		q.push(i);
		exist[i]=true;
	}
	int u;
	while(!q.empty())
	{
		u=q.front();
		q.pop();
		exist[u]=false;
		for(re int i=head[u]; i; i=edge[i].next)
		{
			int &v=edge[i].to,&w=edge[i].dis;
			if(dis[v]>dis[u]+w)
			{
				dis[v]=dis[u]+w;
				cnt[v]=cnt[u]+1;
				if(cnt[v]>num_edge)
					return true;
				if(!exist[v])
				{
					exist[v]=true;
					q.push(v);
				}
			}
		}
	}
	return false;
}
int main()
{
	read(T);
	while(T--)
	{
		read(n);
		read(m);
		for(re int i=1,u,v,w; i<=m; i++)
		{
			read(u);
			read(v);
			read(w);
			add_edge(u-1,v,w);
			add_edge(v,u-1,-w);
		}
		if(spfa())
			puts("false");
		else
			puts("true");
		fill(dis,dis+1+n,0);
		fill(cnt,cnt+1+n,0);
		fill(head,head+1+n,0);
		num_edge=0;
	}
	return 0;
}
