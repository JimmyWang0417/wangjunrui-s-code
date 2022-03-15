#include<cstdio>
#include<ctime>
#include<cstdlib>
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

const int N=1e5+5;
class fhq_treap
{
	private:
		struct Tree
		{
			int val,key,size;
			int l,r;
		} tree[N];
		int cnt,root;
		inline int newnode(int val)
		{
			tree[++cnt].val=val;
			tree[cnt].key=rand();
			tree[cnt].size=1;
			return cnt;
		}
		inline void update(int now)
		{
			tree[now].size=tree[tree[now].l].size+tree[tree[now].r].size+1;
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
			return;
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
			return;
		}
		inline void del(int val)
		{
			int x,y,z;
			split(root,val,x,z);
			split(x,val-1,x,y);
			y=merge(tree[y].l,tree[y].r);
			root=merge(merge(x,y),z);
			return;
		}
		inline void getrank(int val)
		{
			int x,y;
			split(root,val-1,x,y);
			printf("%d\n",tree[x].size+1);
			root=merge(x,y);
			return;
		}
		inline void getnum(int rank)
		{
			int now=root;
			while(now)
			{
				if(rank==tree[tree[now].l].size+1)
					break;
				else if(tree[tree[now].l].size>=rank)
					now=tree[now].l;
				else
				{
					rank-=tree[tree[now].l].size+1;
					now=tree[now].r;
				}
			}
			printf("%d\n",tree[now].val);
			return;
		}
		inline void pre(int val)
		{
			int x,y;
			split(root,val-1,x,y);
			int now=x;
			while(tree[now].r)
				now=tree[now].r;
			printf("%d\n",tree[now].val);
			root=merge(x,y);
			return;
		}
		inline void next(int val)
		{
			int x,y;
			split(root,val,x,y);
			int now=y;
			while(tree[now].l)
				now=tree[now].l;
			printf("%d\n",tree[now].val);
			root=merge(x,y);
			return;
		}
		inline void getans()
		{
			int opt,val;
			read(opt),read(val);
			switch(opt)
			{
				case 1:
					insert(val);
					break;
				case 2:
					del(val);
					break;
				case 3:
					getrank(val);
					break;
				case 4:
					getnum(val);
					break;
				case 5:
					pre(val);
					break;
				case 6:
					next(val);
					break;
			}
		}
} fhq;
int n;
int main()
{
	srand((unsigned int)time(0));
	read(n);
	while(n--)
		fhq.getans();
}
