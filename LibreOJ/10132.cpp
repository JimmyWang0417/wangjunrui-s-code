#include<cstdio>
#include<set>
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
const int N=1e5+5;
struct
{
	int next,to,dis;
} edge[N<<1];
int head[N],num_edge,dep[N],f[N][25],
    dfn[N],dfs_time,n,m,id[N];
long long ans,dis[N];
inline void add_edge(int from,int to,int dis)
{
	edge[++num_edge].next=head[from];
	edge[num_edge].to=to;
	head[from]=num_edge;
	edge[num_edge].dis=dis;
}
inline void Deal_first(int u,int father)
{
	dfn[u]=++dfs_time;
	dep[u]=dep[father]+1;
	for(re int i=0; i<=20; i++)
		f[u][i+1]=f[f[u][i]][i];
	for(re int i=head[u],v; i; i=edge[i].next)
	{
		v=edge[i].to;
		if(v==father)
			continue;
		f[v][0]=u;
		dis[v]=dis[u]+edge[i].dis;
		Deal_first(v,u);
	}
	return;
}
inline int LCA(int x,int y)
{
	if(dep[x]<dep[y])
		swap(x,y);
	for(re int i=21; ~i; i--)
	{
		if(dep[f[x][i]]>=dep[y])
			x=f[x][i];
		if(x==y)
			return x;
	}
	for(re int i=21; ~i; i--)
		if(f[x][i]!=f[y][i])
		{
			x=f[x][i];
			y=f[y][i];
		}
	return f[x][0];
}
#define iter set<int>::iterator
#define dist(x,y) (dis[x]+dis[y]-(dis[LCA(x,y)]<<1))
set<int>s;
inline void add(int x)
{
	if(s.empty())
	{
		s.insert(dfn[x]);
		return;
	}
	iter it=s.lower_bound(dfn[x]);
	if(it==s.end()||it==s.begin())
	{
		iter begin=s.begin(),end=s.end();
		end--;
		ans-=dist(id[*begin],id[*end]);
		ans+=dist(id[*begin],x)+dist(x,id[*end]);
		s.insert(dfn[x]);
	}
	else
	{
		iter pre=it,nxt=it;
		pre--;
		ans-=dist(id[*pre],id[*nxt]);
		ans+=dist(id[*pre],x)+dist(x,id[*nxt]);
		s.insert(dfn[x]);
	}
}
inline void del(int x)
{
	s.erase(dfn[x]);
	if(s.empty())
		return;
	iter it=s.lower_bound(dfn[x]);
	if(it==s.end()||it==s.begin())
	{
		iter begin=s.begin(),end=s.end();
		end--;
		ans+=dist(id[*begin],id[*end]);
		ans-=dist(id[*begin],x)+dist(x,id[*end]);
	}
	else
	{
		iter pre=it,nxt=it;
		pre--;
		ans+=dist(id[*pre],id[*nxt]);
		ans-=dist(id[*pre],x)+dist(x,id[*nxt]);
	}
}
int main()
{
	read(n);
	for(re int i=1,x,y,z; i<n; i++)
	{
		read(x);
		read(y);
		read(z);
		add_edge(x,y,z);
		add_edge(y,x,z);
	}
	Deal_first(1,0);
	for(re int i=1; i<=n; i++)
		id[dfn[i]]=i;
	read(m);
	for(re int i=1,x; i<=m; i++)
	{
		char s=getchar();
		while(s!='+'&&s!='-'&&s!='?')
			s=getchar();
		if(s=='+')
		{
			read(x);
			add(x);
		}
		else if(s=='-')
		{
			read(x);
			del(x);
		}
		else
			printf("%lld\n",ans>>1);
	}
	return 0;
}

