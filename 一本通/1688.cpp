#include<cstdio>
#include<vector>
#include<cstring>
#include<algorithm>
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
const int N=100010,M=200010<<1;
int n,m,t,x,y,z,dis[N],head[N],num_edge,a[N],b[N],ans[N],tot,top,ott,minn,u;
bool vis[N];
struct node
{
	int v,c;
} temp;
struct Edge
{
	int next,to,col;
} edge[M];
queue<int>q;
inline void add_edge(int&from,int&to,int&dis)
{
	edge[++num_edge].next=head[from];
	edge[num_edge].to=to;
	edge[num_edge].col=dis;
	head[from]=num_edge;
}
inline void clear()
{
	memset(head,0,sizeof(head));
	memset(vis,false,sizeof(vis));
	tot=top=ott=num_edge=0;
}
inline void bfs()
{
	q.push(n);
	dis[n]=0;
	vis[n]=true;
	while(!q.empty())
	{
		u=q.front();
		q.pop();
		for(re int i=head[u]; i; i=edge[i].next)
		{
			int &v=edge[i].to;
			if(vis[v])
				continue;
			vis[v]=true;
			dis[v]=dis[u]+1;
			q.push(v);
		}
	}
}
int main()
{
	read(t);
	while(t--)
	{
		read(n);
		read(m);
		for(re int i=1; i<=m; i++)
		{
			read(x);
			read(y);
			read(z);
			add_edge(x,y,z);
			add_edge(y,x,z);
		}
		bfs();
		printf("%d\n",dis[1]);
		/*for(re int i=1; i<=n; i++)
			printf("%d %d\n",i,dis[i]);*/
		a[tot=1]=1;
		int aa;
		for(re int i=1; i<=dis[1]; i++)
		{
			minn=0x7fffffff;/*
			for(re int j=1; j<=tot; j++)
				printf("%d ",a[j]);
			putchar('\n');*/
			//printf("%d\n",minn);
			for(re int j=1; j<=tot; j++)
				for(re int e=head[a[j]]; e; e=edge[e].next)
				{
					int &v=edge[e].to,&w=edge[e].col;
					if(dis[v]+1==dis[a[j]]&&w<minn)
					{
						minn=w;
						aa=v;
					}
				}
			ans[++top]=minn;
			ott=0;
			for(re int j=1; j<=tot; j++)
				for(re int e=head[a[j]]; e; e=edge[e].next)
				{
					int &v=edge[e].to,&w=edge[e].col;
					if(dis[v]+1==dis[a[j]]&&w==minn)
						b[++ott]=v;
				}
			/*for(re int j=1; j<=ott; j++)
				printf("%d ",b[j]);
			putchar('\n');*/
			for(re int j=1; j<=ott; j++)
				a[j]=b[j];
			stable_sort(a+1,a+1+ott);
			tot=unique(a+1,a+1+ott)-a-1;
		}
		for(re int i=1; i<=top; i++)
			printf("%d ",ans[i]);
		putchar('\n');
		clear();
	}
}

