#include <queue>
#include <cstdio>
#include <cctype>
#include <vector>
#include <algorithm>
#define re register
#define ll long long
using namespace std;
namespace IO
{
	const int SIZE=1<<21|1;
	char ibuf[SIZE],*iS,*iT;
#define gc() (iS==iT?(iT=(iS=ibuf)+fread(ibuf,1,SIZE,stdin),iS==iT?EOF:*iS++):*iS++)
	template <typename T>
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
	template <typename T>
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

const int N=200000+5;
int cnt,root;
int recycle[N],top=0;
bool sortflag;
struct Point
{
	int x,y;
	int val;
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
	int size;
	int sum;
} tree[N];
#define lc(x) tree[x].l
#define rc(x) tree[x].r
inline int newnode(const Point &rhs)
{
	int rt=top?recycle[top--]:++cnt;
	tree[rt].point=rhs;
	tree[rt].maxx=tree[rt].minx=rhs.x;
	tree[rt].maxy=tree[rt].miny=rhs.y;
	tree[rt].sum=rhs.val;
	tree[rt].size=1;
	lc(rt)=rc(rt)=0;
	return rt;
}
inline void pushup(int rt)
{
	tree[rt].size=1;
	tree[rt].sum=tree[rt].point.val;
	if(lc(rt))
	{
		tree[rt].size+=tree[lc(rt)].size;
		tree[rt].sum+=tree[lc(rt)].sum;
		tree[rt].maxx=max(tree[rt].maxx,tree[lc(rt)].maxx);
		tree[rt].maxy=max(tree[rt].maxy,tree[lc(rt)].maxy);
		tree[rt].minx=min(tree[rt].minx,tree[lc(rt)].minx);
		tree[rt].miny=min(tree[rt].miny,tree[lc(rt)].miny);
	}
	if(rc(rt))
	{
		tree[rt].size+=tree[rc(rt)].size;
		tree[rt].sum+=tree[rc(rt)].sum;
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
	nth_element(point+l,point+mid,point+r);
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
	if(tree[rt].point.x==need.x&&tree[rt].point.y==need.y)
	{
		tree[rt].sum+=need.val;
		tree[rt].point.val+=need.val;
		return;
	}
	sortflag=flag;
	if(need<tree[rt].point)
		insert(lc(rt),flag^1);
	else
		insert(rc(rt),flag^1);
	pushup(rt);
	check(rt,flag);
}
inline int query(int rt,int x1,int y1,int x2,int y2)
{
	if(!rt||x1>tree[rt].maxx||tree[rt].minx>x2||y1>tree[rt].maxy||tree[rt].miny>y2)
		return 0;
	if(x1<=tree[rt].minx&&tree[rt].maxx<=x2&&y1<=tree[rt].miny&&tree[rt].maxy<=y2)
		return tree[rt].sum;
	int res=0;
	if(x1<=tree[rt].point.x&&tree[rt].point.x<=x2&&y1<=tree[rt].point.y&&tree[rt].point.y<=y2)
		res=tree[rt].point.val;
	return res+query(lc(rt),x1,y1,x2,y2)+query(rc(rt),x1,y1,x2,y2);
}
int n;
int ans;
using IO::read;
using IO::write;
int main()
{
	read(n);
	while(1)
	{
		int opt;
		read(opt);
		if(opt==3)
			break;
		if(opt==1)
		{
			read(need.x),need.x^=ans;
			read(need.y),need.y^=ans;
			read(need.val),need.val^=ans;
			insert(root,true);
		}
		else if(opt==2)
		{
			int x1,x2,y1,y2;
			read(x1),x1^=ans;
			read(y1),y1^=ans;
			read(x2),x2^=ans;
			read(y2),y2^=ans;
			write(ans=query(root,x1,y1,x2,y2));
		}
	}
	IO::flush();
	return 0;
}
