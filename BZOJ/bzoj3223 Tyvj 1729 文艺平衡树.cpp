#include<cstdio>
#include<cstdlib>
#include<algorithm>
#include<ctime>
#define re register
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
			int val,key;
			int l,r,size;
			bool reverse;
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
		inline void pushdown(int now)
		{
			if(!tree[now].reverse)
				return;
			swap(tree[now].l,tree[now].r);
			if(tree[now].l)
				tree[tree[now].l].reverse^=1;
			if(tree[now].r)
				tree[tree[now].r].reverse^=1;
			tree[now].reverse=false;
			return;
		}
		inline void split(int now,int size,int &x,int &y)
		{
			if(!now)
				x=y=0;
			else
			{
				pushdown(now);
				if(tree[tree[now].l].size<size)
				{
					x=now;
					split(tree[now].r,size-tree[tree[now].l].size-1,tree[now].r,y);
				}
				else
				{
					y=now;
					split(tree[now].l,size,x,tree[now].l);
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
				pushdown(x);
				tree[x].r=merge(tree[x].r,y);
				update(x);
				return x;
			}
			else
			{
				pushdown(y);
				tree[y].l=merge(x,tree[y].l);
				update(y);
				return y;
			}
		}
	public:
		inline void reverse(int l,int r)
		{
			int x,y,z;
			split(root,l-1,x,y);
			split(y,r-l+1,y,z);
			tree[y].reverse^=1;
			root=merge(x,merge(y,z));
			return;
		}
		inline void insert(int val)
		{
			root=merge(root,newnode(val));
			return;
		}
		inline void dfs(int now)
		{
			if(!now)
				return;
			pushdown(now);
			dfs(tree[now].l);
			printf("%d ",tree[now].val);
			dfs(tree[now].r);
		}
		int n,m;
		inline void work()
		{
			read(n),read(m);
			for(re int i=1; i<=n; ++i)
				insert(i);
			while(m--)
			{
				int l,r;
				read(l),read(r);
				reverse(l,r);
			}
			dfs(root);
			putchar('\n');
		}
} fhq;

int main()
{
	srand((unsigned int)time(0));
	fhq.work();
	return 0;
}
