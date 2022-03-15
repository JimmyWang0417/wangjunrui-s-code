#include <bits/stdc++.h>
#define lowbit(x) ((x)&(-(x)))
#define re register
#define ll long long
#define ull unsigned long long
#define rep(i,a,b) for(re int i=a;i<=b;++i)
#define per(i,a,b) for(re int i=a;i>=b;--i)
template<typename T>
inline void read(T&x)
{
	x=0;
	char s=(char)getchar();
	bool f=false;
	while(!(s>='0'&&s<='9'))
	{
		if(s=='-')
			f=true;
		s=(char)getchar();
	}
	while(s>='0'&&s<='9')
	{
		x=(x<<1)+(x<<3)+s-'0';
		s=(char)getchar();
	}
	if(f)
		x=(~x)+1;
}
template<typename T,typename ...T1>
inline void read(T&x,T1&...x1)
{
	read(x);
	read(x1...);
}
template<typename T>
inline void clear(T*a,int l,int r,int val)
{
	memset(&a[l],val,sizeof(T)*(r-l+1));
}
const int N=1e6+5;
struct Edge
{
	int next,to;
} edge[N<<1];
int head[N],num_edge;
inline void add_edge(int from,int to)
{
	edge[++num_edge].next=head[from];
	edge[num_edge].to=to;
	head[from]=num_edge;
}
int n,m;
int dep[N],sze[N],son[N];
inline void dfs1(int u,int fa)
{
	dep[u]=dep[fa]+1;
	sze[u]=1;
//	printf(" %d:",u);
//	for(re int i=head[u]; i; i=edge[i].next)
//	{
//		int &v=edge[i].to;
//		if(v==fa)
//			continue;
//		printf(" %d",v);
//	}
//	putchar('\n');
	for(re int i=head[u]; i; i=edge[i].next)
	{
		int &v=edge[i].to;
		if(v==fa)
			continue;
		dfs1(v,u);
		sze[u]+=sze[v];
		if(sze[v]>sze[son[u]])
			son[u]=v;
	}
}
char str[N];
int cnt[N][26];
int Son;
int ans[N];
bool answer[N];
inline void update(int u,int val)
{
	ans[dep[u]]-=cnt[dep[u]][str[u]-'a']%2;
	cnt[dep[u]][str[u]-'a']+=val;
	ans[dep[u]]+=cnt[dep[u]][str[u]-'a']%2;
}
inline void add(int u,int fa,int val)
{
	update(u,val);
	for(re int i=head[u]; i; i=edge[i].next)
	{
		int &v=edge[i].to;
		if(v==fa||v==Son)
			continue;
		add(v,u,val);
	}
}
using std::pair;
using std::make_pair;
std::vector<pair<int,int> >query[N];
inline void dfs2(int u,int fa,bool opt)
{
//	printf("%d %d\n",u,fa);
	for(re int i=head[u]; i; i=edge[i].next)
	{
		int &v=edge[i].to;
		if(v==fa||v==son[u])
			continue;
		dfs2(v,u,false);
	}
	if(son[u])
		dfs2(son[u],u,true),Son=son[u];
	add(u,fa,1);
	Son=0;
//	printf("%d:\n",u);
//	for(re int i=1; i<=n; ++i)
//	{
//		for(re int j=0; j<26; ++j)
//			printf("%d ",cnt[i][j]);
//		putchar('\n');
//	}
//	putchar('\n');
//	for(re int i=1; i<=n; ++i)
//		printf("%d ",ans[i]);
//	putchar('\n');
	for(re int i=0; i<query[u].size(); ++i)
	{
		pair<int,int>&v=query[u][i];
		answer[v.first]=(ans[v.second]<=1);
	}
	if(!opt)
		add(u,fa,-1);
}
signed main()
{
//	freopen("ans.in","r",stdin);
//	freopen("ans.out","w",stdout);
	read(n,m);
	for(re int i=2; i<=n; ++i)
	{
		int fa;
		read(fa);
		add_edge(fa,i);
	}
	scanf("%s",str+1);
	for(re int i=1; i<=m; ++i)
	{
		int u,v;
		read(u,v);
		query[u].push_back(make_pair(i,v));
	}
	dfs1(1,0);
//	for(re int i=1; i<=n; ++i)
//		printf("%d ",son[i]);
//	putchar('\n');
	dfs2(1,0,false);
	for(re int i=1; i<=m; ++i)
		printf(answer[i]?"Yes\n":"No\n");
	return 0;
}


