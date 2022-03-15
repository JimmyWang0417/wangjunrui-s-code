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
const int N=6e5+5;
struct node
{
	int fa,len;
	map<int,int>ch;
} point[N];
int cnt=1;
int samroot[N];
inline int insert(int p,int c)
{
	int np=++cnt;
	point[np].len=point[p].len+1;
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
			int nq=++cnt;
			point[nq]=point[q];
			point[q].fa=point[np].fa=nq;
			point[nq].len=point[p].len+1;
			for(; p&&point[p].ch[c]==q; p=point[p].fa)
				point[p].ch[c]=nq;
		}
	}
	return np;
}
struct Edge
{
	int next,to,dis;
} edge[N];
int head[N],num_edge;
int root[N];
inline void add_edge(int from,int to,int dis)
{
	edge[++num_edge].next=head[from];
	edge[num_edge].to=to;
	edge[num_edge].dis=dis;
	head[from]=num_edge;
}
inline void dfs1(int u)
{
	for(int i=head[u]; i; i=edge[i].next)
	{
		int &v=edge[i].to;
		samroot[v]=insert(samroot[u],edge[i].dis);
		dfs1(v);
	}
}
vector<int>g[N];
int fa[N][25];
int dfn[N],rk[N];
int dep[N];
inline void dfs2(int u,int _fa)
{
	dfn[++cnt]=u;
	rk[u]=cnt;
	fa[u][0]=_fa;
	for(int i=0; i<20; ++i)
		fa[u][i+1]=fa[fa[u][i]][i];
	for(auto v:g[u])
	{
		dep[v]=dep[u]+1;
		dfs2(v,u);
	}
}
inline int LCA(int u,int v)
{
	u=dfn[u],v=dfn[v];
//	printf("%d %d\n",u,v);
	if(dep[u]<dep[v])
		swap(u,v);
	for(int i=20; i>=0; --i)
		if(dep[fa[u][i]]>=dep[v])
			u=fa[u][i];
	if(u==v)
		return u;
	for(int i=20; i>=0; --i)
		if(fa[u][i]!=fa[v][i])
		{
			u=fa[u][i];
			v=fa[v][i];
		}
	return fa[u][0];
}
struct Tree
{
	int l,r;
	int begin,end;
} tree[N*40];
int tot;
#define lc(x) tree[x].l
#define rc(x) tree[x].r
inline void pushup(int rt)
{
	if(lc(rt))
		tree[rt].begin=tree[lc(rt)].begin;
	else
		tree[rt].begin=tree[rc(rt)].begin;
	if(rc(rt))
		tree[rt].end=tree[rc(rt)].end;
	else
		tree[rt].end=tree[lc(rt)].end;
}
inline void update(int &rt,int l,int r,int pos)
{
	if(!rt)
		rt=++tot;
	tree[rt].begin=tree[rt].end=pos;
	if(l==r)
		return;
	int mid=(l+r)>>1;
	if(pos<=mid)
		update(lc(rt),l,mid,pos);
	else
		update(rc(rt),mid+1,r,pos);
}
inline int merge(int &x,int y,int l,int r)
{
	if(!x||!y)
	{
		x=x|y;
		return 0;
	}
	if(l==r)
		return 0;
	int mid=(l+r)>>1;
	int ans=max(merge(lc(x),lc(y),l,mid),merge(rc(x),rc(y),mid+1,r));
	if(lc(x)&&rc(x))
		ans=max(ans,point[LCA(tree[lc(x)].end,tree[rc(x)].begin)].len);
	pushup(x);
	return ans;
}
int dp[N];
int ans;
inline void dfs3(int u,int _dep)
{
	update(root[u],1,cnt,rk[samroot[u]]);
	for(int i=head[u]; i; i=edge[i].next)
	{
		int &v=edge[i].to;
		dfs3(v,_dep+1);
		dp[u]=max(dp[u],dp[v]);
		dp[u]=max(dp[u],merge(root[u],root[v],1,cnt));
	}
	ans=max(ans,dp[u]+_dep);
}
int n;
signed main()
{
	freopen("recollection.in","r",stdin),freopen("recollection.out","w",stdout);
	read(n);
	for(int i=2; i<=n; ++i)
	{
		int v,w;
		read(v,w);
		add_edge(v,i,w);
	}
	samroot[1]=1;
	dfs1(1);
	for(int i=2; i<=cnt; ++i)
		g[point[i].fa].push_back(i);
	cnt=0;
	dfs2(1,0);
//	for(int i=1; i<=n; ++i)
//		printf(" %d %d\n",dfn[i],rk[i]);
	dfs3(1,0);
//	for(int i=1; i<=n; ++i)
//		printf("%d ",dp[i]);
//	putchar('\n');
	printf("%d\n",ans);
	return 0;
}


