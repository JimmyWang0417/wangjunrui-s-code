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
inline void clear(T*array,int l,int r,int val)
{
	memset(&array[l],val,sizeof(T)*(r-l+1));
}
using namespace std;
map<pair<int,int>,int>mp;
inline int query(int u, int v)
{
	if(mp[make_pair(u,v)])
		return mp[make_pair(u,v)];
	printf("? %d %d\n",u,v);
	fflush(stdout);
	int d;
	scanf("%d", &d);
	return mp[make_pair(u,v)]=mp[make_pair(v,u)]=d;
}
const int N=3005;
struct Edge
{
	int next,to;
} edge[N];
int head[N],num_edge;
inline void add_edge(int from,int to)
{
	edge[++num_edge].next=head[from];
	edge[num_edge].to=to;
	head[from]=num_edge;
}
int n,a[N],dep[N],size[N];
int down[N];
int ch[N][2];
#define lc(x) ch[x][0]
#define rc(x) ch[x][1]
inline void dfs(int x)
{
	if(!x)
		return;
	dfs(lc(x)),dfs(rc(x));
	size[x]=size[lc(x)]+size[rc(x)]+1;
	if(size[lc(x)]<size[rc(x)])
		swap(lc(x),rc(x));
	down[x]=(lc(x)?down[lc(x)]:x);
}
int fa[N];
inline void solve(int rt,int u)
{
	if(!lc(rt))
	{
		lc(rt)=u;
		fa[u]=rt;
		return;
	}
	int d=(dep[u]+dep[down[rt]]-query(down[rt],u))/2;
	int v=down[rt];
	while (dep[v]>d) v=fa[v];
	if(!rc(v))
	{
		rc(v)=u;
		fa[u]=v;
	}
	else
		solve(rc(v),u);
}
signed main()
{
	read(n);
	for(int i=2; i<=n; ++i)
		dep[i]=query(1,i);
	for(int i=1; i<=n; ++i)
		a[i]=i;
	sort(a+1,a+n+1,[](int x,int y)
	{
		return dep[x]<dep[y];
	});
	for(int i=2; i<=n; ++i)
	{
		dfs(1);
		solve(1,a[i]);
	}
	putchar('!');
	for(int i=2; i<=n; ++i)
		printf(" %d",fa[i]);
	putchar('\n');
	return 0;
}

