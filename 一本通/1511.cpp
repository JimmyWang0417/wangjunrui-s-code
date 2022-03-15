#include<cstdio>
#include<cstring>
#define N 100010
#define M 1000010
#define re register
using namespace std;
unsigned long long sum;
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
int n,k,
    head[N],num_edge,
    dis[N];
char s[20];
bool vis[N],PC;
inline void write(unsigned long long x)
{
	int top=0;
	while(x)
	{
		s[++top]=x%10+'0';
		x/=10;
	}
	if(!top)
		s[++top]=0;
	while(top)
		putchar(s[top--]);
}
struct Edge
{
	int next,
	    to,
	    dis;
} edge[M];
inline void add_edge(const int &from,const int to,const int dis)
{
	edge[++num_edge].next=head[from];
	edge[num_edge].to=to;
	head[from]=num_edge;
	edge[num_edge].dis=dis;
}
inline void SPFA(int u)
{
	if(PC)
		return;
	vis[u]=true;
	for(re int i=head[u],*v,*w; i; i=edge[i].next)
	{
		v=&edge[i].to;
		w=&edge[i].dis;
		if(dis[*v]<dis[u]+(*w))
		{
			dis[*v]=dis[u]+(*w);
			if(!vis[*v])
				SPFA(*v);
			else
			{
				PC=true;
				return;
			}
			if(PC)return;
		}
	}
	vis[u]=false;
}
int main()
{
	n=read();
	k=read();
	for(re int i=1,x,a,b; i<=k; i++)
	{
		x=read();
		a=read();
		b=read();
		if(x==1)
		{
			add_edge(a,b,0);
			add_edge(b,a,0);
		}
		else if(x==2)
			add_edge(a,b,1);
		else if(x==3)
			add_edge(b,a,0);
		else if(x==4)
			add_edge(b,a,1);
		else if(x==5)
			add_edge(a,b,0);
	}
	for(re int i=1; i<=n; i++)
		dis[i]=1;
	for(re int i=1; i<=n; i++)
	{
		SPFA(i);
		if(PC)
		{
			printf("-1\n");
			return 0;
		}
	}
	for(re int i=1; i<=n; i++)
		sum+=dis[i];
	write(sum);
}
