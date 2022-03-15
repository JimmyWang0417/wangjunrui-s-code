#include<cstdio>
#include<algorithm>
#define re register
#define ll long long
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
const int N=100005;
struct Edge
{
	int next,to,dis;
} edge[N<<1];
int head[N],num_edge;
inline void add_edge(const int &from,const int &to,const int &dis)
{
	edge[++num_edge].next=head[from];
	edge[num_edge].to=to;
	edge[num_edge].dis=dis;
	head[from]=num_edge;
}
int ch[N*30][2],tot=1;
inline void insert(int x)
{
	for(re int i=30,u=1; i>=0; --i)
	{
		bool c=x&(1<<i);
		if(!ch[u][c])
			ch[u][c]=++tot;
		u=ch[u][c];
	}
}
inline int find(int x)
{
	int ans=0;
	for(re int i=30,u=1; i>=0; --i)
	{
		bool c=x&(1<<i);
		if(ch[u][!c])
		{
			ans|=(1<<i);
			u=ch[u][!c];
		}
		else
			u=ch[u][c];
	}
	return ans;
}
int dis[N],n;
inline void dfs(int u,int fa)
{
	for(re int i=head[u]; i; i=edge[i].next)
	{
		int &v=edge[i].to,&w=edge[i].dis;
		if(v==fa)
			continue;
		dis[v]=dis[u]^w;
		dfs(v,u);
	}
}
int main()
{
	read(n);
	for(re int i=1; i<n; ++i)
	{
		int u,v,w;
		read(u);
		read(v);
		read(w);
		add_edge(u,v,w);
		add_edge(v,u,w);
	}
	dfs(1,0);
	for(re int i=1; i<=n; ++i)
		insert(dis[i]);
	int ans=0;
	for(re int i=1; i<=n; ++i)
		ans=max(ans,find(dis[i]));
	printf("%d\n",ans);
	return 0;
}
