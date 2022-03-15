#include <cstdio>
#include <algorithm>
#define re register
#define ll long long
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
const int N=1e5+5,INF=0x3f3f3f3f;
bool sortflag;
struct Point
{
	int x,y,val;
	inline bool operator < (const Point &rhs)const
	{
		return sortflag?x<rhs.x:y<rhs.y;
	}
} point[N],need;
struct Tree
{
	Point point;
	int l,r;
	int maxx,maxy,minx,miny;
	ll sum;
} tree[N];
#define lc(rt) tree[rt].l
#define rc(rt) tree[rt].r
int cnt,root;
inline int newnode(const Point &rhs)
{
	int rt=++cnt;
	tree[rt].point=rhs;
	tree[rt].maxx=tree[rt].minx=rhs.x;
	tree[rt].maxy=tree[rt].miny=rhs.y;
	tree[rt].sum=rhs.val;
	return rt;
}
inline void pushup(int rt)
{
	tree[rt].sum=tree[lc(rt)].sum+tree[rc(rt)].sum+tree[rt].point.val;
	tree[rt].maxx=max(tree[rt].maxx,max(tree[lc(rt)].maxx,tree[rc(rt)].maxx));
	tree[rt].maxy=max(tree[rt].maxy,max(tree[lc(rt)].maxy,tree[rc(rt)].maxy));
	tree[rt].minx=min(tree[rt].minx,min(tree[lc(rt)].minx,tree[rc(rt)].minx));
	tree[rt].miny=min(tree[rt].miny,min(tree[lc(rt)].miny,tree[rc(rt)].miny));
	return;
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
inline bool check(int x,int y)
{
	return 1ll*need.x*x+1ll*need.y*y<need.val;
}
inline ll query(int rt)
{
	int tot=(int)check(tree[rt].maxx,tree[rt].maxy)+(int)check(tree[rt].maxx,tree[rt].miny)+
	    (int)check(tree[rt].minx,tree[rt].maxy)+(int)check(tree[rt].minx,tree[rt].miny);
	if(tot==4)
		return tree[rt].sum;
	if(tot==0)
		return 0ll;
	ll res=check(tree[rt].point.x,tree[rt].point.y)?tree[rt].point.val:0;
	if(lc(rt))
		res+=query(lc(rt));
	if(rc(rt))
		res+=query(rc(rt));
	return res;
}
int n,m;
int main()
{
	tree[0].maxx=tree[0].maxy=-INF;
	tree[0].minx=tree[0].miny=INF;
	read(n),read(m);
	for(re int i=1; i<=n; ++i)
		read(point[i].x),read(point[i].y),read(point[i].val);
	build(root,1,n,true);
	while(m--)
	{
		read(need.x),read(need.y),read(need.val);
		printf("%lld\n",query(root));
	}
		return 0;
}
