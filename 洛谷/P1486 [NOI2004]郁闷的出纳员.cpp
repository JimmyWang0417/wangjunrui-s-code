#include<cstdio>
#include<random>
#include<ctime>

#define re register

const int N=1e5+10;
std::mt19937 rnd((unsigned int)time(0));
class fhq_treap
{
	private:
		int root,cnt;
		struct Tree
		{
			int l,r,size;
			int val,key;
		} tree[N];
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
				return x|y;
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
		int minn,ans=0,sum;
		inline void insert(int val)
		{
			if(val<minn)
				return;
			int x,y;
			val-=sum;
			split(root,val,x,y);
			root=merge(merge(x,newnode(val)),y);
		}
		inline void change(int val)
		{
			sum+=val;
//			printf(" %d\n",minn);
			int x;
			split(root,minn-sum-1,x,root);
			ans+=tree[x].size;
		}
		inline int getnum(int rank)
		{
//			printf("  %d\n",tree[root].size);
			if(rank>tree[root].size)
				return -1;
			rank=tree[root].size-rank+1;
			int now=root;
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
			return tree[now].val+sum;
		}
} fhq;
int n,x;
char str[10];
int main()
{
	scanf("%d%d",&n,&fhq.minn);
	while(n--)
	{
		scanf("%s%d",str,&x);
		if(str[0]=='I')
			fhq.insert(x);
		else if(str[0]=='A')
			fhq.change(x);
		else if(str[0]=='S')
			fhq.change(-x);
		else if(str[0]=='F')
			printf("%d\n",fhq.getnum(x));
	}
	printf("%d\n",fhq.ans);
	return 0;
}
