#include<cstdio>
#include<cstring>
#include<queue>
#define re register
using namespace std;
char before[1010][1010],now[1010][1010];
int g[1000010],dis[(1<<28)+100],n,m,kase;
bool exist[(1<<28)+100];
queue<int>q;
int main()
{
	scanf("%d%d",&n,&m);
	for(re int i=1; i<=m; i++)
		scanf("%d%s%s",&g[i],before[i],now[i]);
	fill(dis,dis+(1<<n),0x3f3f3f3f);
	dis[(1<<n)-1]=0;
	q.push((1<<n)-1);
	while(!q.empty())
	{
		int u=q.front();
		q.pop();
		exist[u]=false;
		for(re int i=1; i<=m; i++)
		{
			//printf("%d\n",u);
			bool flag=true;
			for(re int j=0; j<n; j++)
			{
				if(before[i][j]=='-'&&((1<<j)&u))
					flag=false;
				if(before[i][j]=='+'&&!((1<<j)&u))
					flag=false;
			}
			//printf("%d %d %d\n",u,i,flag);
			if(flag)
			{
				int v=u;
				for(re int j=0; j<n; j++)
					if(now[i][j]=='-')
						v&=~(1<<j);
					else if(now[i][j]=='+')
						v|=(1<<j);
				if(dis[v]>dis[u]+g[i])
				{
					dis[v]=dis[u]+g[i];
					if(!exist[v])
					{
						exist[v]=true;
						q.push(v);
					}
				}
			}
		}
	}
	if(dis[0]==0x3f3f3f3f)
		printf("0\n");
	else
		printf("%d\n",dis[0]);
	return 0;
}
