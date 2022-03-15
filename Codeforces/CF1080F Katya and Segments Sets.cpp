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
const int N=3e5+5;
const int INF=0x7fffffff;
int n,m,k;
struct Segment
{
	int l,r,p;
	inline bool operator <(const Segment &rhs)const
	{
		return l<rhs.l;
	}
} seg[N];
int p[N],tot;
struct Tree
{
	int l,r;
	int val;
	Tree(int _l=0,int _r=0,int _val=INF):l(_l),r(_r),val(_val) {}
} tree[N*40];
int cnt,root[N];
#define lc(rt) tree[rt].l
#define rc(rt) tree[rt].r
inline void pushup(int rt)
{
	tree[rt].val=max(tree[lc(rt)].val,tree[rc(rt)].val);
}
inline void update(int pre,int &rt,int l,int r,int pos,int val)
{
	rt=++cnt;
	tree[rt]=tree[pre];
	if(l==r)
	{
		tree[rt].val=min(tree[rt].val,val);
		return;
	}
	int mid=(l+r)>>1;
	if(pos<=mid)
		update(lc(pre),lc(rt),l,mid,pos,val);
	else
		update(rc(pre),rc(rt),mid+1,r,pos,val);
	pushup(rt);
}
inline int query(int rt,int l,int r,int x,int y)
{
	if(r<x||l>y)
		return ~0x7fffffff;
	if(x<=l&&r<=y)
		return tree[rt].val;
	int mid=(l+r)>>1;
	return max(query(lc(rt),l,mid,x,y),query(rc(rt),mid+1,r,x,y));
}
signed main()
{
	read(n,m,k);
	for(int i=1; i<=k; ++i)
		read(seg[i].l,seg[i].r,seg[i].p);
	sort(seg+1,seg+1+k);
	for(int i=1; i<=k; ++i)
		p[++tot]=seg[i].l;
	tot=(int)(unique(p+1,p+1+tot)-p-1);
	for(int i=k; i>=1; --i)
	{
		seg[i].l=(int)(lower_bound(p+1,p+1+tot,seg[i].l)-p);
		update(root[seg[i+1].l],root[seg[i].l],1,n,seg[i].p,seg[i].r);
	}
	for(int i=1; i<=m; ++i)
	{
		int a,b,x,y;
		read(a,b,x,y);
		int rt=root[lower_bound(p+1,p+1+tot,x)-p];
		puts(query(rt,1,n,a,b)<=y?"yes":"no");
		fflush(stdout);
	}
	return 0;
}

