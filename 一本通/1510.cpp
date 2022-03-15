#include<cstdio>
#include<queue>
#include<cstring>
using namespace std;
#define INF 0x3f3f3f3f
#define N 1010
#define re register
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
inline int min(const int&a,const int &b)
{
	return a<b?a:b;
}
inline int max(const int&a,const int&b)
{
	return a>b?a:b;
}
struct Edge
{
	int next,to,dis;
} edge[N<<5];
int num_edge,head[N],n,dis[N],u,v,w,ru[N];
bool exist[N];
inline void add_edge(int from,int to,int dis)
{
	edge[++num_edge].next=head[from];
	head[from]=num_edge;
	edge[num_edge].to=to;
	edge[num_edge].dis=dis;
}
int num[N],r[N],t,a[N];
inline bool SPFA(const int&ans)
{
	queue<int>q;
	memset(edge,0,sizeof(edge));

	memset(exist,false,sizeof(exist));

	memset(dis,-INF,sizeof(dis));

	memset(head,0,sizeof(head));

	memset(ru,0,sizeof(ru));
	ru[0]=1;
	num_edge=0;
	for(re int i=1; i<=24; i++)
	{
		add_edge(i-1,i,0);
		add_edge(i,i-1,-num[i]);
		add_edge(0,i,0);
	}
	for(re int i=1; i<=8; i++)
		add_edge(i+16,i,r[i]-ans);
	for(re int i=9; i<=24; i++)
		add_edge(i-8,i,r[i]);
	add_edge(0,24,ans);
	dis[0]=0;
	exist[0]=true;
	q.push(0);
	do
	{
		int u=q.front();
		q.pop();
		for(re int i=head[u]; i; i=edge[i].next)
		{
			int *v=&edge[i].to,*w=&edge[i].dis;
			if(dis[*v]<dis[u]+(*w))
			{
				dis[*v]=dis[u]+(*w);
				if(!exist[*v])
				{
					exist[*v]=true;
					q.push(*v);
					if(++ru[*v]>24)
						return false;
				}
			}
		}
		exist[u]=false;
	}
	while(!q.empty());
	return true;
}
int main()
{
	//freopen("ans.in","r",stdin);
	//freopen("ans.out","w",stdout);
	t=read();
	while(t--)
	{
		memset(num,0,sizeof(num));
		int ans;
		bool flag=true;
		for(re int i=1; i<=24; i++)
			r[i]=read();
		n=read();
		for(re int i=1; i<=n; i++)
		{
			a[i]=read();
			num[a[i]+1]++;
		}
		for(re int i=0; i<=n; i++)
			if(SPFA(i))
			{
				printf("%d\n",i);
				flag=false;
				break;
			}
		if(flag)printf("No Solution\n");
	}
	return 0;
}
