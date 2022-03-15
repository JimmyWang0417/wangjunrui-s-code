#include <cstdio>
#include <vector>
#include <algorithm>
#define re register
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
const int N=3e5+5;
bool sortflag;
struct Point
{
	int x,y,r,id;
	inline bool operator <(const Point &rhs)const
	{
		return sortflag?x<rhs.x:y<rhs.y;
	}
} point[N];
inline bool cmp(Point &x,Point &y)
{
	return x.r>y.r||(x.r==y.r&&x.id<y.id);
}
struct Tree
{
	Point point;
	int l,r;
	int size;
	int maxx,maxy,minx,miny;
} tree[N];
int cnt,root;
#define lc(x) tree[x].l
#define rc(x) tree[x].r
inline int newnode(Point need)
{
	int rt=++cnt;
	tree[rt].point=need;
	tree[rt].size=1;
	tree[rt].maxx=need.x+need.r;
	tree[rt].minx=need.x-need.r;
	tree[rt].maxy=need.y+need.r;
	tree[rt].miny=need.y-need.r;
	return rt;
}
inline void pushup(int rt)
{
	tree[rt].size=tree[lc(rt)].size+tree[rc(rt)].size+1;

	tree[rt].maxx=max(tree[rt].point.x+tree[rt].point.r,max(tree[lc(rt)].maxx,tree[rc(rt)].maxx));
	tree[rt].maxy=max(tree[rt].point.y+tree[rt].point.r,max(tree[lc(rt)].maxy,tree[rc(rt)].maxy));

	tree[rt].minx=min(tree[rt].point.x-tree[rt].point.r,min(tree[lc(rt)].minx,tree[rc(rt)].minx));
	tree[rt].miny=min(tree[rt].point.y-tree[rt].point.r,min(tree[lc(rt)].miny,tree[rc(rt)].miny));
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
Point need;
inline bool check(Point &x,Point &y)
{
	return (1ll*(x.x-y.x)*(x.x-y.x)+1ll*(x.y-y.y)*(x.y-y.y)<=1ll*(x.r+y.r)*(x.r+y.r));
}
int ans[N];
int num;
inline void query(int &rt,bool flag)
{
	if(need.x+need.r<tree[rt].minx||need.x-need.r>tree[rt].maxx
	        ||need.y+need.r<tree[rt].miny||need.y-need.r>tree[rt].maxy)
		return;
	if(!ans[tree[rt].point.id]&&check(tree[rt].point,need))
		ans[tree[rt].point.id]=need.id;
	if(lc(rt))
		query(lc(rt),flag^1);
	if(rc(rt))
		query(rc(rt),flag^1);
}
const int INF=0x3f3f3f3f;
int main()
{
	tree[0].maxx=tree[0].maxy=-INF,tree[0].minx=tree[0].miny=INF;
	int n;
	read(n);
	for(re int i=1; i<=n; ++i)
	{
		read(point[i].x);
		read(point[i].y);
		read(point[i].r);
		point[i].id=i;
	}
	build(root,1,n,true);
	sort(point+1,point+1+n,cmp);
	for(re int i=1; i<=n; ++i)
	{
		need=point[i];
		if(!ans[need.id])
			query(root,true);
	}
	for(re int i=1; i<=n; ++i)
		printf("%d ",ans[i]);
	putchar('\n');
	return 0;
}
