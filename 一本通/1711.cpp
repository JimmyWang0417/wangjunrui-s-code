#include<cstdio>
#include<queue>
#include<vector>
#include<algorithm>
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
const long long INF=1e18;
int n,num_edge,head[2010],f[2010][2010];
long long dis[2010],minn;
bool vis[2010];
long long ans;
priority_queue<pair<int,int> >q;
int main()
{
	read(n);
	for(re int i=1,w,j; i<=n; i++)
		for(j=i; j<=n; j++)
		{
			read(w);
			f[i-1][j]=f[j][i-1]=w;
		}
	fill(dis+1,dis+1+n,1e18);
	for(re int i=1; i<=n; i++)
	{
		dis[i]=f[0][i];
		q.push(make_pair(-dis[i],i));
	}
	while(!q.empty())
	{
		minn=INF;
		int u=q.top().second;
		q.pop();
		if(vis[u])
			continue;
		vis[u]=true;
		ans+=dis[u];
		for(re int j=1; j<=n; j++)
			if((!vis[j])&&dis[j]>f[u][j])
			{
				dis[j]=f[u][j];
				q.push(make_pair(-dis[j],j));
			}
	}
	printf("%lld\n",ans);
	return 0;
}

