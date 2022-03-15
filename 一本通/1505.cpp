#include<cstdio>
#include<queue>
#include<cstring>
using namespace std;
inline int min(int a,int b)
{
	return a<b?a:b;
}
#define r register
inline int read()
{
	char s=getchar();
	bool f=false;
	int x=0;
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
	return f?-x:x;
}
const int N=1e4+5;
struct node
{
	int first,second;
};
struct Edge
{
	int next,end,tim,fee;
} edge[605];
queue<node>q;
int dis[105][N],vis[105][N],delt[105][N],
    tot,n,m,s,t,ans,poi[605];
inline void add_edge(int x,int y,int z,int w)
{
	edge[++tot].next=poi[x];
	edge[tot].end=y;
	edge[tot].tim=z;
	edge[tot].fee=w;
	poi[x]=tot;
}
inline int query(int x,int y)
{
	++y;
	int mn=1e7;
	for(; y; y-=(y&-y))
		mn=min(mn,delt[x][y]);
	return mn;
}
inline void updata(int x,int y,int val)
{
	++y;
	for(; y<=n*100; y+=(y&-y))
		delt[x][y]=min(delt[x][y],val);
}
inline void spfa()
{
	memset(dis,63,sizeof(dis));
	memset(delt,63,sizeof(delt));
	r node a;
	a.first=s;
	a.second=0;
	q.push(a);
	dis[s][0]=0;
	updata(s,0,0);
	while(!q.empty())
	{
		a=q.front();
		int x=a.first,f1=a.second;
		q.pop();
		vis[x][f1]=0;
		for(r int i=poi[x],y; y=edge[i].end,i; i=edge[i].next)
		{
			int f2=f1+edge[i].fee;
			if(query(y,f2)>dis[x][f1]+edge[i].tim)
			{
				dis[y][f2]=dis[x][f1]+edge[i].tim;
				updata(y,f2,dis[y][f2]);
				if(!vis[y][f2])
				{
					vis[y][f2]=1;
					a.first=y;
					a.second=f2;
					q.push(a);
				}
			}
		}
	}
}
int main()
{
	n=read();
	m=read();
	s=read();
	t=read();
	for(r int i=1,x,y,w,z; i<=m; i++)
	{
		x=read();
		y=read();
		w=read();
		z=read();
		add_edge(x,y,z,w);
		add_edge(y,x,z,w);
	}
	spfa();
	int mn=dis[0][0];
	for(r int i=0; i<=n*100; i++)
		if(dis[t][i]<mn)
		{
			++ans;
			mn=dis[t][i];
		}
	printf("%d\n",ans);
}

