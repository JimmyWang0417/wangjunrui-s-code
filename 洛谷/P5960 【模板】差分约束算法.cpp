#include <cstdio>
#include <cstring>
#include <queue>
#define re register
using namespace std;
template <typename T>
inline void read(T &x)
{
	char s=(char)getchar();
	bool flag=false;
	x=0;
	while(s<'0'||s>'9')
	{
		if(s=='-')
			flag=true;
		s=(char)getchar();
	}
	while(s>='0'&&s<='9')
	{
		x=(x<<1)+(x<<3)+(s^'0');
		s=(char)getchar();
	}
	if(flag)
		x=~x+1;
	return;
}
const int N=5e3+5;
struct Edge
{
	int next,to,dis;
} edge[N<<1];
int head[N],num_edge;
inline void add_edge(int from,int to,int dis)
{
	edge[++num_edge].next=head[from];
	edge[num_edge].to=to;
	edge[num_edge].dis=dis;
	head[from]=num_edge;
}
int n,m;
int cnt[N],dis[N];
bool exist[N];
inline void SPFA()
{
	for(re int i=1; i<=n; ++i)
		add_edge(0,i,0);
	memset(dis+1,0x3f3f3f3f,sizeof(int)*n);
	static queue<int>q;
	dis[0]=0;
	q.push(0);
	while(!q.empty())
	{
		int u=q.front();
		q.pop();
//		printf("%d\n",u);
		exist[u]=false;
		for(re int i=head[u]; i; i=edge[i].next)
		{
			int &v=edge[i].to,&w=edge[i].dis;
//			printf("%d %d %d\n",u,v,w);
			if(dis[v]>dis[u]+w)
			{
				dis[v]=dis[u]+w;
				cnt[v]=cnt[u]+1;
				if(cnt[v]>m)
				{
					printf("NO\n");
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
	for(re int i=1; i<=n; ++i)
		printf("%d ",dis[i]);
	putchar('\n');
	return;
}
int main()
{
	read(n),read(m);
	for(re int i=0; i<m; ++i)
	{
		int u,v,w;
		read(u),read(v),read(w);
		add_edge(v,u,w);
	}
	SPFA();
	return 0;
}
