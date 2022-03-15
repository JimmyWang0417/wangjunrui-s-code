#include<cstdio>
#include<random>
#include<ctime>
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

const int N=2e5+5;
std::mt19937 rnd((unsigned int)time(0));
class Persistent_fhq_treap
{
	private:
		int root[N],cnt;
		ll lastans;
		struct node
		{
			int l,r,size;
			int key;
			ll sum,val;
			bool reverse;
		} tree[N<<7];
		inline int newnode(ll val=0)
		{
			++cnt;
			tree[cnt].val=tree[cnt].sum=val;
			tree[cnt].key=rnd();
			tree[cnt].size=1;
			return cnt;
		}
		inline int copynode(int prex)
		{
			tree[++cnt]=tree[prex];
//			printf("%d\n",tree[cnt].sum);
			return cnt;
		}
		inline void update(int now)
		{
			tree[now].size=tree[tree[now].l].size+tree[tree[now].r].size+1;
			tree[now].sum=tree[tree[now].l].sum+tree[tree[now].r].sum+tree[now].val;
//			printf("%lld\n",tree[now].sum);
			return;
		}
		inline void pushdown(int now)
		{
			if(!tree[now].reverse)
				return;
			if(tree[now].l)
				tree[now].l=copynode(tree[now].l);
			if(tree[now].r)
				tree[now].r=copynode(tree[now].r);
			std::swap(tree[now].l,tree[now].r);
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
					x=copynode(now);
					split(tree[x].r,size-tree[tree[now].l].size-1,tree[x].r,y);
					update(x);
				}
				else
				{
					y=copynode(now);
					split(tree[y].l,size,x,tree[y].l);
					update(y);
				}
			}
			return;
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
		inline void insert(int pre,int now)
		{
			ll a,b;
			int x,y;
			read(a),read(b);
			a^=lastans;
			b^=lastans;
			split(root[pre],a,x,y);
			root[now]=merge(merge(x,newnode(b)),y);
		}
		inline void del(int pre,int now)
		{
			ll a;
			int x,y,z;
			read(a);
			a^=lastans;
			split(root[pre],a,x,z);
			split(x,a-1,x,y);
			root[now]=merge(x,z);
		}
		inline void reverse(int pre,int now)
		{
			ll a,b;
			int x,y,z;
			read(a),read(b);
			a^=lastans;
			b^=lastans;
			split(root[pre],a-1,x,y);
			split(y,b-a+1,y,z);
			tree[y].reverse^=1;
			root[now]=merge(x,merge(y,z));
		}
		inline void getsum(int pre,int now)
		{
			ll a,b;
			int x,y,z;
			read(a),read(b);
			a^=lastans;
			b^=lastans;
			split(root[pre],a-1,x,y);
			split(y,b-a+1,y,z);
			printf("%lld\n",lastans=tree[y].sum);
			root[now]=merge(x,merge(y,z));
		}
//		inline void dfs(int now)
//		{
//			if(!now)
//				return;
//			dfs(tree[now].l);
//			printf("%lld ",tree[now].val);
//			dfs(tree[now].r);
//		}
		inline void work(int now)
		{
			int pre,opt;
			read(pre),read(opt);
			if(opt==1)
				insert(pre,now);
			else if(opt==2)
				del(pre,now);
			else if(opt==3)
				reverse(pre,now);
			else if(opt==4)
				getsum(pre,now);
//			dfs(root[now]);
//			putchar('\n');
		}

} fhq;
int main()
{
//	freopen("ans.out","w",stdout);
	int n;
	read(n);
	for(re int i=1; i<=n; ++i)
		fhq.work(i);
}
