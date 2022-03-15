#include <cstdio>
#include <algorithm>
#pragma GCC optimize(2)
#pragma GCC optimize(3)
#pragma GCC optimize("Ofast")
#pragma GCC optimize("inline")
#pragma GCC optimize("-fgcse")
#pragma GCC optimize("-fgcse-lm")
#pragma GCC optimize("-fipa-sra")
#pragma GCC optimize("-ftree-pre")
#pragma GCC optimize("-ftree-vrp")
#pragma GCC optimize("-fpeephole2")
#pragma GCC optimize("-ffast-math")
#pragma GCC optimize("-fsched-spec")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("-falign-jumps")
#pragma GCC optimize("-falign-loops")
#pragma GCC optimize("-falign-labels")
#pragma GCC optimize("-fdevirtualize")
#pragma GCC optimize("-fcaller-saves")
#pragma GCC optimize("-fcrossjumping")
#pragma GCC optimize("-fthread-jumps")
#pragma GCC optimize("-funroll-loops")
#pragma GCC optimize("-fwhole-program")
#pragma GCC optimize("-freorder-blocks")
#pragma GCC optimize("-fschedule-insns")
#pragma GCC optimize("inline-functions")
#pragma GCC optimize("-ftree-tail-merge")
#pragma GCC optimize("-fschedule-insns2")
#pragma GCC optimize("-fstrict-aliasing")
#pragma GCC optimize("-fstrict-overflow")
#pragma GCC optimize("-falign-functions")
#pragma GCC optimize("-fcse-skip-blocks")
#pragma GCC optimize("-fcse-follow-jumps")
#pragma GCC optimize("-fsched-interblock")
#pragma GCC optimize("-fpartial-inlining")
#pragma GCC optimize("no-stack-protector")
#pragma GCC optimize("-freorder-functions")
#pragma GCC optimize("-findirect-inlining")
#pragma GCC optimize("-frerun-cse-after-loop")
#pragma GCC optimize("inline-small-functions")
#pragma GCC optimize("-finline-small-functions")
#pragma GCC optimize("-ftree-switch-conversion")
#pragma GCC optimize("-foptimize-sibling-calls")
#pragma GCC optimize("-fexpensive-optimizations")
#pragma GCC optimize("-funsafe-loop-optimizations")
#pragma GCC optimize("inline-functions-called-once")
#pragma GCC optimize("-fdelete-null-pointer-checks")
#define lowbit(x) ((x)&(-(x)))
#define re register
#define ll long long
#define ull unsigned long long
#define rep(i,a,b) for(re int i=a;i<=b;++i)
#define per(i,a,b) for(re int i=a;i>=b;--i)
namespace IO
{
	const int SIZE=5e6+5;
	char ibuf[SIZE],*iS,*iT;
#define gc() (iS==iT?(iT=(iS=ibuf)+fread(ibuf,1,SIZE,stdin),iS==iT?EOF:*iS++):*iS++)
	template<typename T>
	inline void read(T & x)
	{
		x=0;
		bool b=false;
		char ch=gc();
		while(!isdigit(ch)&&ch^'-')
			ch=gc();
		if(ch=='-')
		{
			b=true;
			ch=gc();
		}
		while(isdigit(ch))
		{
			x=(x<<1)+(x<<3)+(ch^'0');
			ch=gc();
		}
		if(b)
			x=~x+1;
		return;
	}
#undef gc
}
using namespace IO;
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
const int N=5e5+5,mod=1e9+9,M=1e6+5e4+5;
#define add(x,y) (x+=y,x>=mod?x-=mod:0)
inline void times(int &x,int y)
{
	x=(int)((ll)x*y%mod);
}
struct node
{
	int l,r;
	inline bool operator <(const node &rhs)const
	{
		return l<rhs.l;
	}
} a[N];
int n,m;
int b[N];
int fac[N];
#define lc (rt<<1)
#define rc (rt<<1|1)
struct Tree
{
	int sum;
	int tag;
	inline void update(int val)
	{
		add(tag,val);
		times(sum,fac[val]);
	}
} tree[M];
inline void pushup(int rt)
{
	tree[rt].sum=(tree[lc].sum+tree[rc].sum)%mod;
}
inline void pushdown(int rt)
{
	if(tree[rt].tag)
	{
		tree[lc].update(tree[rt].tag);
		tree[rc].update(tree[rt].tag);
		tree[rt].tag=0;
	}
}
inline void update(int rt,int l,int r,int x,int y,int val)
{
	if(x<=l&&r<=y)
	{
		tree[rt].update(val);
		return;
	}
	pushdown(rt);
	int mid=(l+r)>>1;
	if(x<=mid)
		update(lc,l,mid,x,y,val);
	if(mid<y)
		update(rc,mid+1,r,x,y,val);
	pushup(rt);
}
inline void update(int rt,int l,int r,int pos,int val)
{
	if(l==r)
	{
		add(tree[rt].sum,val);
		return;
	}
	pushdown(rt);
	int mid=(l+r)>>1;
	if(pos<=mid)
		update(lc,l,mid,pos,val);
	else
		update(rc,mid+1,r,pos,val);
	pushup(rt);
}
inline int query(int rt,int l,int r,int x,int y)
{
	if(x<=l&&r<=y)
		return tree[rt].sum;
	pushdown(rt);
	int mid=(l+r)>>1,res=0;
	if(x<=mid)
		add(res,query(lc,l,mid,x,y));
	if(mid<y)
		add(res,query(rc,mid+1,r,x,y));
	return res;
}
signed main()
{
	freopen("xmasinterval.in","r",stdin),freopen("xmasinterval.out","w",stdout);
	read(n,m);
	for(int i=1; i<=n; ++i)
		read(a[i].l,a[i].r);
	for(int i=1; i<=m; ++i)
		read(b[i]);
	fac[0]=1;
	for(int i=1; i<=n; ++i)
	{
		fac[i]=fac[i-1]<<1;
		if(fac[i]>=mod)
			fac[i]-=mod;
	}

	sort(a+1,a+1+n);
	sort(b+1,b+1+m);
	for(int i=1; i<=n; ++i)
	{
		a[i].l=(int)(lower_bound(b+1,b+1+m,a[i].l)-b);
		a[i].r=(int)(upper_bound(b+1,b+1+m,a[i].r)-b-1);
	}
	update(1,0,m,0,1);
	for(int i=1; i<=n; ++i)
	{
		if(a[i].r<m)
			update(1,0,m,a[i].r+1,m,1);
		update(1,0,m,a[i].r,query(1,0,m,a[i].l-1,a[i].r));
	}
	printf("%d\n",query(1,0,m,m,m));
	return 0;
}

