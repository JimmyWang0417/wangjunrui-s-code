#include <bits/stdc++.h>
#define int ll
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
const int N=2e5+5;
const ll INF=(1ull<<63)-1;
struct Edge
{
	int next,to;
} edge[N*2];
int head[N],num_edge;
inline void add_edge(int from,int to)
{
	edge[++num_edge].next=head[from];
	edge[num_edge].to=to;
	head[from]=num_edge;
}
struct Tree
{
	int ch[2],fa;
	int size;

	ll tag;
	ll val;
	ll d,min;
	bool leaf;
} tree[N];
#define lc(x) tree[x].ch[0]
#define rc(x) tree[x].ch[1]
#define fa(x) tree[x].fa
#define rev(x) tree[x].rev
ll f[N];
int father[N];
inline void dfs(int u,int _fa)
{
	tree[u].leaf=true;
	tree[u].d=tree[u].val;
	ll sum=0;
	for(int i=head[u]; i; i=edge[i].next)
	{
		int &v=edge[i].to;
		if(v==_fa)
			continue;
		dfs(v,u);
		tree[u].leaf=false;
		sum+=f[v];
	}
	tree[u].d-=sum;
	f[u]=tree[u].leaf?tree[u].val:min(tree[u].val,sum);
	tree[u].min=tree[u].d;
	father[u]=fa(u)=_fa;
}
inline bool check(int x)
{
	return rc(fa(x))==x;
}
inline bool nroot(int x)
{
	return lc(fa(x))==x||rc(fa(x))==x;
}
inline void addtag(int x,ll y)
{
	tree[x].tag+=y;
	tree[x].d+=y;
	tree[x].min+=y;
}
inline void pushup(int x)
{
	tree[x].min=min(tree[x].d,min(tree[lc(x)].min,tree[rc(x)].min));
}
inline void pushdown(int x)
{
	if(tree[x].tag)
	{
		if(lc(x))
			addtag(lc(x),tree[x].tag);
		if(rc(x))
			addtag(rc(x),tree[x].tag);
		tree[x].tag=0;
	}
}
inline void rotate(int x)
{
	int y=fa(x),z=fa(y),k=check(x),w=tree[x].ch[k^1];
	if(nroot(y))
		tree[z].ch[check(y)]=x;
	tree[y].ch[k]=w;
	tree[x].ch[k^1]=y;
	if(w)
		fa(w)=y;
	fa(y)=x;
	fa(x)=z;
	pushup(y),pushup(x);
}
int st[N];
inline void splay(int x)
{
	int top;
	st[top=1]=x;
	for(re int y=x; nroot(y); y=fa(y))
		st[++top]=fa(y);
	while(top)
		pushdown(st[top--]);
	while(nroot(x))
	{
		if(nroot(fa(x)))
			rotate(check(x)==check(fa(x))?fa(x):x);
		rotate(x);
	}
}
inline void access(int x)
{
	for(int y=0; x; x=fa(y=x))
	{
		splay(x);
		rc(x)=y;
		pushup(x);
	}
}
inline int query(int x,ll k)
{
	while(x)
	{
		pushdown(x);
		if(tree[rc(x)].min<k)
			x=rc(x);
		else if(tree[x].d<k)
			return x;
		else x=lc(x);
	}
	return x;
}
inline void modify(int x,ll v)
{
	access(x);
	splay(x);
	addtag(x,v);
}
inline void change(int x,ll y)
{
	splay(x);
	tree[x].val+=y;
	ll k=tree[x].leaf?y:(tree[x].d+y<0?y:-tree[x].d);
	tree[x].d+=y;
	pushup(x);
	if(!tree[x].leaf&&tree[x].d>=y)
		return;
	x=father[x];
	while(x)
	{
		access(x);
		splay(x);
		int up=query(x,k);
		ll upval=tree[up].d;
//		printf("%d %lld\n",up,upval);
		modify(x,-k);
//		printf("ok\n");
		if(father[up])
			modify(father[up],k);
		x=father[up],k=upval;
		if(k<=0)
			return;
	}
}
int n,m;
signed main()
{
	freopen("lct.in","r",stdin);
	freopen("lct.out","w",stdout);
	tree[0].min=tree[0].d=INF;
	read(n);
	for(int i=1; i<=n; ++i)
		read(tree[i].val);
	for(int i=1; i<n; ++i)
	{
		int u,v;
		read(u,v);
		add_edge(u,v);
		add_edge(v,u);
	}
	dfs(1,0);
//	for(int i=1; i<=n; ++i)
//		printf("%d ",tree[i].d);
//	putchar('\n');
	read(m);
	for(int i=1; i<=m; ++i)
	{
		char opt[3];
		scanf("%s",opt);
		int x,y;
		read(x);
		if(opt[0]=='Q')
		{
			splay(x);
			printf("%lld\n",tree[x].leaf?tree[x].val:min(tree[x].val,tree[x].val-tree[x].d));
		}
		else
		{
			read(y);
			change(x,y);
		}
//		for(int j=1; j<=n; ++j)
//			printf("%d ",tree[j].d);
//		putchar('\n');
	}
	return 0;
}

