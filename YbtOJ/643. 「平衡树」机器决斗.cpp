#include <bits/stdc++.h>
#define int ll
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
const int N=3e5+5;
struct Point
{
	int x,y;
	Point(int _x=0,int _y=0):x(_x),y(_y) {}
	inline Point operator +(const Point &rhs)const
	{
		return Point(x+rhs.x,y+rhs.y);
	}
	inline Point operator -(const Point &rhs)const
	{
		return Point(x-rhs.x,y-rhs.y);
	}
	inline int operator *(const Point &rhs)const
	{
		return x*rhs.y-y*rhs.x;
	}
	inline double norm()
	{
		return sqrt(x*x+y*y);
	}
	inline bool operator <(const Point &rhs)const
	{
		return x==rhs.x?y<rhs.y:x<rhs.x;
	}
	inline void print()
	{
		printf("(%lld,%lld)\n",x,y);
	}
};
struct Tree
{
	int l,r;
	int size;
	Point val,abs;
	int key;
	int id;
} tree[N];
int cnt,root;
#define lc(x) tree[x].l
#define rc(x) tree[x].r
mt19937 rnd((unsigned)time(0));
inline int newnode(Point val,int id)
{
	int now=++cnt;
	tree[now].val=val;
	tree[now].size=1;
	lc(now)=rc(now)=0;
	tree[now].id=id;
	tree[now].key=rnd();
	return now;
}
inline void pushup(int now)
{
	tree[now].size=tree[lc(now)].size+tree[rc(now)].size+1;
}
inline void split(int now,int size,int &x,int &y)
{
	if(!now)
		x=y=0;
	else
	{
		if(tree[lc(now)].size<size)
		{
			x=now;
			split(rc(now),size-tree[lc(now)].size-1,rc(x),y);
			pushup(x);
		}
		else
		{
			y=now;
			split(lc(now),size,x,lc(y));
			pushup(y);
		}
	}
}
inline void splitval(int now,Point val,int &x,int &y)
{
	if(!now)
		x=y=0;
	else
	{
		if(tree[now].val<val)
		{
			x=now;
			splitval(rc(now),val,rc(x),y);
			pushup(x);
		}
		else
		{
			y=now;
			splitval(lc(now),val,x,lc(y));
			pushup(y);
		}
	}
}
inline int merge(int x,int y)
{
	if(!x||!y)
		return x|y;
	if(tree[x].key>tree[y].key)
	{
		rc(x)=merge(rc(x),y);
		pushup(x);
		return x;
	}
	else
	{
		lc(y)=merge(x,lc(y));
		pushup(y);
		return y;
	}
}
inline void insert(Point val,int id)
{
	int now=newnode(val,id);
	if(tree[root].size==0)
	{
		root=now;
		return;
	}
	int rtl,rtr;
	splitval(root,val,rtl,rtr);
	int l,r;
	split(rtl,tree[rtl].size-1,rtl,l);
	split(rtr,1,r,rtr);
	if(l&&r)
	{
		if((tree[l].val-val)*(tree[r].val-val)<0)
		{
			root=merge(merge(rtl,l),merge(r,rtr));
			return;
		}
		while(tree[rtl].size>=1)
		{
			int las;
			split(rtl,tree[rtl].size-1,rtl,las);
			if((tree[las].val-val)*(tree[l].val-val)<0)
			{
				rtl=merge(rtl,las);
				break;
			}
			l=las;
		}
		while(tree[rtr].size>=1)
		{
			int las;
			split(rtr,1,las,rtr);
			if((tree[r].val-val)*(tree[las].val-val)<0)
			{
				rtr=merge(las,rtr);
				break;
			}
			r=las;
		}
		tree[now].abs=val-tree[l].val;
		tree[r].abs=tree[r].val-val;
		root=merge(merge(rtl,l),merge(now,merge(r,rtr)));
	}
	else if(l)
	{
		while(tree[rtl].size>=1)
		{
			int las;
			split(rtl,tree[rtl].size-1,rtl,las);
			if((tree[las].val-val)*(tree[l].val-val)<0)
			{
				rtl=merge(rtl,las);
				break;
			}
			l=las;
		}
		tree[now].abs=val-tree[l].val;
		root=merge(merge(rtl,l),now);
	}
	else if(r)
	{
		while(tree[rtr].size>=1)
		{
			int las;
			split(rtr,1,las,rtr);
			if((tree[r].val-val)*(tree[las].val-val)<0)
			{
				rtr=merge(las,rtr);
				break;
			}
			r=las;
		}
		tree[r].abs=tree[r].val-val;
		root=merge(now,merge(r,rtr));
	}
}
inline int query(int k)
{
	int now=root,ans=0;
	while(now)
	{
		ans=max(ans,tree[now].val.y-tree[now].val.x*k);
		now=(tree[now].abs.y>=k*tree[now].abs.x?rc(now):lc(now));
	}
	return ans;
}
int n,atk;
int S[N];
struct node
{
	int a,p;
	inline bool operator <(const node &rhs)const
	{
		return p*rhs.a<rhs.p*a;
	}
} a[N];
int pre[N],suf[N];
signed main()
{
	freopen("fittest.in","r",stdin);
	freopen("fittest.out","w",stdout);
	read(n,atk);
	for(int i=1; i<=n; ++i)
	{
		read(a[i].a,a[i].p);
		a[i].p=(a[i].p+atk-1)/atk;
	}
	sort(a+1,a+1+n);
	for(int i=1; i<=n; ++i)
		pre[i]=pre[i-1]+a[i].p;
	for(int i=n; i>=1; --i)
		suf[i]=suf[i+1]+a[i].a;
	for(int i=1; i<=n; ++i)
		S[i]=(pre[i]-1)*a[i].a+suf[i+1]*a[i].p;
	int ans=0,res=0;
	for(int i=1; i<=n; ++i)
		ans+=(pre[i]-1)*a[i].a;
	for(int i=n; i>=1; --i)
	{
		res=max(res,S[i]+query(a[i].p));
		insert(Point(a[i].a,S[i]),i);
	}
	printf("%lld\n",ans-res);
	return 0;
}

