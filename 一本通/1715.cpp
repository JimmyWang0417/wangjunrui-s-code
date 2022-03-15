#include<cstdio>
#include<queue>
#include<vector>
#include<cstring>
#define re register
using namespace std;
#define pill pair<int,int>
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
const int N=2e5+10;
priority_queue<pill>q;
int n,m,dis[N<<1];
bool vis[N<<1];
vector<int>bus[N],id[N],time[N];
int main()
{
	read(n);
	read(m);
	for(re int i=1,t,x; i<=m; i++)
	{
		read(t);
		for(re int p=0; p<t; p++)
		{
			read(x);
			bus[i].push_back(x);
			time[x].push_back(p);
			id[x].push_back(i);
		}
	}
	q.push(make_pair(0,1));
	memset(dis,0x3f3f3f3f,sizeof(dis));
	dis[1]=0;
	while(!q.empty())
	{
		int u=q.top().second;
		q.pop();
		if(vis[u])
			continue;
		vis[u]=true;
		if(u<=n)
		{
			int len=id[u].size();
			for(re int i=0; i<len; i++)
			{
				int v=id[u][i]+n,l=bus[v-n].size();
				int now=dis[u]%l;
				int d;
				if(time[u][i]>=now)
					d=time[u][i]-now+dis[u];
				else
					d=time[u][i]+l-now+dis[u];
				if(dis[v]>d)
				{
					dis[v]=d;
					q.push(make_pair(-d,v));
				}
			}
		}
		else
		{
			int len=bus[u-n].size();
			int t=dis[u]%len;
			for(re int i=0; i<len; i++)
			{
				int v=bus[u-n][t];
				int d=dis[u]+i;
				if(dis[v]>d)
				{
					dis[v]=d;
					q.push(make_pair(-d,v));
				}
				t=(t+1)%len;
			}
		}
	}
	for(re int i=2; i<=n; i++)
		if(dis[i]>=0x3f3f3f3f)
			printf("-1 ");
		else
			printf("%d ",dis[i]);
	putchar('\n');
	return 0;
}
