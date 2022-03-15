#include <cstdio>
#include <cmath>
#include <cctype>
#include <algorithm>
#define re register
#define ll long long
#define lc(x) tree[x].l
#define rc(x) tree[x].r
using namespace std;
namespace IO
{
	const int SIZE=1<<25;
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
	inline void write_str(char *s)
	{
		for(re int i=0; s[i]; i++)
			*fe++=s[i];
		*fe++='\n';
	}
	inline void flush()
	{
		fwrite(Out,1,fe-Out,stdout);
		fe=Out;
	}
}
const int N=500000*2+5;
int n,m,root,ans,cnt;
bool sort_flag;
struct Point
{
	int x,y;
	inline bool operator < (const Point& rhs)const
	{
		return sort_flag?x<rhs.x:y<rhs.y;
	}
} point[N],need;
struct Tree
{
	Point point;
	int maxx,maxy,minx,miny;
	int l,r,size;
} tree[N];

int top,recycle[N];

inline int getdis(const Point &x,const Point &y)
{
	return abs(x.x-y.x)+abs(x.y-y.y);
}
inline int newnode(const Point &rhs)
{
	int rt=top?recycle[top--]:++cnt;
	tree[rt].point=rhs;
	tree[rt].maxx=tree[rt].minx=rhs.x;
	tree[rt].maxy=tree[rt].miny=rhs.y;
	tree[rt].l=tree[rt].r=0;
	tree[rt].size=1;
	return rt;
}
inline void pushup(int rt)
{
	tree[rt].size=tree[lc(rt)].size+tree[rc(rt)].size+1;
	tree[rt].maxx=max(tree[rt].maxx,max(tree[lc(rt)].maxx,tree[rc(rt)].maxx));
	tree[rt].maxy=max(tree[rt].maxy,max(tree[lc(rt)].maxy,tree[rc(rt)].maxy));
	tree[rt].minx=min(tree[rt].minx,min(tree[lc(rt)].minx,tree[rc(rt)].minx));
	tree[rt].miny=min(tree[rt].miny,min(tree[lc(rt)].miny,tree[rc(rt)].miny));
}
inline void build(int &rt,int l,int r,bool flag)
{
	int mid=(l+r)>>1;
	sort_flag=flag;
	nth_element(point+l,point+mid,point+1+r);
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
	if(alpha*tree[rt].size<max(tree[lc(rt)].size,tree[rc(rt)].size))
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
	sort_flag=flag;
	if(need<tree[rt].point)
		insert(lc(rt),flag^1);
	else
		insert(rc(rt),flag^1);
	pushup(rt);
	check(rt,flag);
}
inline int mindis(int rt)
{
	return max(need.x-tree[rt].maxx,0)+max(tree[rt].minx-need.x,0)+
	       max(need.y-tree[rt].maxy,0)+max(tree[rt].miny-need.y,0);
}
const int INF=0x3f3f3f3f;
inline void query(int rt)
{
	ans=min(getdis(need,tree[rt].point),ans);
	int ldis=lc(rt)?mindis(lc(rt)):INF,rdis=rc(rt)?mindis(rc(rt)):INF;
	if(ldis<rdis)
	{
		if(ldis>=ans)
			return;
		query(lc(rt));
		if(rdis>=ans)
			return;
		query(rc(rt));
	}
	else
	{
		if(rdis>=ans)
			return;
		query(rc(rt));
		if(ldis>=ans)
			return;
		query(lc(rt));
	}
}
int main()
{
	IO::read(n),IO::read(m);
	tree[0].maxx=tree[0].maxy=-INF;
	tree[0].minx=tree[0].miny=INF;
	for(re int i=1; i<=n; ++i)
	{
		IO::read(point[i].x);
		IO::read(point[i].y);
	}
	build(root,1,n,true);
	while(m--)
	{
		int opt;
		IO::read(opt);
		IO::read(need.x),IO::read(need.y);
		if(opt==1)
			insert(root,true);
		else if(opt==2)
		{
			ans=INF;
			query(root);
			IO::write(ans);
		}
	}
	IO::flush();
	return 0;
}
