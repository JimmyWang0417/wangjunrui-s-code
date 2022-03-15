#include<ctime>
#include<cstdio>
#include<random>
#include<cstdlib>
#include<algorithm>
#define re register
#define ll long long

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

const int N=32767+5;

const int INF=0x3f3f3f3f;
std::mt19937 rnd((unsigned int)time(0));
class fhq_treap
{
#define lc(x) tree[x].l
#define rc(x) tree[x].r
	private:
		int root,cnt;
		struct Tree
		{
			int l,r;
			int key,val;
			int size;
		} tree[N];
		inline int newnode(int val)
		{
			tree[++cnt].val=val;
			tree[cnt].size=1;
			tree[cnt].key=rnd();
			return cnt;
		}
		inline void update(int now)
		{
			tree[now].size=tree[lc(now)].size+tree[rc(now)].size+1;
			return;
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
					split(tree[now].r,val,tree[now].r,y);
				}
				else
				{
					y=now;
					split(tree[now].l,val,x,tree[now].l);
				}
				update(now);
			}
		}
		inline int merge(int x,int y)
		{
			if(!x||!y)
				return x+y;
			if(tree[x].key>tree[y].key)
			{
				tree[x].r=merge(tree[x].r,y);
				update(x);
				return x;
			}
			else
			{
				tree[y].l=merge(x,tree[y].l);
				update(y);
				return y;
			}
		}
	public:
		inline void insert(int val)
		{
			int x,y;
			split(root,val,x,y);
			root=merge(merge(x,newnode(val)),y);
		}
		inline int pre(int val)
		{
			int x,y;
			split(root,val,x,y);
			int now=x;
			if(!now)
				return -INF;
			while(tree[now].r)
				now=tree[now].r;
			root=merge(x,y);
			return tree[now].val;
		}
		inline int next(int val)
		{
			int x,y;
			split(root,val-1,x,y);
			int now=y;
			if(!now)
				return INF;
			while(tree[now].l)
				now=tree[now].l;
			root=merge(x,y);
			return tree[now].val;
		}
} fhq;
int n;
int main()
{
	read(n);
	int x;
	read(x);
	int ans=x;
	fhq.insert(x);
	for(re int i=1; i<n; ++i)
	{
		read(x);
		ans+=std::min(x-fhq.pre(x),fhq.next(x)-x);
		fhq.insert(x);
	}
	printf("%d\n",ans);
	return 0;
}
