#include<cstdio>
#include<queue>
#include<cstring>
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
queue<int>q;
const int N=(2000<<1)+5,M=(3000<<1)+5;
struct Edge
{
	int next,to,dis;
} edge[M];
int n,m,T,head[N],num_edge,cnt[N],dis[N];
bool exist[N];
inline void add_edge(int from,int to,int dis)
{
	edge[++num_edge].next=head[from];
	edge[num_edge].to=to;
	edge[num_edge].dis=dis;
	head[from]=num_edge;
}
inline bool spfa(int a)
{
	int u;
	memset(dis,0x3f3f3f3f,sizeof(dis));
	memset(exist,false,sizeof(exist));
	memset(cnt,0,sizeof(cnt));
	q.push(a);
	dis[a]=0;
	cnt[a]=0;
	while(!q.empty())
	{
		int u=q.front();
		q.pop();
		exist[u]=false;
		for(re int i=head[u],*v,*w; i; i=edge[i].next)
		{
			v=&edge[i].to;
			w=&edge[i].dis;
			if(dis[*v]>dis[u]+(*w))
			{
				dis[*v]=dis[u]+(*w);
				cnt[*v]=cnt[u]+1;
				if(cnt[*v]>num_edge)
					return true;
				if(!exist[*v])
				{
					exist[*v]=true;
					q.push(*v);
				}
			}
		}
	}
	return false;
}
int main()
{
	read(T);
	while(T--)
	{
		read(n);
		read(m);
		memset(head,0,sizeof(head));
		num_edge=0;
		for(re int i=1,x,y,z; i<=m; i++)
		{
			read(x);
			read(y);
			read(z);
			add_edge(x,y,z);
			if(z>=0)
				add_edge(y,x,z);
		}
		if(spfa(1))
			printf("YE5\n");
		else
			printf("N0\n");
	}
}
