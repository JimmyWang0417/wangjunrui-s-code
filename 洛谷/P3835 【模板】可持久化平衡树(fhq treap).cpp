#include<cstdio>
#include<random>
#include<ctime>
#define re register

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

const int N=5e5+5;
std::mt19937 rnd((unsigned int)time(0));
class Persistent_fhq_treap
{
	private:
		int root[N],cnt;
		struct Tree
		{
			int l,r,size;
			int val,key;
		} tree[N*50];
		inline int newnode(int val)
		{
			tree[++cnt].val=val;
			tree[cnt].key=rnd();
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
					tree[x=++cnt]=tree[now];
					split(tree[x].r,val,tree[x].r,y);
					update(x);
				}
				else
				{
					tree[y=++cnt]=tree[now];
					split(tree[y].l,val,x,tree[y].l);
					update(y);
				}
			}
		}
		inline int merge(int x,int y)
		{
			if(!x||!y)
				return x+y;
			int p=++cnt;
			if(tree[x].key>tree[y].key)
			{
				tree[p]=tree[x];
				tree[p].r=merge(tree[p].r,y);
			}
			else
			{
				tree[p]=tree[y];
				tree[p].l=merge(x,tree[p].l);
			}
			update(p);
			return p;
		}
	public:
		inline void insert(int prex,int now,int val)
		{
			int x,y;
			split(root[prex],val,x,y);
			root[now]=merge(merge(x,newnode(val)),y);
			return;
		}
		inline void del(int prex,int now,int val)
		{
			int x,y,z;
			split(root[prex],val,x,z);
			split(x,val-1,x,y);
			y=merge(tree[y].l,tree[y].r);
			root[now]=merge(merge(x,y),z);
			return;
		}
		inline void getrank(int prex,int now,int val)
		{
			int x,y;
			split(root[prex],val-1,x,y);
			printf("%d\n",tree[x].size+1);
			root[now]=merge(x,y);
			return;
		}
		inline void getnum(int prex,int i,int rank)
		{
			int now=root[prex];
			while(now)
			{
				if(tree[tree[now].l].size+1==rank)
					break;
				if(tree[tree[now].l].size>=rank)
					now=tree[now].l;
				else
				{
					rank-=tree[tree[now].l].size+1;
					now=tree[now].r;
				}
			}
			printf("%d\n",tree[now].val);
			root[i]=root[prex];
		}
		inline void pre(int prex,int i,int val)
		{
			int x,y;
			split(root[prex],val-1,x,y);
			int now=x;
			if(!tree[now].size)
			{
				printf("-2147483647\n");
				return;
			}
			while(tree[now].r)
				now=tree[now].r;
			printf("%d\n",tree[now].val);
			root[i]=merge(x,y);
			return;
		}
		inline void next(int prex,int i,int val)
		{
			int x,y;
			split(root[prex],val,x,y);
			int now=y;
			if(!tree[now].size)
			{
				printf("2147483647\n");
				return;
			}
			while(tree[now].l)
				now=tree[now].l;
			printf("%d\n",tree[now].val);
			root[i]=merge(x,y);
		}
		inline void work(int now)
		{
			int prex,opt,val;
			read(prex),read(opt),read(val);
			if(opt==1)
				insert(prex,now,val);
			else if(opt==2)
				del(prex,now,val);
			else if(opt==3)
				getrank(prex,now,val);
			else if(opt==4)
				getnum(prex,now,val);
			else if(opt==5)
				pre(prex,now,val);
			else if(opt==6)
				next(prex,now,val);
		}
} fhq;
int main()
{
	int n;
	read(n);
	for(re int i=1; i<=n; ++i)
		fhq.work(i);
	return 0;
}
