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
struct Tree
{
	int l,r;
	int size;
	int max;
} tree[N*100];
int cnt,root[N];
#define lc(rt) tree[rt].l
#define rc(rt) tree[rt].r
inline void pushup(int &rt)
{
	tree[rt].size=tree[lc(rt)].size+tree[rc(rt)].size;
	tree[rt].max=max(tree[lc(rt)].max,tree[rc(rt)].max);
}
inline void update(int &rt,int l,int r,int pos)
{
	if(!rt)
		rt=++cnt;
	++tree[rt].size;
//	printf("%d %d %d\n",l,r,pos);
	if(l==r)
	{
		++tree[rt].size;
		tree[rt].max=pos;
		return;
	}
	int mid=(l+r)>>1;
	if(pos<=mid)
		update(lc(rt),l,mid,pos);
	else
		update(rc(rt),mid+1,r,pos);
	pushup(rt);
}
inline int query(int &rt,int l,int r,int pos)
{
	if(l==r)
		return tree[rt].max;
	int mid=(l+r)>>1;
	if(pos<=mid)
		return query(lc(rt),l,mid,pos);
	else
		return max(tree[lc(rt)].max,query(rc(rt),mid+1,r,pos));
}
inline int merge(int x,int y)
{
	if(!x||!y)
		return x|y;
	int now=++cnt;
	lc(now)=merge(lc(x),lc(y));
	rc(now)=merge(rc(x),rc(y));
	pushup(now);
	return now;
}
int n;
char str[N];
struct SAM
{
	int fa,len;
	int ch[26];
} point[N];
int las=1,tot=1;
inline void insert(int c,int id)
{
	int p=las,np=las=++tot;
	update(root[np],1,n,id);
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
			int nq=++tot;
			point[nq]=point[q];
			point[q].fa=point[np].fa=nq;
			point[nq].len=point[p].len+1;
			for(; p&&point[p].ch[c]==q; p=point[p].fa)
				point[p].ch[c]=nq;
		}
	}
}
struct Edge
{
	int next,to;
} edge[N];
int head[N],num_edge;
inline void add_edge(int from,int to)
{
//	printf("%d %d\n",from,to);
	edge[++num_edge].next=head[from];
	edge[num_edge].to=to;
	head[from]=num_edge;
}
inline void dfs1(int u)
{
	for(int i=head[u]; i; i=edge[i].next)
	{
		int &v=edge[i].to;
		dfs1(v);
		root[u]=merge(root[u],root[v]);
	}
}
int ans,f[N];
int fa[N],len[N];
inline void dfs2(int u)
{
	if(u!=1)
		ans=max(ans,f[u]);
	for(int i=head[u]; i; i=edge[i].next)
	{
		int &v=edge[i].to;
		if(u==1)
		{
			f[v]=1;
			fa[v]=v;
			len[v]=1;
		}
		else
		{
			int a=tree[root[v]].max;
			int b=query(root[fa[u]],1,n,a-1);
			if(a-point[v].len<=b-len[u])
			{
				f[v]=f[u]+1;
				fa[v]=v;
				len[v]=a-b+len[u];
			}
			else
			{
				f[v]=f[u];
				fa[v]=fa[u];
				len[v]=len[u];
			}
		}
		dfs2(v);
	}
}
signed main()
{
	freopen("level.in","r",stdin);
	freopen("level.out","w",stdout);
	scanf("%s",str+1);
	n=(int)strlen(str+1);
	for(int i=1; i<=n; ++i)
		insert(str[i]-'a',i);
	for(int i=2; i<=tot; ++i)
		add_edge(point[i].fa,i);
//	for(int i=1; i<=tot; ++i)
//		printf("%d ",point[i].fa);
//	putchar('\n');
	dfs1(1);
	dfs2(1);
//	for(int i=1; i<=tot; ++i)
//		printf("%d %d %d\n",f[i],fa[i],len[i]);
	printf("%d\n",ans);
	return 0;
}


