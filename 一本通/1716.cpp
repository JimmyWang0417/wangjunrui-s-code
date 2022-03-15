#include<cstdio>
#include<queue>
#include<algorithm>
#include<cstring>
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
co int N=1010,M=20010,INF=0x3f3f3f3f;
int T,dis[N][2],cnt[N][2],num_edge,head[N],n,m,s,t;
bool vis[N][2];
struct Edge
{
	int next,to,dis;
} edge[M];
struct node
{
	int date,u,p;
	inline bool operator < (co node a)const
	{
		return date>a.date;
	}
};
inline void add_edge(co int &from,co int &to,co int &dis)
{
	edge[++num_edge].next=head[from];
	edge[num_edge].to=to;
	edge[num_edge].dis=dis;
	head[from]=num_edge;
	return;
}
int main()
{
	read(T);
	while(T--)
	{
		read(n);
		read(m);
		for(re int i=1,x,y,z; i<=m; i++)
		{
			read(x);
			read(y);
			read(z);
			add_edge(x,y,z);
		}
		read(s);
		read(t);
		memset(dis,INF,sizeof(dis));
		dis[s][0]=0;
		cnt[s][0]=1;
		priority_queue<node>q;
		q.push(node {0,s,0});
		int u,p;
		while(!q.empty())
		{
			u=q.top().u;
			p=q.top().p;
			q.pop();
			if(vis[u][p])
				continue;
			//printf("%d %d %d %d\n",u,p,cnt[u][p],dis[u][p]);
			vis[u][p]=true;
			for(re int i=head[u]; i; i=edge[i].next)
			{
				co int &v=edge[i].to,d=dis[u][p]+edge[i].dis;
				if(dis[v][0]>d)
				{
					if(dis[v][0]!=INF)
					{
						dis[v][1]=dis[v][0];
						cnt[v][1]=cnt[v][0];
						q.push(node {dis[v][1],v,1});
					}
					dis[v][0]=d;
					cnt[v][0]=cnt[u][p];
					q.push(node {d,v,0});
				}
				else if(dis[v][0]==d)
					cnt[v][0]+=cnt[u][p];
				else if(dis[v][1]>d)
				{
					dis[v][1]=d;
					cnt[v][1]=cnt[u][p];
					q.push(node {d,v,1});
				}
				else if(dis[v][1]==d)
					cnt[v][1]+=cnt[u][p];
			}
		}
		/*putchar('\n');
		for(re int i=1; i<=n; i++)
			printf("%d %d %d %d %d\n",i,dis[i][0],cnt[i][0],dis[i][1],cnt[i][1]);*/
		//putchar('\n');
		printf("%d\n",cnt[t][0]+(dis[t][0]+1==dis[t][1]?cnt[t][1]:0));
		//putchar('\n');
		num_edge=0;
		fill(head+1,head+1+n,0);
		memset(cnt,0,sizeof(cnt));
		memset(vis,false,sizeof(vis));
	}
	return 0;
}
