#include<cstdio>
#include<vector>
#include<cstring>
#include<algorithm>
#define re register
using namespace std;
const int N=1e6+5;
int ch[N][30],tot;
int flag[N],cnt;
int size[N];
int head[N],num_edge;
int n;
long long ans;
struct Edge
{
	int next,to;
} edge[N<<1];
char str[N];
inline void insert()
{
	scanf("%s",str);
	int u=0;
	for(re int i=strlen(str)-1; i>=0; --i)
	{
		int c=str[i]-'a';
		if(!ch[u][c])
			ch[u][c]=++tot;
		u=ch[u][c];
	}
	flag[u]=true;
}
inline void add_edge(int from,int to)
{
	edge[++num_edge].next=head[from];
	head[from]=num_edge;
	edge[num_edge].to=to;
}
inline void dfs1(int u,int fa)
{
	if(flag[u])
	{
		add_edge(fa,u);
		size[u]=1;
		fa=u;
	}
	for(re int i=0; i<=25; ++i)
		if(ch[u][i])
		{
			dfs1(ch[u][i],fa);
			size[u]+=size[ch[u][i]];
		}
}
inline void dfs2(int pre,int u)
{
	if(flag[u])
	{
		++cnt;
		ans+=cnt-pre;
		pre=cnt;
	}
	vector<int>team;
	for(re int i=head[u]; i; i=edge[i].next)
		team.push_back(edge[i].to);
	sort(team.begin(),team.end(),[](int x,int y)
	{
		return size[x]<size[y];
	});
	for(re int i=0; i<team.size(); ++i)
		dfs2(pre,team[i]);
}
int main()
{
	scanf("%d",&n);
	for(re int i=1; i<=n; ++i)
		insert();
	dfs1(0,0);
	dfs2(0,0);
	printf("%lld\n",ans);
}
