#include <queue>
#include <cstdio>
#include <vector>
#include <cctype>
#include <algorithm>

#define re register
#define ll long long
#define ull unsigned ll

using namespace std;

const int N=1e5+5;

namespace IO
{
	const int SIZE=25*N;
	char ibuf[SIZE],*iS,*iT;
#define gc() (iS==iT?(iT=(iS=ibuf)+fread(ibuf,1,SIZE,stdin),iS==iT?EOF:*iS++):*iS++)
	template<typename T>
	inline void read(T & x)
	{
		x=0;
		bool b=false;
		char ch=(char)gc();
		while(!isdigit(ch)&&ch^'-')
			ch=(char)gc();
		if(ch=='-')
		{
			b=true;
			ch=(char)gc();
		}
		while(isdigit(ch))
		{
			x=(x<<1)+(x<<3)+(ch^'0');
			ch=(char)gc();
		}
		if(b)
			x=~x+1;
		return;
	}
#undef gc
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
	int maxx,minx;
	int maxy,miny;
	int l,r;
	int size;
} tree[N];

priority_queue<ll,vector<ll>,greater<ll> >q;

#define lc(x) tree[x].l
#define rc(x) tree[x].r
int cnt,root;
int top=0,recycle[N];
inline int newnode(const Point &rhs)
{
	int rt=top?recycle[top--]:++cnt;
	tree[rt].point=rhs;
	tree[rt].maxx=tree[rt].minx=rhs.x;
	tree[rt].maxy=tree[rt].miny=rhs.y;
	lc(rt)=rc(rt)=0;
	tree[rt].size=1;
	return rt;
}
inline void pushup(int rt)
{
	tree[rt].size=1;
	if(lc(rt))
	{
		tree[rt].size+=tree[lc(rt)].size;
		tree[rt].maxx=max(tree[rt].maxx,tree[lc(rt)].maxx);
		tree[rt].maxy=max(tree[rt].maxy,tree[lc(rt)].maxy);
		tree[rt].minx=min(tree[rt].minx,tree[lc(rt)].minx);
		tree[rt].miny=min(tree[rt].miny,tree[lc(rt)].miny);
	}
	if(rc(rt))
	{
		tree[rt].size+=tree[rc(rt)].size;
		tree[rt].maxx=max(tree[rt].maxx,tree[rc(rt)].maxx);
		tree[rt].maxy=max(tree[rt].maxy,tree[rc(rt)].maxy);
		tree[rt].minx=min(tree[rt].minx,tree[rc(rt)].minx);
		tree[rt].miny=min(tree[rt].miny,tree[rc(rt)].miny);
	}
}
#define square(x) (1ll*(x)*(x))

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
inline void rebuild(int rt)
{
	if(lc(rt))
		rebuild(lc(rt));
	recycle[++top]=rt;
	point[top]=tree[rt].point;
	if(rc(rt))
		rebuild(rc(rt));
}
const double alpha=0.75;
inline void check(int &rt,bool flag)
{
	if(tree[rt].size*alpha<max(tree[lc(rt)].size,tree[rc(rt)].size))
	{
		rebuild(rt);
		build(rt,1,top,flag);
	}
}
inline void insert(int &rt,bool flag)
{
	if(!rt)
	{
		rt=newnode(need);
		return;
	}
	sortflag=flag;
	if(need<tree[rt].point)
		insert(lc(rt),flag^1);
	else insert(rc(rt),flag^1);
	pushup(rt);
	check(rt,flag);
}

const ll INF=2e18;
inline ll dist(const Point &rhs)
{
	return square(rhs.x-need.x)+square(rhs.y-need.y);
}
inline ll maxdis(const Tree &rhs)
{
	return max(square(rhs.maxx-need.x),square(rhs.minx-need.x))+
	       max(square(rhs.maxy-need.y),square(rhs.miny-need.y));
}
inline void query(int rt)
{
//	print(q);
	ll res=dist(tree[rt].point);
	ll ldis=lc(rt)?maxdis(tree[lc(rt)]):-INF*2,rdis=rc(rt)?maxdis(tree[rc(rt)]):-INF*2;
	if(res>q.top())
	{
		q.pop();
		q.push(res);
	}
	if(ldis>rdis)
	{
		if(ldis>q.top())
			query(lc(rt));
		if(rdis>q.top())
			query(rc(rt));
	}
	else
	{
		if(rdis>q.top())
			query(rc(rt));
		if(ldis>q.top())
			query(lc(rt));
	}
}



using IO::read;
int n,k;
int main()
{
	read(n),read(k);
	for(re int i=0; i<k; ++i)
		q.push(-INF);
	for(re int i=1; i<=n; ++i)
	{
		read(need.x);
		read(need.y);
		insert(root,true);
		query(root);
	}
//	print(q);
	printf("%lld\n",q.top());
	return 0;
}
