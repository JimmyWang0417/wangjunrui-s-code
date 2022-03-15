#include <cstdio>
#include <ctime>
#include <random>
#include <cmath>
#define ll long long
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

const int N=1e4+5,INF=0x7fffffff,mod=1e6;
mt19937 rnd((unsigned int)(time(0)));
class fhq_treap
{
#define lc(x) tree[x].l
#define rc(x) tree[x].r
	public:
		struct Tree
		{
			int l,r;
			int val,key;
			int size;
		} tree[N];
		int root,cnt;
	private:
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
					split(rc(x),val,rc(x),y);
				}
				else
				{
					y=now;
					split(lc(y),val,x,lc(y));
				}
				update(now);
			}
		}
		inline int merge(int x,int y)
		{
			if(!x||!y)
				return x|y;
			if(tree[x].key>tree[y].key)
			{
				rc(x)=merge(rc(x),y);
				update(x);
				return x;
			}
			else
			{
				lc(y)=merge(x,lc(y));
				update(y);
				return y;
			}
		}
	public:
		inline int pre(int val)
		{
			int x,y;
			split(root,val,x,y);
			int now=x;
			if(!now)
				return -INF;
			while(rc(now))
				now=rc(now);
			int ans=tree[now].val;
			root=merge(x,y);
			return ans;
		}
		inline int next(int val)
		{
			int x,y;
			split(root,val-1,x,y);
			int now=y;
			if(!now)
				return INF;
			while(lc(now))
				now=lc(now);
			int ans=tree[now].val;
			root=merge(x,y);
			return ans;
		}
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
			y=merge(lc(y),rc(y));
			root=merge(merge(x,y),z);
			if(!root)
				cnt=0;
			return;
		}
} customer,pet;
int n;
int ans;
signed main()
{
	read(n);
	while(n--)
	{
		int opt,x;
		read(opt),read(x);
		if(opt==0)
		{
			if(customer.tree[customer.root].size)
			{
				ll pre=customer.pre(x),nxt=customer.next(x);
				if(x-pre<=nxt-x)
				{
					(ans+=x-pre)%=mod;
					customer.del(pre);
				}
				else
				{
					(ans+=nxt-x)%=mod;
					customer.del(nxt);
				}
			}
			else
				pet.insert(x);
		}
		else
		{
			if(pet.tree[pet.root].size)
			{
				ll pre=pet.pre(x),nxt=pet.next(x);
				if(x-pre<=nxt-x)
				{
					(ans+=x-pre)%=mod;
					pet.del(pre);
				}
				else
				{
					(ans+=nxt-x)%=mod;
					pet.del(nxt);
				}
			}
			else
				customer.insert(x);
		}
//		printf("%lld %d %d\n",ans,customer.tree[customer.root].size,pet.tree[pet.root].size);
	}
	printf("%d\n",ans);
	return 0;
}
#undef lc
#undef rc
