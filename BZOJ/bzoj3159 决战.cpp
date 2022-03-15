#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#define re register
#define ll long long
template <typename T>
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
using std::swap;
using std::min;
using std::max;
const int N=50005,INF=0x3f3f3f3f;
struct Tree
{
	int l,r,size;
	int val,key;
	int max,min;
	ll sum;
	int tag;
	bool reverse;
} tree[N];
#define lc(x) tree[x].l
#define rc(x) tree[x].r
int cnt,root[N];
inline int newnode(int val)
{
	int now=++cnt;
	tree[now].key=rand();
	tree[now].sum=tree[now].val=tree[now].max=tree[now].min=val;
	tree[now].size=1;
	return now;
}
inline void pushup(int now)
{
	tree[now].size=tree[lc(now)].size+tree[rc(now)].size+1;
	tree[now].sum=tree[lc(now)].sum+tree[rc(now)].sum+tree[now].val;
	tree[now].max=max(tree[now].val,max(tree[lc(now)].max,tree[rc(now)].max));
	tree[now].min=min(tree[now].val,min(tree[lc(now)].min,tree[rc(now)].min));
}
inline void tag(int now,int val)
{
	tree[now].sum+=1ll*tree[now].size*val;
	tree[now].val+=val;
	tree[now].tag+=val;
	tree[now].max+=val;
	tree[now].min+=val;
}
inline void pushdown(int now)
{
	if(tree[now].reverse)
	{
		swap(lc(now),rc(now));
		if(lc(now))
			tree[lc(now)].reverse^=1;
		if(rc(now))
			tree[rc(now)].reverse^=1;
		tree[now].reverse=false;
	}
	if(tree[now].tag)
	{
		if(lc(now))
			tag(lc(now),tree[now].tag);
		if(rc(now))
			tag(rc(now),tree[now].tag);
		tree[now].tag=0;
	}
}
inline void split(int now,int size,int &x,int &y)
{
	if(!now)
		x=y=0;
	else
	{
		pushdown(now);
		if(size>tree[lc(now)].size)
		{
			x=now;
			split(rc(now),size-tree[lc(now)].size-1,rc(now),y);
		}
		else
		{
			y=now;
			split(lc(now),size,x,lc(now));
		}
		pushup(now);
	}
}
inline int merge(int x,int y)
{
	if(!x||!y)
		return x|y;
	if(tree[x].key>tree[y].key)
	{
		pushdown(x);
		rc(x)=merge(rc(x),y);
		pushup(x);
		return x;
	}
	else
	{
		pushdown(y);
		lc(y)=merge(x,lc(y));
		pushup(y);
		return y;
	}
}
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
int size[N],son[N],dep[N],fa[N];
inline void dfs1(int u,int _fa)
{
	fa[u]=_fa;
	dep[u]=dep[_fa]+1;
	size[u]=1;
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
int top[N],dfn[N],dfstime;
inline void dfs2(int u,int topf)
{
	dfn[u]=++dfstime;
	top[u]=topf;
	root[topf]=merge(root[topf],newnode(0));
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
inline int querymax(int x,int y)
{
	int ans=-INF;
	while(top[x]!=top[y])
	{
		if(dep[top[x]]<dep[top[y]])
			swap(x,y);
		int rtx,rty;
		split(root[top[x]],dfn[x]-dfn[top[x]]+1,rtx,rty);
		ans=max(ans,tree[rtx].max);
		root[top[x]]=merge(rtx,rty);
		x=fa[top[x]];
	}
	if(dep[x]>dep[y])
		swap(x,y);
	int rtx,rty,rtz;
	split(root[top[x]],dfn[x]-dfn[top[x]],rtx,rty);
	split(rty,dfn[y]-dfn[x]+1,rty,rtz);
	ans=max(ans,tree[rty].max);
	root[top[x]]=merge(rtx,merge(rty,rtz));
	return ans;
}
inline int querymin(int x,int y)
{
	int ans=INF;
	while(top[x]!=top[y])
	{
		if(dep[top[x]]<dep[top[y]])
			swap(x,y);
		int rtx,rty;
		split(root[top[x]],dfn[x]-dfn[top[x]]+1,rtx,rty);
		ans=min(ans,tree[rtx].min);
		root[top[x]]=merge(rtx,rty);
		x=fa[top[x]];
	}
	if(dep[x]>dep[y])
		swap(x,y);
	int rtx,rty,rtz;
	split(root[top[x]],dfn[x]-dfn[top[x]],rtx,rty);
	split(rty,dfn[y]-dfn[x]+1,rty,rtz);
	ans=min(ans,tree[rty].min);
	root[top[x]]=merge(rtx,merge(rty,rtz));
	return ans;
}
inline ll querysum(int x,int y)
{
	ll ans=0;
	while(top[x]!=top[y])
	{
		if(dep[top[x]]<dep[top[y]])
			swap(x,y);
		int rtx,rty;
		split(root[top[x]],dfn[x]-dfn[top[x]]+1,rtx,rty);
		ans+=tree[rtx].sum;
		root[top[x]]=merge(rtx,rty);
		x=fa[top[x]];
	}
	if(dep[x]>dep[y])
		swap(x,y);
	int rtx,rty,rtz;
	split(root[top[x]],dfn[x]-dfn[top[x]],rtx,rty);
	split(rty,dfn[y]-dfn[x]+1,rty,rtz);
	ans+=tree[rty].sum;
	root[top[x]]=merge(rtx,merge(rty,rtz));
	return ans;
}
inline void change(int x,int y,int val)
{
	while(top[x]!=top[y])
	{
		if(dep[top[x]]<dep[top[y]])
			swap(x,y);
		int rtx,rty;
		split(root[top[x]],dfn[x]-dfn[top[x]]+1,rtx,rty);
		tag(rtx,val);
		root[top[x]]=merge(rtx,rty);
		x=fa[top[x]];
	}
	if(dep[x]>dep[y])
		swap(x,y);
	int rtx,rty,rtz;
	split(root[top[x]],dfn[x]-dfn[top[x]],rtx,rty);
	split(rty,dfn[y]-dfn[x]+1,rty,rtz);
	tag(rty,val);
	root[top[x]]=merge(rtx,merge(rty,rtz));
}
inline void reverse(int _x,int _y)
{
	int rootl=0,rootr=0;
	int x,y;
	x=_x,y=_y;
	while(top[x]!=top[y])
	{
		int rt;
		if(dep[top[x]]>dep[top[y]])
		{
			split(root[top[x]],dfn[x]-dfn[top[x]]+1,rt,root[top[x]]);
			rootl=merge(rt,rootl);
			x=fa[top[x]];
		}
		else
		{
			split(root[top[y]],dfn[y]-dfn[top[y]]+1,rt,root[top[y]]);
			rootr=merge(rt,rootr);
			y=fa[top[y]];
		}
	}
	tree[rootl].reverse^=1;
	int sze=tree[rootl].size;
	if(dep[x]>dep[y])
		swap(x,y);
	int rtx,rty,rtz;
	split(root[top[x]],dfn[x]-dfn[top[x]],rtx,rty);
	split(rty,dfn[y]-dfn[x]+1,rty,rtz);
	int _root=merge(rootl,merge(rty,rootr));
	tree[_root].reverse^=1;
	split(_root,sze,rootl,_root);
	tree[rootl].reverse^=1;
	x=_x,y=_y;
	while(top[x]!=top[y])
	{
		int rt;
		if(dep[top[x]]>dep[top[y]])
		{
			split(rootl,tree[rootl].size-(dfn[x]-dfn[top[x]]+1),rootl,rt);
			root[top[x]]=merge(rt,root[top[x]]);
			x=fa[top[x]];
		}
		else
		{
			split(_root,tree[_root].size-(dfn[y]-dfn[top[y]]+1),_root,rt);
			root[top[y]]=merge(rt,root[top[y]]);
			y=fa[top[y]];
		}
	}
	root[top[x]]=merge(rtx,merge(_root,rtz));
}
int n,m,R;
int main()
{
	srand(123456),srand(rand()),srand(rand());
	tree[0].max=-INF,tree[0].min=INF;
	read(n),read(m),read(R);
	for(re int i=1; i<n; ++i)
	{
		int x,y;
		read(x),read(y);
		add_edge(x,y);
		add_edge(y,x);
	}
	dfs1(R,0);
	dfs2(R,R);
	while(m--)
	{
		char opt[10];
		scanf("%s",opt);
		if(opt[2]=='c')
		{
			int x,y,w;
			read(x),read(y),read(w);
			change(x,y,w);
		}
		else if(opt[2]=='m')
		{
			int x,y;
			read(x),read(y);
			printf("%lld\n",querysum(x,y));
		}
		else if(opt[2]=='j')
		{
			int x,y;
			read(x),read(y);
			printf("%d\n",querymax(x,y));
		}
		else if(opt[2]=='n')
		{
			int x,y;
			read(x),read(y);
			printf("%d\n",querymin(x,y));
		}
		else if(opt[2]=='v')
		{
			int x,y;
			read(x),read(y);
			reverse(x,y);
		}
//		for(re int i=1; i<=n; ++i)
//			printf(" %d %d %d\n",tree[root[i]].max,tree[root[i]].min,tree[root[i]].sum);
	}
	return 0;
}
