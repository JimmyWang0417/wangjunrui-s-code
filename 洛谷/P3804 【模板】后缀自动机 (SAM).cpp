#include<cstdio>
#define re register
#define max(x,y) ((x)>(y)?(x):(y))
using namespace std;
const int N=2e6+5;
int head[N],num_edge;
struct Edge
{
	int next,to;
} edge[N];
inline void add_edge(int from,int to)
{
	edge[++num_edge].next=head[from];
	edge[num_edge].to=to;
	head[from]=num_edge;
}
struct node
{
	int ch[26],fa,len;
} point[N];
int tot=1,las=1,sum[N];
inline void insert(int c)
{
	int p=las,np=las=++tot;
	point[np].len=point[p].len+1;
	sum[tot]=1;
	for(; p&&!point[p].ch[c]; p=point[p].fa)
		point[p].ch[c]=np;
	if(!p)
		point[np].fa=1;
	else
	{
		int q=point[p].ch[c];
		if(point[q].len==point[p].len+1)
			point[np].fa=q;
		else
		{
			int nq=++tot;
			point[nq]=point[q];
			point[q].fa=point[np].fa=nq;
			point[nq].len=point[p].len+1;
			for(; p&&point[p].ch[c]==q; p=point[p].fa)
				point[p].ch[c]=nq;
		}
	}
}
long long ans;
inline void dfs(int u)
{
	for(re int i=head[u]; i; i=edge[i].next)
	{
		dfs(edge[i].to);
		sum[u]+=sum[edge[i].to];
	}
	if(sum[u]>1)
		ans=max(ans,1ll*point[u].len*sum[u]);
}
char s[N];
int main()
{
	scanf("%s",s);
	for(re int i=0; s[i]; ++i)
		insert(s[i]-'a');
	for(re int i=2; i<=tot; ++i)
		add_edge(point[i].fa,i);
	for(int i=1; i<=tot; ++i)
		printf("%d ",point[i].len-point[point[i].fa].len);
	putchar('\n');
	dfs(1);
	printf("%lld\n",ans);
	return 0;
}
