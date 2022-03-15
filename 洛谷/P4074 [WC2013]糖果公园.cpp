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
const int N=2e5+5;
int n,m,Q;
int V[N],W[N];
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
int top[N],last[N],first[N],dfstime,a[N];
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
using std::swap;
inline int LCA(int x,int y)
{
	while(top[x]!=top[y])
	{
		if(dep[top[x]]<dep[top[y]])
			swap(x,y);
		x=fa[top[x]];
	}
	if(dep[x]>dep[y])
		swap(x,y);
	return x;
}
int block,belong[N];
int color[N];
struct Queue
{
	int l,r,lca,id,t;
	inline bool operator <(const Queue&rhs)const
	{
		return (belong[l]==belong[rhs.l]?(belong[r]==belong[rhs.r]?(belong[r]&1?t<rhs.t:t>rhs.t):r<rhs.r):l<rhs.l);
	}
} q[N];
struct Change
{
	int pos,val;
} c[N];
bool vis[N];
ll ans,answer[N];
int cnt[N];
inline void add(int val)
{
	ans+=1ll*V[val]*W[++cnt[val]];
}
inline void del(int val)
{
	ans-=1ll*V[val]*W[cnt[val]--];
}
inline void update(int u)
{
	vis[u]?del(color[u]):add(color[u]);
	vis[u]^=1;
//	printf(" %d %d\n",u,color[u]);
}
signed main()
{
	read(n,m,Q);
	for(re int i=1; i<=m; ++i)
		read(V[i]);
	for(re int i=1; i<=n; ++i)
		read(W[i]);
	for(re int i=1; i<n; ++i)
	{
		int u,v;
		read(u,v);
		add_edge(u,v);
		add_edge(v,u);
	}
	dfs1(1,0),dfs2(1,1);
	for(re int i=1; i<=n; ++i)
		read(color[i]);
	int tim=0,ct=0;
	for(re int i=1; i<=Q; ++i)
	{
		int opt,x,y;
		read(opt,x,y);
		if(opt==0)
		{
			++tim;
			c[tim].pos=x;
			c[tim].val=y;
		}
		else if(opt==1)
		{
			int lca=LCA(x,y);
			if(first[x]>first[y])
				swap(x,y);
//			printf("-%d %d %d\n",x,y,lca);
//			printf("---%d %d\n",first[x],first[y]);
			++ct;
			q[ct].id=ct;
			q[ct].t=tim;
			if(x==lca)
			{
				q[ct].l=first[x];
				q[ct].r=first[y];
			}
			else
			{
				q[ct].l=last[x];
				q[ct].r=first[y];
				q[ct].lca=lca;
			}
		}
	}
	block=(int)pow(dfstime,2.0/3.0);
	for(re int i=1; i<=dfstime; ++i)
		belong[i]=(i-1)/block+1;
	std::sort(q+1,q+1+ct);
	int l=1,r=0,t=0;
//	for(re int i=1; i<=dfstime; ++i)
//		printf(" %d",a[i]);
//	putchar('\n');
	for(re int now=1; now<=ct; ++now)
	{
		const int &ql=q[now].l,&qr=q[now].r,&lca=q[now].lca,&qt=q[now].t;
//		printf(" %d %d %d %d %d\n",ql,qr,lca,qt,q[now].id);
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
		while(qt>t)
		{
			++t;
			if(vis[c[t].pos])
			{
				del(color[c[t].pos]);
				add(c[t].val);
			}
			swap(color[c[t].pos],c[t].val);
		}
		while(qt<t)
		{
			if(vis[c[t].pos])
			{
				del(color[c[t].pos]);
				add(c[t].val);
			}
			swap(color[c[t].pos],c[t].val);
			--t;
		}
//		printf("%d %d %d\n",l,r,t);
		answer[q[now].id]=ans;
		if(lca)
			update(lca);
	}
	for(re int i=1; i<=ct; ++i)
		printf("%lld\n",answer[i]);
	return 0;
}
