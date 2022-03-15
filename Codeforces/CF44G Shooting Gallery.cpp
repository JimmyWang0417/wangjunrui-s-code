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
const int N=1e5+5;
int n,m;
struct Query
{
	int x1,y1,x2,y2,z,id;
	inline bool operator < (const Query &rhs)const
	{
		return z<rhs.z;
	}
} q[N];
bool sortflag;
struct Point
{
	int x,y,id;
	inline bool operator < (const Point &rhs)const
	{
		return sortflag?x<rhs.x:y<rhs.y;
	}
} point[N];
struct Tree
{
	Point val;
	int minx,miny,maxx,maxy;
	int minid;
	int l,r,fa;
} tree[N];
#define lc(x) tree[x].l
#define rc(x) tree[x].r
#define fa(x) tree[x].fa
int root,cnt;
inline void pushup(int rt)
{
	tree[rt].minid=rt;
	tree[rt].minx=tree[rt].maxx=tree[rt].val.x;
	tree[rt].miny=tree[rt].maxy=tree[rt].val.y;
	if(lc(rt))
	{
		if(tree[tree[lc(rt)].minid].val.id<tree[tree[rt].minid].val.id)
			tree[rt].minid=tree[lc(rt)].minid;
		tree[rt].minx=min(tree[rt].minx,tree[lc(rt)].minx);
		tree[rt].miny=min(tree[rt].miny,tree[lc(rt)].miny);
		tree[rt].maxx=max(tree[rt].maxx,tree[lc(rt)].maxx);
		tree[rt].maxy=max(tree[rt].maxy,tree[lc(rt)].maxy);
	}
	if(rc(rt))
	{
		if(tree[tree[rc(rt)].minid].val.id<tree[tree[rt].minid].val.id)
			tree[rt].minid=tree[rc(rt)].minid;
		tree[rt].minx=min(tree[rt].minx,tree[rc(rt)].minx);
		tree[rt].miny=min(tree[rt].miny,tree[rc(rt)].miny);
		tree[rt].maxx=max(tree[rt].maxx,tree[rc(rt)].maxx);
		tree[rt].maxy=max(tree[rt].maxy,tree[rc(rt)].maxy);
	}
}
inline void build(int &rt,int l,int r,bool flag)
{
	int mid=(l+r)>>1;
	sortflag=flag;
	nth_element(point+l,point+mid,point+r+1);
	tree[rt=++cnt].val=point[mid];
	if(l<mid)
		build(lc(rt),l,mid-1,flag^1);
	if(mid<r)
		build(rc(rt),mid+1,r,flag^1);
	tree[lc(rt)].fa=tree[rc(rt)].fa=rt;
	pushup(rt);
}
int ans,where;
inline void query(int &rt,int x1,int y1,int x2,int y2)
{
	if(!rt)
		return;
//	printf("%d %d %d %d %d\n",rt,x1,y1,x2,y2);
	if(tree[rt].maxx<x1||tree[rt].minx>x2||tree[rt].maxy<y1||tree[rt].miny>y2)
		return;
	if(x1<=tree[rt].minx&&tree[rt].maxx<=x2&&y1<=tree[rt].miny&&tree[rt].maxy<=y2)
	{
		if(tree[tree[rt].minid].val.id<ans)
		{
			ans=tree[tree[rt].minid].val.id;
			where=tree[rt].minid;
		}
		return;
	}
	if(x1<=tree[rt].val.x&&tree[rt].val.x<=x2&&y1<=tree[rt].val.y&&tree[rt].val.y<=y2)
	{
		if(tree[rt].val.id<ans)
		{
			ans=tree[rt].val.id;
			where=rt;
		}
	}
	query(lc(rt),x1,y1,x2,y2);
	query(rc(rt),x1,y1,x2,y2);
}
int answer[N];
signed main()
{
	read(n);
	for(int i=1; i<=n; ++i)
	{
		read(q[i].x1,q[i].x2,q[i].y1,q[i].y2,q[i].z);
		q[i].id=i;
	}
	read(m);
	for(int i=1; i<=m; ++i)
	{
		read(point[i].x,point[i].y);
		point[i].id=i;
	}
	sort(q+1,q+1+n);
	build(root,1,m,false);
//	for(int i=1; i<=cnt; ++i)
//		printf("%d %d %d %d %d %d %d %d\n",tree[i].minid,tree[i].val.id,lc(i),rc(i),tree[i].minx,tree[i].miny,tree[i].maxx,tree[i].maxy);
//	putchar('\n');
	for(int i=1; i<=n; ++i)
	{
		ans=m+1;
		query(root,q[i].x1,q[i].y1,q[i].x2,q[i].y2);
		if(ans==m+1)
			continue;
		answer[ans]=q[i].id;
		int rt=where;
		tree[rt].val.id=m+1;
		while(rt)
		{
			pushup(rt);
			rt=fa(rt);
		}
	}
	for(int i=1; i<=m; ++i)
		printf("%d\n",answer[i]);
	return 0;
}
