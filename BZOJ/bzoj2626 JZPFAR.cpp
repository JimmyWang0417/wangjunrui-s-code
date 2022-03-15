#include <queue>
#include <cstdio>
#include <cctype>
#include <vector>
#include <algorithm>
#define re register
#define ll long long
using namespace std;
const int N=1e5+5,M=1e4+5;


namespace IO
{
	const int SIZE=1<<23;
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
	char Out[1<<20],*fe=Out,ch[100];
	int num=0;
	template<typename T>
	inline void write(T x)
	{
		if(!x)
			*fe++='0';
		if(x<0)
		{
			*fe++='-';
			x=-x;
		}
		while(x)
		{
			ch[++num]=(char)(x%10+'0');
			x/=10;
		}
		while(num)
			*fe++=ch[num--];
		*fe++='\n';
	}
	inline void flush()
	{
		fwrite(Out,1,fe-Out,stdout);
		fe=Out;
	}
}


bool sortflag;
struct Point
{
	int x,y;
	int id;
	inline bool operator <(const Point&rhs)const
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
#define lc(x) tree[x].l
#define rc(x) tree[x].r
#define square(x) (1ll*(x)*(x))
struct node
{
	ll dis;
	int id;
	node() {}
	node(ll nowdis,int nowid):dis(nowdis),id(nowid) {}
	inline bool operator > (const node &rhs)const
	{
		return dis>rhs.dis||(dis==rhs.dis&&id<rhs.id);
	}
};
inline ll dist(const Point &rhs)
{
	return square(rhs.x-need.x)+square(rhs.y-need.y);
}
inline ll maxdis(const Tree &rhs)
{
	return max(square(rhs.maxx-need.x),square(rhs.minx-need.x))
	       +max(square(rhs.maxy-need.y),square(rhs.miny-need.y));
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
int cnt,root;
inline int newnode(const Point &rhs)
{
	int rt=++cnt;
	tree[rt].maxx=tree[rt].minx=rhs.x;
	tree[rt].maxy=tree[rt].miny=rhs.y;
	tree[rt].point=rhs;
	lc(rt)=rc(rt)=0;
	return rt;
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
const ll INF=2e18;
priority_queue<node,vector<node>,greater<node> >q;
//inline void print(priority_queue<node,vector<node>,greater<node> > que)
//{
//	while(!que.empty())
//	{
//		printf("%d ",que.top().id);
//		que.pop();
//	}
//	putchar('\n');
//}
inline void query(int rt)
{
//	if(!rt)
//		return;
//	print(q);
	node res=node(dist(tree[rt].point),tree[rt].point.id);
//	printf("%lld %d\n",res.dis,res.id);
	ll ldis=lc(rt)?maxdis(tree[lc(rt)]):-INF<<1,rdis=rc(rt)?maxdis(tree[rc(rt)]):-INF<<1;
	if(res>q.top())
	{
		q.pop();
		q.push(res);
	}
	if(ldis>rdis)
	{
		if(ldis>=q.top().dis)
			query(lc(rt));
		if(rdis>=q.top().dis)
			query(rc(rt));
	}
	else
	{
		if(rdis>=q.top().dis)
			query(rc(rt));
		if(ldis>=q.top().dis)
			query(lc(rt));
	}
}
int n,m,k;
int main()
{
	IO::read(n);
	for(re int i=1; i<=n; ++i)
	{
		IO::read(point[i].x);
		IO::read(point[i].y);
		point[i].id=i;
	}
	build(root,1,n,true);
//	for(re int i=1; i<=cnt; ++i)
//		printf("%d %d %d %d %d\n",tree[i].maxx,tree[i].maxy,tree[i].minx,tree[i].miny,tree[i].point.id);
	IO::read(m);
	while(m--)
	{
		IO::read(need.x);
		IO::read(need.y);
		IO::read(k);
		for(re int i=0; i<k; ++i)
			q.push(node(-INF,~0x7fffffff));
		query(root);
		IO::write(q.top().id);
//		print(q);
//		printf("\n\n");
		priority_queue<node,vector<node>,greater<node> > empty;
		swap(empty,q);
	}
	IO::flush();
	return 0;
}
