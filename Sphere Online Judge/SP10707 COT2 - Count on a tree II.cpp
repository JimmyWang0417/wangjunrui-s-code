#include <bits/stdc++.h>
#define lowbit(x) (x&(-x))
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
const int N=8e4+5,M=1e5+5;
struct Edge
{
	int next,to;
	Edge(int _next=0,int _to=0):next(_next),to(_to) {}
} edge[N];
int head[N],num_edge;
inline void add_edge(int from,int to)
{
	edge[++num_edge]=Edge(head[from],to);
	head[from]=num_edge;
}
int sze[N],son[N],fa[N],dep[N];
inline void dfs1(int u,int _fa)
{
	dep[u]=dep[_fa]+1;
	fa[u]=_fa;
	sze[u]=1;
	for(re int i=head[u]; i; i=edge[i].next)
	{
		int &v=edge[i].to;
		if(v==_fa)
			continue;
		dfs1(v,u);
		sze[u]+=sze[v];
		if(sze[v]>sze[son[u]])
			son[u]=v;
	}
}
int top[N],last[N],begin[N],dfstime,a[N];
inline void dfs2(int u,int _top)
{
	a[begin[u]=++dfstime]=u;
	top[u]=_top;
	if(son[u])
		dfs2(son[u],_top);
	for(re int i=head[u]; i; i=edge[i].next)
	{
		int &v=edge[i].to;
		if(top[v])
			continue;
		dfs2(v,v);
	}
	a[last[u]=++dfstime]=u;
}
using std::swap;
inline int LCA(int u,int v)
{
	while(top[u]!=top[v])
	{
		if(dep[top[u]]<dep[top[v]])
			swap(u,v);
		u=fa[top[u]];
	}
	if(dep[u]>dep[v])
		swap(u,v);
	return u;
}
int n,m;
int val[N],p[N];
int block,belong[N];
struct Queue
{
	int l,r,lca,id;
	inline bool operator <(const Queue&rhs)const
	{
		return belong[l]==belong[rhs.l]?(belong[l]&1?r<rhs.r:r>rhs.r):belong[l]<belong[rhs.l];
	}
} q[M];
int answer[M],ans,cnt[N];
bool vis[N];
inline void update(int now)
{
	if(vis[now])
		ans-=!--cnt[val[now]];
	else
		ans+=!cnt[val[now]]++;
	vis[now]^=1;
}
using std::sort;
using std::unique;
using std::lower_bound;
signed main()
{
	read(n,m);

	for(re int i=1; i<=n; ++i)
	{
		read(val[i]);
		p[i]=val[i];
	}
	sort(p+1,p+1+n);
	int tot=(int)(unique(p+1,p+1+n)-p-1);
	for(re int i=1; i<=n; ++i)
		val[i]=(int)(lower_bound(p+1,p+1+tot,val[i])-p);

	for(re int i=1; i<n; ++i)
	{
		int u,v;
		read(u,v);
		add_edge(u,v);
		add_edge(v,u);
	}
	dfs1(1,0);
	dfs2(1,1);
//	for(re int i=1; i<=n; ++i)
//		printf(" %d %d\n",begin[i],last[i]);

	block=(int)sqrt(dfstime);
	for(re int i=1; i<=dfstime; ++i)
		belong[i]=(i-1)/block+1;
	for(re int i=1; i<=m; ++i)
	{
		q[i].id=i;
		int u,v;
		read(u,v);
		if(begin[u]>begin[v])
			swap(u,v);
		int lca=LCA(u,v);
		if(u==lca)
		{
			q[i].l=begin[u];
			q[i].r=begin[v];
		}
		else
		{
			q[i].l=last[u];
			q[i].r=begin[v];
			q[i].lca=lca;
		}
//		printf(" %d %d\n",q[i].l,q[i].r);
	}
	sort(q+1,q+1+m);
	int l=1,r=0;
	for(re int i=1; i<=m; ++i)
	{
		const int &ql=q[i].l,&qr=q[i].r,&lca=q[i].lca;
		while(ql<l)
			update(a[--l]);
		while(ql>l)
			update(a[l++]);
		while(qr<r)
			update(a[r--]);
		while(qr>r)
			update(a[++r]);
		if(lca)
			update(lca);
		answer[q[i].id]=ans;
		if(lca)
			update(lca);
	}
	for(re int i=1; i<=m; ++i)
		printf("%d\n",answer[i]);
	return 0;
}


