#include <cstdio>
#include <stack>
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
using namespace std;
const int N=7e4+5,V=7e4,logn=20,SIZE=1e7;
const double alpha=0.75;
int n,v[N];
namespace segment
{
	struct Tree
	{
		int l,r;
		int sum;
	} tree[N];
#define lc(x) tree[x].l
#define rc(x) tree[x].r
#define sum(x) tree[x].sum
	int stack[SIZE],top;
	inline int newnode()
	{
		int now=stack[top--];
		lc(now)=rc(now)=0;
		return now;
	}
	inline void insert(int &rt,int l,int r,int pos,int v)
	{
		if(rt==0)
			rt=newnode();
		sum(rt)+=v;
		if(l==r)
			return;
		int mid=(l+r)>>1;
		if(pos<=mid)
			insert(lc(rt),l,mid,pos,v);
		else
			insert(rc(rt),mid+1,r,pos,v);
	}
	inline void newtree(int &rt,int pos)
	{
		rt=newnode();
		++sum(rt);
		int l,r=V,now=rt;
		while(l<r)
		{
			int mid=(l+r)>>1;
			if(pos<=mid)
			{
				now=lc(now)=newnode();
				r=mid;
			}
			else
			{
				now=rc(now)=newnode();
				l=mid+1;
			}
			++sum(now);
		}
	}
	inline void merge(int &x,int y)
	{
		if(!y)
			return;
		if(!x)
			x=newnode();
		sum(x)+=sum(y);
		merge(lc(x),lc(y));
		merge(rc(x),rc(y));
	}
	inline void clear(int &rt)
	{
		stack[++top]=rt;
		if(lc(rt))
			clear(lc(rt));
		if(rc(rt))
			clear(rc(rt));
		lc(rt)=rc(rt)=sum(rt)=0;
		rt=0;
	}
#undef lc
#undef rc
#undef sum
}
namespace ScapgoatTree
{
	int root;
	int lc[N], rc[N], sz[N], rt[N];
	int dfn[N], dfnN, val[N], valN;
	int maxDepth;

	int build(int l, int r)
	{
		int mid = (l+r)>>1, x = dfn[mid];
		segment::newtree(rt[x], v[x]);
		if(l < mid) lc[x] = build(l, mid-1);
		if(mid < r) rc[x] = build(mid+1, r);
		sz[x] = sz[lc[x]]+sz[rc[x]]+1;
		SegmentTree::merge(rt[x], rt[lc[x]]);
		SegmentTree::merge(rt[x], rt[rc[x]]);
		return x;
	}

	void get(int x)
	{
		if(lc[x]) get(lc[x]);
		dfn[++dfnN] = x;
		if(rc[x]) get(rc[x]);
	}

	int rebuild(int x)
	{
		dfnN = 0, get(x);
		for(int i = 1; i <= dfnN; ++i)
		{
			SegmentTree::clear(rt[dfn[i]]);
			lc[dfn[i]] = rc[dfn[i]] = sz[dfn[i]] = 0;
		}
		return build(1, dfnN);
	}

	void get(int x, int l, int r, int ql, int qr)
	{
		if(ql <= l && r <= qr)
		{
			dfn[++dfnN] = rt[x];
			return ;
		}
		int mid = l+sz[lc[x]];
		if(ql < mid && lc[x]) get(lc[x], l, mid-1, ql, qr);
		if(ql <= mid && mid <= qr) val[++valN] = v[x];
		if(qr > mid && rc[x]) get(rc[x], mid+1, r, ql, qr);
	}

	int query(int l, int r, int k)
	{
		valN = dfnN = 0, get(root, 1, n, l, r);
		l = 0, r = V;
		while(l < r)
		{
			int ls = 0, mid = (l+r)>>1;
			for(int i = 1; i <= dfnN; ++i)
				ls += SegmentTree::sum[SegmentTree::lc[dfn[i]]];
			for(int i = 1; i <= valN; ++i)
				if(l <= val[i] && val[i] <= mid) ls++;
			if(ls >= k)
			{
				r = mid;
				for(int i = 1; i <= dfnN; ++i)
					dfn[i] = SegmentTree::lc[dfn[i]];
			}
			else
			{
				k -= ls, l = mid+1;
				for(int i = 1; i <= dfnN; ++i)
					dfn[i] = SegmentTree::rc[dfn[i]];
			}
		}
		return l;
	}

	void get(int x, int pos)
	{
		dfn[++dfnN] = x;
		if(sz[lc[x]] >= pos) get(lc[x], pos);
		else if(sz[lc[x]]+1 == pos) return ;
		else get(rc[x], pos-sz[lc[x]]-1);
	}

	void modify(int x, int value)
	{
		dfnN = 0, get(root, x);
		for(int i = 1; i <= dfnN; ++i)
		{
			SegmentTree::insert(rt[dfn[i]], 0, V, v[dfn[dfnN]], -1);
			SegmentTree::insert(rt[dfn[i]], 0, V, value, 1);
		}
		v[dfn[dfnN]] = value;
	}

	bool insert(int &x, int pos, int p, int d)
	{
		if(x == 0)
		{
			sz[x = p]++;
			SegmentTree::newTree(rt[x], v[x]);
			return d <= maxDepth;
		}
		sz[x]++;
		SegmentTree::insert(rt[x], 0, V, v[p], 1);
		bool ret;
		if(pos <= sz[lc[x]]+1) ret = insert(lc[x], pos, p, d+1);
		else ret = insert(rc[x], pos-sz[lc[x]]-1, p, d+1);
		int lim = (int)(sz[x]*ALPHA);
		if(ret && (sz[lc[x]] > lim || sz[rc[x]] > lim))
		{
			x = rebuild(x);
			return false;
		}
		else return ret;
	}

	void insert(int pos, int p)
	{
		maxDepth = log(1.0*n)/LOGALPHA;
		insert(root, pos, p, 0);
	}
}
int main()
{

}
