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
const int N=1000,M=1e6+5;
int n,m,head[1005],num_edge,dis[1005],
    f[1005],maxx;
queue<int>q;
bool cut[1005][1005],exist[1005],flag;
struct Edge
{
	int next,to,dis;
} edge[1000005];
inline void add_edge(int from,int to,int dis)
{
	edge[++num_edge].next=head[from];
	head[from]=num_edge;
	edge[num_edge].to=to;
	edge[num_edge].dis=dis;
}
inline void spfa()
{
	memset(dis,0x3f3f3f3f,sizeof(dis));
	dis[1]=0;
	q.push(1);
	do
	{
		int u=q.front();
		q.pop();
		exist[u]=false;
		/**/for(re int i=head[u],v,w; i; i=edge[i].next)
		{
			w=edge[i].dis;
			v=edge[i].to;
			if(dis[v]>dis[u]+w&&(!cut[u][v]))
			{
				if(!flag)
					f[v]=u;
				dis[v]=dis[u]+w;
				if(!exist[v])
				{
					exist[v]=true;
					q.push(v);
				}
			}
		}
	}
	while(!q.empty());
	return;
}
int main()
{
	read(n);
	read(m);
	for(re int i=1,x,y,z; i<=m; i++)
	{
		read(x);
		read(y);
		read(z);
		add_edge(x,y,z);
		add_edge(y,x,z);
	}
	spfa();
	flag=true;
	for(re int i=n,d; i!=1; i=f[i])
	{
		cut[f[i]][i]=cut[i][f[i]]=true;
		spfa();
		if(dis[n]>maxx)
			maxx=dis[n];
		cut[f[i]][i]=cut[i][f[i]]=false;
	}
	printf("%d\n",maxx);
	return 0;
}

