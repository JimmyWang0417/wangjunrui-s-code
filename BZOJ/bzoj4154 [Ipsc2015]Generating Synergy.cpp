#include <cstdio>
#include <cstring>
#include <algorithm>
#define re register
#define ll long long
using namespace std;

template <typename T>
inline void read(T&x)
{
	x=0;
	char s=(char)getchar();
	bool flag=false;
	while(!(s>='0'&&s<='9'))
	{
		if(s=='-')
			flag=true;
		s=(char)getchar();
	}
	while(s>='0'&&s<='9')
	{
		x=(x<<1)+(x<<3)+s-'0';
		s=(char)getchar();
	}
	if(flag)
		x=(~x)+1;
}
const int N=1e5+5;
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

int dep[N],ed[N],dfn[N],dfstime;
inline void dfs(int u)
{
	dfn[u]=++dfstime;
	for(re int i=head[u]; i; i=edge[i].next)
	{
		int &v=edge[i].to;
		dep[v]=dep[u]+1;
		dfs(v);
	}
	ed[u]=dfstime;
}
bool sortflag;
struct Point
{
	int x,y;
	inline bool operator < (const Point &rhs)const
	{
		return sortflag?x<rhs.x:y<rhs.y;
	}
} point[N],need;
struct Tree
{
	Point point;
	int l,r;
	int maxx,minx;
	int maxy,miny;
	int color;
	int lazy;
} tree[N];
int cnt,root;
#define lc(x) tree[x].l
#define rc(x) tree[x].r
inline int newnode(const Point &rhs)
{
	int rt=++cnt;
	tree[rt].maxx=tree[rt].minx=rhs.x;
	tree[rt].maxy=tree[rt].miny=rhs.y;
	tree[rt].color=1;
	tree[rt].lazy=-1;
	tree[rt].point=rhs;
	lc(rt)=rc(rt)=0;
	return rt;
}
inline void pushup(int rt)
{
	if(lc(rt))
	{
		tree[rt].maxx=max(tree[rt].maxx,tree[lc(rt)].maxx);
		tree[rt].maxy=max(tree[rt].maxy,tree[lc(rt)].maxy);
		tree[rt].minx=min(tree[rt].minx,tree[lc(rt)].minx);
		tree[rt].miny=min(tree[rt].miny,tree[lc(rt)].miny);
	}
	if(rc(rt))
	{
		tree[rt].maxx=max(tree[rt].maxx,tree[rc(rt)].maxx);
		tree[rt].maxy=max(tree[rt].maxy,tree[rc(rt)].maxy);
		tree[rt].minx=min(tree[rt].minx,tree[rc(rt)].minx);
		tree[rt].miny=min(tree[rt].miny,tree[rc(rt)].miny);
	}
}
inline void pushdown(int rt)
{
	if(tree[rt].lazy==-1)
		return;
	if(lc(rt))
		tree[lc(rt)].color=tree[lc(rt)].lazy=tree[rt].lazy;
	if(rc(rt))
		tree[rc(rt)].color=tree[rc(rt)].lazy=tree[rt].lazy;
	tree[rt].lazy=-1;
}
inline void build(int &rt,int l,int r,bool flag)
{
	int mid=(l+r)>>1;
	sortflag=flag;
	nth_element(point+l,point+mid,point+r+1);
	rt=newnode(point[mid]);
	if(l<mid)
		build(lc(rt),l,mid-1,flag^1);
	if(mid<r)
		build(rc(rt),mid+1,r,flag^1);
	pushup(rt);
}
inline void change(int rt,int x1,int y1,int x2,int y2,int val)
{
	if(!rt||x1>tree[rt].maxx||tree[rt].minx>x2||y1>tree[rt].maxy||tree[rt].miny>y2)
		return;
	if(x1<=tree[rt].minx&&tree[rt].maxx<=x2&&y1<=tree[rt].miny&&tree[rt].maxy<=y2)
	{
		tree[rt].color=tree[rt].lazy=val;
		return;
	}
	pushdown(rt);
	if(x1<=tree[rt].point.x&&tree[rt].point.x<=x2&&y1<=tree[rt].point.y&&tree[rt].point.y<=y2)
		tree[rt].color=val;
	change(lc(rt),x1,y1,x2,y2,val);
	change(rc(rt),x1,y1,x2,y2,val);
}
inline int query(int rt)
{
	if(!rt||need.x>tree[rt].maxx||tree[rt].minx>need.x||need.y>tree[rt].maxy||tree[rt].miny>need.y)
		return -1;
	if(tree[rt].point.x==need.x&&tree[rt].point.y==need.y)
		return tree[rt].color;
	pushdown(rt);
	return max(query(lc(rt)),query(rc(rt)));
}
int ans,n,q;
const int mod=1e9+7;
inline void solve(int x)
{
	int a,l,c;
	read(a),read(l),read(c);
	if(!c)
	{
		need.x=dfn[a],need.y=dep[a];
//		printf(" %d %d\n",need.x,need.y);
//		printf("%d\n",query(root));
		ans=(ans+1ll*x*query(root))%mod;
//		for(re int i=1; i<=n; ++i)
//			printf("%d %d\n%d %d %d %d %d %d %d %d\n",tree[i].point.x,tree[i].point.y,tree[i].maxx,tree[i].maxy,tree[i].minx,tree[i].miny,tree[i].color,tree[i].lazy,tree[i].l,tree[i].r);
	}
	else
	{
//		printf(" %d %d %d %d\n",dfn[a],dep[a],ed[a],dep[a]+l);
		change(root,dfn[a],dep[a],ed[a],dep[a]+l,c);
//		for(re int i=1; i<=n; ++i)
//			printf("%d %d\n%d %d %d %d %d %d %d %d\n",tree[i].point.x,tree[i].point.y,tree[i].maxx,tree[i].maxy,tree[i].minx,tree[i].miny,tree[i].color,tree[i].lazy,tree[i].l,tree[i].r);
	}
//	for(re int i=1; i<=n; ++i)
//		printf("%d %d\n%d %d %d %d %d %d %d %d\n",tree[i].point.x,tree[i].point.y,tree[i].maxx,tree[i].maxy,tree[i].minx,tree[i].miny,tree[i].color,tree[i].lazy,tree[i].l,tree[i].r);
}
inline void work()
{
	int c;
	read(n),read(c),read(q);
	memset(head+1,num_edge=cnt=ans=0,n*sizeof(int));
	for(re int i=2; i<=n; ++i)
	{
		int fa;
		read(fa);
		add_edge(fa,i);
	}
	dfs(1);
	for(re int i=1; i<=n; ++i)
	{
//		printf(" %d %d %d\n",dfn[i],ed[i],dep[i]);
		point[i].x=dfn[i];
		point[i].y=dep[i];
	}
	build(root,1,n,true);
//	for(re int i=1; i<=n; ++i)
//		printf("%d %d %d %d\n",tree[i].maxx,tree[i].maxy,tree[i].minx,tree[i].miny);
//	printf("%d\n",root);
	for(re int i=1; i<=q; ++i)
		solve(i);
	printf("%d\n",ans);
}
int main()
{
	int T;
	read(T);
	while(T--)
		work();
}
