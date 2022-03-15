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
const int N=1e5+5;
int belong[N],block;
struct Queue
{
	int l,r,a,b,lca,id;
	inline bool operator <(const Queue&rhs)const
	{
		return belong[l]==belong[rhs.l]?(belong[l]&1?r<rhs.r:r>rhs.r):belong[l]<belong[rhs.l];
	}
} q[N];
int val[N];
bool vis[N];
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
int a[N];
int first[N],last[N],dfstime;
int sze[N],top[N],dep[N],fa[N],son[N];
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
inline void dfs2(int u,int _top)
{
	a[first[u]=++dfstime]=u;
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
inline int getlca(int x,int y)
{
	while(top[x]!=top[y])
	{
		if(dep[top[x]]<dep[top[y]])
			std::swap(x,y);
		x=fa[top[x]];
	}
	if(dep[x]>dep[y])
		std::swap(x,y);
	return x;
}
int cnt[N];
int ans,answer[N*2];
inline void add(int v)
{
	if(!(cnt[v]++))
		++ans;
}
inline void del(int v)
{
	if(!(--cnt[v]))
		--ans;
}
inline void update(int u)
{
	vis[u]?(del(val[u]),vis[u]=false):(add(val[u]),vis[u]=true);
}
signed main()
{
	int n,m;
	read(n,m);
	for(re int i=1; i<=n; ++i)
		read(val[i]);
	int root=1;
	for(re int i=1; i<=n; ++i)
	{
		int u,v;
		read(u,v);
		if(!u||!v)
			root=u|v;
		else
		{
			add_edge(u,v);
			add_edge(v,u);
		}
	}
	dfs1(root,0);
	dfs2(root,root);
	for(re int i=1; i<=m; ++i)
	{
		int u,v,lca;
		read(u,v,q[i].a,q[i].b);
		q[i].id=i;
		if(first[u]>first[v])
			std::swap(u,v);
		lca=getlca(u,v);
		if(u==lca)
		{
			q[i].l=first[u];
			q[i].r=first[v];
		}
		else
		{
			q[i].l=last[u];
			q[i].r=first[v];
			q[i].lca=lca;
		}
	}
	block=(int)sqrt(dfstime);
	for(re int i=1; i<=dfstime; ++i)
		belong[i]=(i-1)/block+1;
	std::sort(q+1,q+1+m);
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
		answer[q[i].id]=(ans-(cnt[q[i].a]&&cnt[q[i].b]&&q[i].a!=q[i].b));
		if(lca)
			update(lca);
	}
	for(re int i=1; i<=m; ++i)
		printf("%d\n",answer[i]);
	return 0;
}


