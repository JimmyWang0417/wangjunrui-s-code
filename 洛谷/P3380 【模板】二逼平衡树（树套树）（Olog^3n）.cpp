#include <cstdio>
#include <cstdlib>
#include <algorithm>
#define re register
#define min(x,y) ((x)<(y)?(x):(y))
#define max(x,y) ((x)>(y)?(x):(y))
using namespace std;
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
const int N=5e4+5,INF=0x7fffffff;
int n,m,a[N];
struct Tree
{
	int l,r;
	int size;
	int val,key;
} tree[N*25];
int cnt;
#define lc(x) tree[x].l
#define rc(x) tree[x].r
#define size(x) tree[x].size
#define val(x) tree[x].val
#define key(x) tree[x].key
inline int newnode(int val)
{
	int now=++cnt;
	key(now)=rand();
	val(now)=val;
	size(now)=1;
	lc(now)=rc(now)=0;
	return now;
}
class FHQ
{
	private:
		int root=0;
		inline void pushup(int now)
		{
			size(now)=size(lc(now))+size(rc(now))+1;
		}
		inline void split(int now,int val,int &x,int &y)
		{
			if(!now)
				x=y=0;
			else
			{
				if(val(now)<=val)
				{
					x=now;
					split(rc(now),val,rc(now),y);
				}
				else
				{
					y=now;
					split(lc(now),val,x,lc(now));
				}
				pushup(now);
			}
		}
		inline int merge(int x,int y)
		{
			if(!x||!y)
				return x|y;
			if(key(x)>key(y))
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
	public:
		inline void insert(int val)
		{
			int x,y;
			split(root,val-1,x,y);
			root=merge(merge(x,newnode(val)),y);
		}
		inline void del(int val)
		{
			int x,y,z;
			split(root,val-1,x,y);
			split(y,val,y,z);
			y=merge(lc(y),rc(y));
			root=merge(merge(x,y),z);
		}
		inline int getrank(int val)
		{
			int x,y,ans;
			split(root,val-1,x,y);
			ans=tree[x].size;
			root=merge(x,y);
			return ans;
		}
		inline int pre(int val)
		{
			int x,y;
			split(root,val-1,x,y);
			if(!tree[x].size)
			{
				root=merge(x,y);
				return -INF;
			}
			else
			{
				int now=x;
				while(rc(now))
					now=rc(now);
				root=merge(x,y);
				return tree[now].val;
			}
		}
		inline int sub(int val)
		{
			int x,y;
			split(root,val,x,y);
			if(!tree[y].size)
			{
				root=merge(x,y);
				return INF;
			}
			else
			{
				int now=y;
				while(lc(now))
					now=lc(now);
				root=merge(x,y);
				return tree[now].val;
			}
		}
};
#undef lc
#undef rc
#undef val
#undef size
#undef key
class segment
{
	private:
		FHQ tree[N*4];
#define lc (rt<<1)
#define rc (rt<<1|1)
#define query 1,1,n
	public:
		inline void build(int rt,int l,int r)
		{
			for(re int i=l; i<=r; ++i)
				tree[rt].insert(a[i]);
			if(l==r)
				return;
			int mid=(l+r)>>1;
			build(lc,l,mid);
			build(rc,mid+1,r);
		}
		inline void update(int rt,int l,int r,int pos,int val)
		{
			tree[rt].del(a[pos]);
			tree[rt].insert(val);
			if(l==r)
				return;
			int mid=(l+r)>>1;
			if(pos<=mid)
				update(lc,l,mid,pos,val);
			else
				update(rc,mid+1,r,pos,val);
		}
		inline int getrank(int rt,int l,int r,int x,int y,int val)
		{
			if(r<x||l>y)
				return 0;
			if(x<=l&&r<=y)
				return tree[rt].getrank(val);
			int mid=(l+r)>>1;
			return getrank(lc,l,mid,x,y,val)+getrank(rc,mid+1,r,x,y,val);
		}
		inline int k_th(int x,int y,int rk)
		{
			int l=0,r=1e8,ans=0;
			while(l<=r)
			{
				int mid=(l+r)>>1;
				if(getrank(query,x,y,mid)+1<=rk)
				{
					ans=mid;
					l=mid+1;
				}
				else
					r=mid-1;
			}
			return ans;
		}
		inline int pre(int rt,int l,int r,int x,int y,int val)
		{

			if(r<x||l>y)
				return -INF;
			if(x<=l&&r<=y)
				return tree[rt].pre(val);
			int mid=(l+r)>>1;
			return max(pre(lc,l,mid,x,y,val),pre(rc,mid+1,r,x,y,val));
		}
		inline int sub(int rt,int l,int r,int x,int y,int val)
		{

			if(r<x||l>y)
				return INF;
			if(x<=l&&r<=y)
				return tree[rt].sub(val);
			int mid=(l+r)>>1;
			return min(sub(lc,l,mid,x,y,val),sub(rc,mid+1,r,x,y,val));
		}
} seg;
signed main()
{
	read(n),read(m);
	for(re int i=1; i<=n; ++i)
		read(a[i]);
	seg.build(query);
	while(m--)
	{
		int opt;
		read(opt);
		if(opt==1)
		{
			int l,r,val;
			read(l),read(r),read(val);
			printf("%d\n",seg.getrank(query,l,r,val)+1);
		}
		else if(opt==2)
		{
			int l,r,val;
			read(l),read(r),read(val);
			printf("%d\n",seg.k_th(l,r,val));
		}
		else if(opt==3)
		{
			int pos,val;
			read(pos),read(val);
			seg.update(query,pos,val);
			a[pos]=val;
		}
		else if(opt==4)
		{
			int l,r,val;
			read(l),read(r),read(val);
			printf("%d\n",seg.pre(query,l,r,val));
		}
		else if(opt==5)
		{
			int l,r,val;
			read(l),read(r),read(val);
			printf("%d\n",seg.sub(query,l,r,val));
		}
	}
	return 0;
}
