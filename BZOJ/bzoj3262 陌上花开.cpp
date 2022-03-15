#include <cstdio>
#include <algorithm>
#define min(x,y) ((x)<(y)?(x):(y))
#define max(x,y) ((x)>(y)?(x):(y))
#define re register
using namespace std;

namespace IO
{
	const int SIZE=10*1e5;
	char ibuf[SIZE],*iS,*iT;
#define gc() (char)(iS==iT?(iT=(iS=ibuf)+fread(ibuf,1,SIZE,stdin),iS==iT?EOF:*iS++):*iS++)
	template<typename T>
	inline void read(T & x)
	{
		x=0;
		bool b=false;
		char ch=gc();
		while((ch<'0'||ch>'9')&&ch^'-')
			ch=gc();
		if(ch=='-')
		{
			b=true;
			ch=gc();
		}
		while(ch>='0'&&ch<='9')
		{
			x=(x<<1)+(x<<3)+(ch^'0');
			ch=gc();
		}
		if(b)
			x=~x+1;
		return;
	}
#undef gc
	char Out[(int)1e5*7],*fe=Out,ch[25];
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
const int N=1e5+5,INF=0x3f3f3f3f;
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
	int l,r,size;
	int maxx,minx;
	int maxy,miny;
} tree[N];
int root,cnt;
int top,recycle[N];
#define lc(x) tree[x].l
#define rc(x) tree[x].r
inline int newnode(const Point &rhs)
{
	int rt=top?recycle[top--]:++cnt;
	tree[rt].size=1;
	tree[rt].point=rhs;
	tree[rt].maxx=tree[rt].minx=rhs.x;
	tree[rt].maxy=tree[rt].miny=rhs.y;
	lc(rt)=rc(rt)=0;
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
	recycle[top=1]=rt;
	for(re int i=1; i<=top; ++i)
	{
		point[i]=tree[recycle[i]].point;
		if(lc(recycle[i]))
			recycle[++top]=lc(recycle[i]);
		if(rc(recycle[i]))
			recycle[++top]=rc(recycle[i]);
	}
}
inline void check(int &rt,bool flag)
{
	if((tree[rt].size*3>>2)<max(tree[lc(rt)].size,tree[rc(rt)].size))
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
	else
		insert(rc(rt),flag^1);
	pushup(rt);
	check(rt,flag);
}
inline int query(int rt)
{
	if(!rt||tree[rt].minx>need.x||tree[rt].miny>need.y)
		return 0;
	if(tree[rt].maxx<=need.x&&tree[rt].maxy<=need.y)
		return tree[rt].size;
	return (tree[rt].point.x<=need.x&&tree[rt].point.y<=need.y)+query(lc(rt))+query(rc(rt));
}
struct node
{
	int x,y,z;
	inline bool operator < (const node &rhs)const
	{
		return x<rhs.x;
	}
} a[N];
int n,k;
int mp[N];
inline void solve(int l,int r)
{
//	printf("%d %d\n",l,r);
	for(re int i=l; i<=r; ++i)
	{
		need.x=a[i].y,need.y=a[i].z;
		insert(root,true);
	}
	for(re int i=l; i<=r; ++i)
	{
		need.x=a[i].y,need.y=a[i].z;
		++mp[query(root)];
	}
//	for(re int i=1; i<=cnt; ++i)
//		printf("%d %d %d %d %d %d\n",tree[i].maxx,tree[i].minx,tree[i].maxy,tree[i].miny,tree[i].point.x,tree[i].point.y);
//	putchar('\n');
}
using namespace IO;
int main()
{
	tree[0].maxx=tree[0].maxy=-INF;
	tree[0].minx=tree[0].miny=INF;
	read(n),read(k);
	for(re int i=1; i<=n; ++i)
	{
		read(a[i].x);
		read(a[i].y);
		read(a[i].z);
	}
	stable_sort(a+1,a+1+n);
//	for(re int i=1; i<=n; ++i)
//		printf("%d %d %d\n",a[i].x,a[i].y,a[i].z);
	re int head=1,tail=2;
	for(; tail<=n; ++tail)
	{
		if(a[head].x!=a[tail].x)
		{
			solve(head,tail-1);
			head=tail;
		}
	}
	solve(head,tail-1);
	for(re int i=1; i<=n; ++i)
		write(mp[i]);
	flush();
	return 0;
}
