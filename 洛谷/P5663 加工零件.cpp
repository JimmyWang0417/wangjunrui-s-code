#include<cstdio>
#include<cstring>
#include<queue>
#define re register
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
const int N=1e5+10,M=N<<1;
struct Edge
{
	int next,to;
} edge[M];
bool vis[N][2],exist[N];
int n,m,q;
int head[N],num_edge;
int dis[N][2];
queue<int>que;
char ans[2][12]= {"No\n","Yes\n"};
inline void add_edge(int from,int to)
{
	edge[++num_edge].next=head[from];
	head[from]=num_edge;
	edge[num_edge].to=to;
}
int main()
{
	read(n),read(m),read(q);
	memset(dis,0x3f3f3f3f,sizeof(dis));
	int x,y,a,l;
	for(re int i=1; i<=m; ++i)
	{
		read(x),read(y);
		add_edge(x,y);
		add_edge(y,x);
	}
	dis[1][0]=0;
	vis[1][0]=true;
	que.push(1);
	while(!que.empty())
	{
		int u=que.front();
		exist[u]=false;
		que.pop();
		for(re int i=head[u]; i; i=edge[i].next)
		{
			int &v=edge[i].to;
			if(dis[v][0]>dis[u][1]+1)
			{
				dis[v][0]=dis[u][1]+1;
				vis[v][0]=true;
				if(!exist[v])
				{
					que.push(v);
					exist[v]=true;
				}
			}
			if(dis[v][1]>dis[u][0]+1)
			{
				dis[v][1]=dis[u][0]+1;
				vis[v][1]=true;
				if(!exist[v])
				{
					que.push(v);
					exist[v]=true;
				}
			}
		}
	}
	/*for(re int i=1; i<=n; ++i)
		printf("%d %d %d %d %d\n",i,dis[i][0],dis[i][1],vis[i][0],vis[i][1]);*/
	for(re int i=1; i<=q; ++i)
	{
		read(a),read(l);
		printf("%s",ans[dis[a][l%2]<=l]);
	}
	return 0;
}
