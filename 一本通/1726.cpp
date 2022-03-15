#include<cstdio>
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
const int N=2e6+10;
int head[N],dis[N],num_edge,n,m,k,T,cnt[N];
bool exist[N];
struct Edge
{
	int next,to,dis;
} edge[N];
inline void add_edge(co int from,co int to,co int dis)
{
	edge[++num_edge].next=head[from];
	edge[num_edge].dis=dis;
	edge[num_edge].to=to;
	head[from]=num_edge;
}
inline void spfa()
{
	queue<int>q;
	for(re int i=1; i<=n+m; i++)
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
				cnt[v]=cnt[u]+1;
				dis[v]=dis[u]+w;
				if(cnt[v]>num_edge)
				{
					puts("No");
					return;
				}
				if(!exist[v])
				{
					exist[v]=true;
					q.push(v);
				}
			}
		}
	}
	puts("Yes");
	return;
}
int main()
{
	read(T);
	while(T--)
	{
		read(n);
		read(m);
		read(k);
		for(re int i=1,x,y,c; i<=k; i++)
		{
			read(x);
			read(y);
			read(c);
			add_edge(y+n,x,c);
			add_edge(x,y+n,-c);
		}
		spfa();
		fill(dis+1,dis+1+n+m,0);
		fill(head+1,head+1+n+m,0);
		fill(cnt+1,cnt+1+n+m,0);
		num_edge=0;
	}
	return 0;
}
