#include <cstdio>
#include <algorithm>
#define re register
#define ll long long
#define rep(i,a,b) for(re int i=a;i<=b;++i)
#define per(i,a,b) for(re int i=a;i>=b;--i)
using namespace std;
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
const int N=8e4+5;
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
int dfn[N],size[N],dep[N],son[N],fa[N],top[N];
inline void dfs1(int u,int _fa)
{
	size[u]=1;
	dep[u]=dep[_fa]+1;
	fa[u]=_fa;
	for(re int i=head[u]; i; i=edge[i].next)
	{
		int &v=edge[i].to;
		if(v==_fa)
			continue;
		dfs1(v,u);
		size[u]+=size[v];
		if(size[v]>size[son[u]])
			son[u]=v;
	}
}
int dfstime;
inline void dfs2(int u,int topf)
{
	top[u]=topf;
	dfn[u]=++dfstime;
	if(!son[u])
		return;
	dfs2(son[u],topf);
	for(re int i=head[u]; i; i=edge[i].next)
	{
		int &v=edge[i].to;
		if(top[v])
			continue;
		dfs2(v,v);
	}
}
struct Tree
{
	int size;
	int l,r;
} tree[N*1000];
int cnt;
#define lc(x) tree[x].l
#define rc(x) tree[x].r
inline void update(int &rt,int l,int r,int pos,int val)
{
	if(!rt)
		rt=++cnt;
	tree[rt].size+=val;
	if(l==r)
		return;
	int mid=(l+r)>>1;
	if(pos<=mid)
		update(lc(rt),l,mid,pos,val);
	else
		update(rc(rt),mid+1,r,pos,val);
}
int root[N];
int rtadd[1005],rtdec[1005],totadd,totdec;
#define lowbit(x) (x&(-x))
inline void update(int pos,int val,int v)
{
	for(re int i=pos; i<=dfstime; i+=lowbit(i))
		update(root[i],0,1e8,val,v);
}
inline int getcnt()
{
	int ans=0;
	for(re int i=1; i<=totadd; ++i)
		ans+=tree[lc(rtadd[i])].size;
	for(re int i=1; i<=totdec; ++i)
		ans-=tree[lc(rtdec[i])].size;
	return ans;
}
inline void rtleft()
{
	for(re int i=1; i<=totadd; ++i)
		rtadd[i]=lc(rtadd[i]);
	for(re int i=1; i<=totdec; ++i)
		rtdec[i]=lc(rtdec[i]);
}
inline void rtright()
{
	for(re int i=1; i<=totadd; ++i)
		rtadd[i]=rc(rtadd[i]);
	for(re int i=1; i<=totdec; ++i)
		rtdec[i]=rc(rtdec[i]);
}
inline int query(int l,int r,int rk)
{
	if(l==r)
		return l;
	int mid=(l+r)>>1,sum=getcnt();
	if(rk<=sum)
	{
		rtleft();
		return query(l,mid,rk);
	}
	else
	{
		rtright();
		return query(mid+1,r,rk-sum);
	}

}
inline void init(int l,int r)
{
	for(re int i=r; i; i-=lowbit(i))
		rtadd[++totadd]=root[i];
	for(re int i=l-1; i; i-=lowbit(i))
		rtdec[++totdec]=root[i];
}
inline void query(int x,int y)
{
	totadd=totdec=0;
	while(top[x]!=top[y])
	{
		if(dep[top[x]]<dep[top[y]])
			swap(x,y);
		init(dfn[top[x]],dfn[x]);
		x=fa[top[x]];
	}
	if(dep[x]>dep[y])
		swap(x,y);
	init(dfn[x],dfn[y]);
}
int n,m,a[N];
signed main()
{
	read(n,m);
	for(re int i=1; i<=n; ++i)
		read(a[i]);
	for(re int i=1; i<n; ++i)
	{
		int u,v;
		read(u,v);
		add_edge(u,v);
		add_edge(v,u);
	}
	dfs1(1,0);
	dfs2(1,1);
	for(re int i=1; i<=n; ++i)
		update(dfn[i],a[i],1);
	while(m--)
	{
		int k,x,y;
		read(k,x,y);
		if(!k)
		{
			update(dfn[x],a[x],-1);
			update(dfn[x],a[x]=y,1);
		}
		else
		{
			query(x,y);
			int ans=0;
			for(re int i=1; i<=totadd; ++i)
				ans+=tree[(rtadd[i])].size;
			for(re int i=1; i<=totdec; ++i)
				ans-=tree[(rtdec[i])].size;
			if(ans<k)
				printf("invalid request!\n");
			else
				printf("%d\n",query(0,1e8,ans-k+1));
		}
	}
	return 0;
}

