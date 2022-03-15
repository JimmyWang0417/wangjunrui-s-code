#include <cstdio>
#include <cstring>
#define re register
using namespace std;
template <typename T>
inline void read(T &x)
{
	x=0;
	char s=(char)getchar();
	bool flag=false;
	while(s<'0'||s>'9')
	{
		if(s=='-')
			flag=true;
		s=(char)getchar();
	}
	while(s>='0'&&s<='9')
	{
		x=(x<<1)+(x<<3)+(s^'0');
		s=(char)getchar();
	}
	if(flag)
		x=~x+1;
	return;
}
const int N=5e5+5;
struct node
{
	int ch[26];
	int len,fa;
} point[N<<1];
int las=1,tot=1,f[N<<1],g[N<<1];
inline void insert(int c)
{
	int p=las;
	int np=las=++tot;
	point[np].len=point[p].len+1;
	f[np]=1;
	for(; p&&!point[p].ch[c]; p=point[p].fa)
		point[p].ch[c]=np;
	if(!p)
		point[np].fa=1;
	else
	{
		int q=point[p].ch[c];
		if(point[p].len+1==point[q].len)
			point[np].fa=q;
		else
		{
			int nq=++tot;
			point[nq]=point[q];
			point[nq].len=point[p].len+1;
			point[np].fa=point[q].fa=nq;
			for(; p&&point[p].ch[c]==q; p=point[p].fa)
				point[p].ch[c]=nq;
		}
	}
}
int t,k;
struct Edge
{
	int next,to;
} edge[N*3];
int head[N*2],num_edge;
inline void add_edge(int from,int to)
{
	edge[++num_edge].next=head[from];
	edge[num_edge].to=to;
	head[from]=num_edge;
}
inline void dfs1(int u)
{
	for(re int i=head[u]; i; i=edge[i].next)
	{
		int &v=edge[i].to;
		if(!v)
			continue;
		dfs1(v);
		f[u]+=f[v];
	}
}
inline void dfs2(int u)
{
	if(g[u]!=-1)
		return;
	g[u]=f[u];
	for(re int i=0; i<26; ++i)
	{
		int &v=point[u].ch[i];
		if(!v)
			continue;
		dfs2(v);
		g[u]+=g[v];
	}
}
inline void print(int u,int k_th)
{
	k_th-=f[u];
	if(k_th<=0)
		return;
	for(re int i=0; i<26; ++i)
	{
		int &v=point[u].ch[i];
		if(!v)
			continue;
		if(k_th>g[v])
			k_th-=g[v];
		else
		{
			putchar('a'+i);
			print(v,k_th);
			return;
		}
	}
}
char s[N];
int main()
{
	scanf("%s",s);
	read(t),read(k);
	memset(g,-1,sizeof(g));
//	printf("%d\n",g[1]);
	for(re int i=0; s[i]; ++i)
		insert(s[i]-'a');
	if(t)
	{
		for(re int i=2; i<=tot; ++i)
			add_edge(point[i].fa,i);
		dfs1(1);
	}
	else for(re int i=tot; i>=2; --i)
			f[i]=1;
	f[1]=0;
//	for(re int i=1; i<=tot; ++i)
//		printf("%d ",f[i]);
	dfs2(1);
//	for(re int i=1; i<=tot; ++i)
//		printf("%d ",g[i]);
	if(g[1]<k)
		printf("-1\n");
	else
		print(1,k);
	return 0;
}
