#include<cstdio>
#include<algorithm>
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

const int N=1e5+5,M=2e5+5;
class Persistent_union_find
{
	private:

		int cnt;
		int n,m;
		int root[M];
		struct Tree
		{
			int lc,rc;
			int dep,fa;
		} tree[N*40];
		inline void build(int &rt,int l,int r)
		{
			rt=++cnt;
			if(l==r)
			{
				tree[rt].fa=l;
				return;
			}
			int mid=(l+r)>>1;
			build(tree[rt].lc,l,mid);
			build(tree[rt].rc,mid+1,r);
			return;
		}
		inline void merge(int last,int &rt,int l,int r,int pos,int fa)
		{
			rt=++cnt;
			tree[rt]=tree[last];
			if(l==r)
			{
				tree[rt].fa=fa;
				return;
			}
			int mid=(l+r)>>1;
			if(pos<=mid)
				merge(tree[last].lc,tree[rt].lc,l,mid,pos,fa);
			else merge(tree[last].rc,tree[rt].rc,mid+1,r,pos,fa);
		}
		inline void update(int rt,int l,int r,int pos)
		{
			if(l==r)
			{
				++tree[rt].dep;
				return;
			}
			int mid=(l+r)>>1;
			if(pos<=mid)
				update(tree[rt].lc,l,mid,pos);
			else
				update(tree[rt].rc,mid+1,r,pos);
		}
		inline int query(int rt,int l,int r,int pos)
		{
			if(l==r)
				return rt;
			int mid=(l+r)>>1;
			return pos<=mid?query(tree[rt].lc,l,mid,pos):query(tree[rt].rc,mid+1,r,pos);
		}
		inline int find(int rt,int pos)
		{
			int now=query(rt,1,n,pos);
			if(tree[now].fa==pos)
				return now;
			return find(rt,tree[now].fa);
		}
	public:

		inline void work()
		{
			read(n),read(m);
			build(root[0],1,n);
			for(re int i=1; i<=m; ++i)
			{
				int opt;
				read(opt);
				if(opt==1)
				{
					int x,y;
					root[i]=root[i-1];
					read(x),read(y);
					int posx=find(root[i],x),posy=find(root[i],y);
					if(tree[posx].fa!=tree[posy].fa)
					{
						if(tree[posx].dep>tree[posy].dep)
							swap(posx,posy);
						merge(root[i-1],root[i],1,n,tree[posx].fa,tree[posy].fa);
						if(tree[posx].dep==tree[posy].dep)
							update(root[i],1,n,tree[posy].fa);
					}
				}
				else if(opt==2)
				{
					int k;
					read(k);
					root[i]=root[k];
				}
				else if(opt==3)
				{
					int x,y;
					root[i]=root[i-1];
					read(x),read(y);
					int posx=find(root[i],x),posy=find(root[i],y);
					printf("%d\n",tree[posx].fa==tree[posy].fa);
				}
			}
			return;
		}
} unionn;
int main()
{
	unionn.work();
	return 0;
}
