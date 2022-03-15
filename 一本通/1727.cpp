#include<cstdio>
#include<cmath>
#include<algorithm>
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
const int N=1000010;
int n,hp,a[N],sum[N],head[N],num_edge,cnt[N],dis[N];
bool exist[N];
struct Edge
{
	int next,to,dis;
} edge[N];
inline void add_edge(co int from,co int to,co int dis)
{
	edge[++num_edge].next=head[from];
	head[from]=num_edge;
	edge[num_edge].to=to;
	edge[num_edge].dis=dis;
}
inline bool spfa(co int cd)
{
	num_edge=0;
	fill(head,head+1+n,0);
	fill(exist,exist+1+n,1);
	fill(dis,dis+1+n,0);
	fill(cnt,cnt+1+n,0);
	for(re int i=1; i<=n; i++)
	{
		add_edge(i-1,i,0);
		add_edge(i,i-1,-1);
	}
	for(re int i=cd; i<=n; i++)
		add_edge(i,i-cd,-1);
	for(re int i=1; i<n; i++)
	{
		int pos=ceil((1+sum[i+1]-hp)/15.0);
		if(pos>0)
			add_edge(pos-1,i,1);
	}
	queue<int>q;
	for(re int i=0; i<=n; i++)
	{
		q.push(i);
	}
	while(!q.empty())
	{
		int u=q.front();
		q.pop();
		exist[u]=false;
		for(re int i=head[u]; i; i=edge[i].next)
		{
			int &v=edge[i].to,&w=edge[i].dis;
			if(dis[v]<dis[u]+w)
			{
				dis[v]=dis[u]+w;
				cnt[v]=cnt[u]+1;
				if(cnt[v]>num_edge)
					return true;
				if(!exist[v])
				{
					exist[v]=false;
					q.push(v);
				}
			}
		}
	}
	return false;
}
int main()
{
	read(n);
	read(hp);
	for(re int i=1; i<=n; i++)
	{
		read(a[i]);
		sum[i]=sum[i-1]+a[i];
	}
	re int l=1,r=n,ans=-1,mid;
	while(l<=r)
	{
		mid=l+r>>1;
		if(!spfa(mid))
		{
			ans=mid;
			l=mid+1;
		}
		else
			r=mid-1;
	}
	if(ans==n)
		puts("No upper bound.");
	else if(ans==-1)
		puts("-1");
	else
		printf("%d\n",ans);
	return 0;
}
