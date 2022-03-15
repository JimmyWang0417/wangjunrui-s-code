#include<cstdio>
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
const int N=100010;
struct node
{
	int next,to,dis;
} edge[N<<1];
int ch[N*31][2],xo[N],head[N],num_edge,tot,ans,n;
inline void add_edge(const int &from,const int &to,const int &dis)
{
	edge[++num_edge].next=head[from];
	head[from]=num_edge;
	edge[num_edge].to=to;
	edge[num_edge].dis=dis;
}
inline void dfs(int u,int father)
{
	for(re int i=head[u]; i; i=edge[i].next)
	{
		int &v=edge[i].to,&w=edge[i].dis;
		if(v!=father)
		{
			xo[v]=xo[u]^w;
			dfs(v,u);
		}
	}
}
inline int query(int pre,int x)
{
	int ans=0;
	for(re int i=(1<<30); i; i>>=1)
	{
		bool c=x&i;
		if(ch[pre][c^1])
		{
			ans+=i;
			pre=ch[pre][c^1];
		}
		else
			pre=ch[pre][c];
	}
	return ans;
}
inline void make(int pre,int x)
{
	for(re int i=(1<<30); i; i>>=1)
	{
		bool c=x&i;
		if(!ch[pre][c])
			ch[pre][c]=++tot;
		pre=ch[pre][c];
	}
}
int main()
{
	read(n);
	for(re int i=1,u,v,w; i<=n-1; i++)
	{
		read(u);
		read(v);
		read(w);
		add_edge(u,v,w);
		add_edge(v,u,w);
	}
	dfs(1,0);
	int pre=0;
	for(re int i=1; i<=n; i++)
		make(pre,xo[i]);
	for(re int i=1; i<=n; i++)
		ans=max(ans,query(pre,xo[i]));
	printf("%d\n",ans);
	return 0;
}
