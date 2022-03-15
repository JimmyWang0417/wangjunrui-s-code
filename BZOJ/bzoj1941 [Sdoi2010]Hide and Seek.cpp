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
const int N=500000+5;
int n;
bool sortflag;
struct Point
{
	int x,y,id;
	inline bool operator < (const Point &rhs)const
	{
		return sortflag?x<rhs.x:y<rhs.y;
	}
} point[N],need;
struct Tree
{
	Point point;
	int maxx,maxy;
	int minx,miny;
	int l,r;
} tree[N];
int cnt,root;
#define lc(x) tree[x].l
#define rc(x) tree[x].r
inline int newnode(const Point &rhs)
{
	int rt=++cnt;
	tree[rt].maxx=tree[rt].minx=rhs.x;
	tree[rt].maxy=tree[rt].miny=rhs.y;
	lc(rt)=rc(rt)=0;
	tree[rt].point=rhs;
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
const int INF=0x3f3f3f3f;
inline int dist(const Point &rhs)
{
	return abs(rhs.x-need.x)+abs(rhs.y-need.y);
}
inline int mindis(const Tree &rhs)
{
	return max(need.x-rhs.maxx,0)+max(rhs.minx-need.x,0)+
	       max(need.y-rhs.maxy,0)+max(rhs.miny-need.y,0);
}
inline int maxdis(const Tree &rhs)
{
	return max(abs(need.x-rhs.maxx),abs(rhs.minx-need.x))+
	       max(abs(need.y-rhs.maxy),abs(rhs.miny-need.y));
}
int ansmin;
inline void querymin(int rt)
{
	if(tree[rt].point.id!=need.id)
		ansmin=min(ansmin,dist(tree[rt].point));
	int ldis=lc(rt)?mindis(tree[lc(rt)]):(INF<<1),rdis=rc(rt)?mindis(tree[rc(rt)]):(INF<<1);
	if(ldis<rdis)
	{
		if(ldis<ansmin)
			querymin(lc(rt));
		if(rdis<ansmin)
			querymin(rc(rt));
	}
	else
	{
		if(rdis<ansmin)
			querymin(rc(rt));
		if(ldis<ansmin)
			querymin(lc(rt));
	}
}
int ansmax;
inline void querymax(int rt)
{
	ansmax=max(ansmax,dist(tree[rt].point));
	int ldis=lc(rt)?maxdis(tree[lc(rt)]):(-INF<<1),rdis=rc(rt)?maxdis(tree[rc(rt)]):(-INF<<1);
	if(ldis>rdis)
	{
		if(ldis>ansmax)
			querymax(lc(rt));
		if(rdis>ansmax)
			querymax(rc(rt));
	}
	else
	{
		if(rdis>ansmax)
			querymax(rc(rt));
		if(ldis>ansmax)
			querymax(lc(rt));
	}
}
int main()
{
	read(n);
	for(re int i=1; i<=n; ++i)
	{
		read(point[i].x);
		read(point[i].y);
		point[i].id=i;
	}
	int ans=INF;
	build(root,1,n,true);
	for(re int i=1; i<=n; ++i)
	{
		need=point[i];
		ansmax=-INF,querymax(root);
		ansmin=INF,querymin(root);
		ans=min(ans,ansmax-ansmin);
//		printf("%d %d %d\n",ansmax,ansmin,ans);
	}
	printf("%d\n",ans);
	return 0;
}
