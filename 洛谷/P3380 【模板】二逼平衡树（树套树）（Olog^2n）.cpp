#include <ctime>
#include <cstdio>
#include <cstdlib>
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
struct Tree
{
	int l,r,size;
	int val,key;
} tree[N*40];
#define lc(x) tree[x].l
#define rc(x) tree[x].r
int cnt;
inline int newnode(int val)
{
	int now=++cnt;
	tree[now].val=val;
	tree[now].key=rand();
	tree[now].size=1;
	lc(now)=rc(now)=0;
	return now;
}
int n,a[N];
class Treap
{
	private:
		int root;
		inline void pushup(int now)
		{
			tree[now].size=tree[lc(now)].size+tree[rc(now)].size+1;
		}
		inline void split(int now,int val,int &x,int &y)
		{
			if(!now)
				x=y=0;
			else
			{
				if(tree[now].val<=val)
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
			else
			{
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
		}
	public:
		inline void insert(int pos)
		{
			int x,y;
			split(root,pos-1,x,y);
			root=merge(merge(x,newnode(pos)),y);
		}
		inline void del(int pos)
		{
			int x,y,z;
			split(root,pos-1,x,y);
			split(y,pos,y,z);
			root=merge(x,z);
		}
		inline int cnt(int l,int r)
		{
			int x,y,z;
			split(root,r,y,z);
			split(y,l-1,x,y);
			int ans=tree[y].size;
			root=merge(merge(x,y),z);
			return ans;
		}
};
class segment
{
	private:
		struct Tree
		{
			int l,r;
			Treap root;
		} tree[N*40];
		int cnt;
	public:
		inline void insert(int &rt,int l,int r,int pos,int val)
		{
			if(!rt)
				rt=++cnt;
			tree[rt].root.insert(val);
			if(l==r)
				return;
			int mid=(l+r)>>1;
			if(pos<=mid)
				insert(lc(rt),l,mid,pos,val);
			else
				insert(rc(rt),mid+1,r,pos,val);
		}
		inline void del(int &rt,int l,int r,int pos,int val)
		{
			if(!rt)
				return;
			tree[rt].root.del(val);
			if(l==r)
				return;
			int mid=(l+r)>>1;
			if(pos<=mid)
				del(lc(rt),l,mid,pos,val);
			else
				del(rc(rt),mid+1,r,pos,val);
		}
		inline int k_th(int &rt,int l,int r,int x,int y,int rk)
		{
			if(l==r)
				return l;
			int mid=(l+r)>>1,sum=tree[lc(rt)].root.cnt(x,y);
//			printf("         %d %d %d %d\n",l,r,sum,rk);
			if(rk<=sum)
				return k_th(lc(rt),l,mid,x,y,rk);
			else
				return k_th(rc(rt),mid+1,r,x,y,rk-sum);
		}
		inline int getrank(int &rt,int l,int r,int x,int y,int pos)
		{
			if(l==r)
				return 0;
			int mid=(l+r)>>1;
			if(pos<=mid)
				return getrank(lc(rt),l,mid,x,y,pos);
			else
				return tree[lc(rt)].root.cnt(x,y)+getrank(rc(rt),mid+1,r,x,y,pos);
		}
		inline int getcnt(int &rt,int l,int r,int x,int y,int pos)
		{
			if(!rt)
				return 0;
			if(l==r)
				return tree[rt].root.cnt(x,y);
			int mid=(l+r)>>1;
			if(pos<=mid)
				return getcnt(lc(rt),l,mid,x,y,pos);
			else
				return getcnt(rc(rt),mid+1,r,x,y,pos);
		}
} seg;
int root;
#define query root,0,1e8
signed main()
{
	srand(123456),srand(rand()),srand(rand());
	int m;
	read(n),read(m);
	for(re int i=1; i<=n; ++i)
	{
		read(a[i]);
		seg.insert(query,a[i],i);
	}
//	printf("%d\n",seg.tree[root].size);
//	for(re int i=1; i<=seg.cnt; ++i)
//		printf(" %d %d %d %d\n",i,seg.tree[i].size,seg.lc(i),seg.rc(i));
//	putchar('\n');
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
			printf("%d\n",seg.k_th(query,l,r,val));
		}
		else if(opt==3)
		{
			int pos,val;
			read(pos),read(val);
			seg.del(query,a[pos],pos);
			seg.insert(query,a[pos]=val,pos);
		}
		else if(opt==4)
		{
			int l,r,val;
			read(l),read(r),read(val);
			int rk=seg.getrank(query,l,r,val);
			printf("%d\n",!rk?-INF:seg.k_th(query,l,r,rk));
		}
		else if(opt==5)
		{
			int l,r,val;
			read(l),read(r),read(val);
			int rk=seg.getrank(query,l,r,val)+seg.getcnt(query,l,r,val)+1;
			printf("%d\n",rk>r-l+1?INF:seg.k_th(query,l,r,rk));
		}
	}
	return 0;
}
