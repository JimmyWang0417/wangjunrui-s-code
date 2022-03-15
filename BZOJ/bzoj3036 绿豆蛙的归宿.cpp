#include<cstdio>
#define re register
template<typename T>
inline void read(T&x)
{
	x=0;
	char s=(char)getchar();
	bool flag=false;
	while(!(s>='0'&&s<='9'))
	{
		if(s=='-')
			flag=true;
		s=(char)getchar();
	}
	while(s>='0'&&s<='9')
	{
		x=(x<<1)+(x<<3)+s-'0';
		s=(char)getchar();
	}
	if(flag)
		x=(~x)+1;
}
const int N=1e5+5;
int n,m,head[N],outedge[N],inedge[N],q[N],num_edge;
struct Edge
{
	int next,to,dis;
} edge[N<<1];
double f[N];
inline void add_edge(int from,int to,int dis)
{
	edge[++num_edge].next=head[from];
	edge[num_edge].to=to;
	edge[num_edge].dis=dis;
	head[from]=num_edge;
}
int main()
{
	read(n);
	read(m);
	for(re int i=1; i<=m; ++i)
	{
		static int u,v,w;
		read(u);
		read(v);
		read(w);
		add_edge(u,v,w);
		++outedge[u];
		++inedge[v];
	}
	re int l=0,r=0;
	q[++r]=1;
	while(r>l)
	{
		int u=q[++l];
		for(re int i=head[u]; i; i=edge[i].next)
		{
			if(!(--inedge[edge[i].to]))
				q[++r]=edge[i].to;
		}
	}
	for(re int i=n-1; i>=1; --i)
	{
		int u=q[i];
		for(re int e=head[u]; e; e=edge[e].next)
			f[u]+=(f[edge[e].to]+edge[e].dis)/outedge[u];
	}
	printf("%.2lf\n",f[1]);
	return 0;
}
