#include<cstdio>
#include<algorithm>
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
co int N=3e5*2+10;
int T,n,m,num_edge,head[N],src,det,low[N],dfn[N],dfstime,father[N];
bool cut[N];
struct Edge
{
	int next,from,to,dis;
} edge[N];
inline void add_edge(co int &from,co int &to,co int &dis)
{
	edge[num_edge].next=head[from];
	edge[num_edge].from=from;
	edge[num_edge].to=to;
	edge[num_edge].dis=dis;
	head[from]=num_edge++;
}
inline void Tarjan(co int &u,int e)
{
	low[u]=dfn[u]=++dfstime;
	for(re int i=head[u]; i!=-1; i=edge[i].next)
	{
		if(e==i)
			continue;
		int &v=edge[i].to;
		if(!dfn[v])
		{
			Tarjan(v,i^1);
			if(low[v]<low[u])
				low[u]=low[v];
			if(low[v]>dfn[u])
				cut[i]=cut[i^1]=true;
		}
		else if(dfn[v]<low[u])
			low[u]=dfn[v];
	}
	return;
}
inline int find(co int &x)
{
	if(!father[x])
		return x;
	return father[x]=find(father[x]);
}
int main()
{
	read(T);
	while(T--)
	{
		read(n);
		read(m);
		fill(head,head+1+n,-1);
		num_edge=0;
		for(re int i=1,u,v,w; i<=m; i++)
		{
			read(u);
			read(v);
			read(w);
			add_edge(u,v,w);
			add_edge(v,u,w);
		}
		read(src);
		read(det);
		//printf("%d\n",(-1)^1);
		add_edge(src,det,0);
		add_edge(det,src,0);
		fill(dfn,dfn+1+n,0);
		fill(low,low+1+n,0);
		fill(cut,cut+1+(m<<1)+5,0);
		fill(father,father+1+n,0);
		for(re int i=1; i<=n; i++)
			if(!dfn[i])
				Tarjan(i,-1);
		for(re int i=0,fx,fy; i<num_edge; i++)
			if(!cut[i])
			{
				fx=find(edge[i].from);
				fy=find(edge[i].to);
				if(fx!=fy)
					father[fx]=fy;
			}
		/*for(re int i=0; i<num_edge;i++)
		printf("%d %d\n",cut[i],edge[i].dis);*/
		bool flag=false;
		if(find(src)!=find(det))
		{
			puts("NO");
			continue;
		}
		for(re int i=0; i<num_edge; i++)
			if(find(src)==find(edge[i].from)&&(!cut[i])&&edge[i].dis)
			{
				flag=true;
				break;
			}
		puts(flag?"YES":"NO");
	}
	return 0;
}
