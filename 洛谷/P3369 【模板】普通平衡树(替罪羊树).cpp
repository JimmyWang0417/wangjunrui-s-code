#include <cstdio>
#include <algorithm>
#define ll long long
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
using std::max;
const int N=1e5+5;
const double alpha=0.75;
struct Tree
{
	int l,r,val;
	int size,fact;
	bool exist;
} tree[N];
#define lc(x) tree[x].l
#define rc(x) tree[x].r
int cnt,root;
inline void newnode(int &now,int val)
{
	now=++cnt;
	tree[now].val=val;
	tree[now].size=tree[cnt].fact=1;
	tree[now].exist=true;
}
inline bool imbalence(int now)
{
	return max(tree[lc(now)].size,tree[rc(now)].size)>tree[now].size*alpha||
	       tree[now].size-tree[now].fact>tree[now].size*0.3;
}
int sta[N],top;
inline void ldr(int now)
{
	if(!now)
		return;
	ldr(lc(now));
	if(tree[now].exist)
		sta[++top]=now;
	ldr(rc(now));
}
inline void lift(int l,int r,int &now)
{
	if(l==r)
	{
		now=sta[l];
		lc(now)=rc(now)=0;
		tree[now].size=tree[now].fact=1;
		return;
	}
	int mid=(l+r)>>1;
	while(l<mid&&tree[sta[mid]].val==tree[sta[mid-1]].val)
		--mid;
	now=sta[mid];
	if(l<mid)
		lift(l,mid-1,lc(now));
	else lc(now)=0;
	lift(mid+1,r,rc(now));
	tree[now].size=tree[lc(now)].size+tree[rc(now)].size+1;
	tree[now].fact=tree[lc(now)].fact+tree[rc(now)].fact+1;
}
inline void rebuild(int &now)
{
	ldr(now);
	if(!top)
	{
		now=0;
		return;
	}
	lift(1,top,now);
	top=0;
}
inline void update(int now,int end)
{
	if(!now)
		return;
	if(tree[end].val<tree[now].val)
		update(lc(now),end);
	else
		update(rc(now),end);
	tree[now].size=tree[lc(now)].size+tree[rc(now)].size+1;
}
inline void check(int &now,int end)
{
	if(now==end)
		return;
	if(imbalence(now))
	{
		rebuild(now);
		update(root,now);
		return;
	}
	if(tree[end].val<tree[now].val)
		check(lc(now),end);
	else
		check(rc(now),end);
}
inline void insert(int &now,int val)
{
	if(!now)
	{
		newnode(now,val);
		check(root,now);
		return;
	}
	++tree[now].size;
	++tree[now].fact;
	if(val<tree[now].val)
		insert(lc(now),val);
	else
		insert(rc(now),val);
}
inline void del(int now,int val)
{
	if(tree[now].exist&&tree[now].val==val)
	{
		tree[now].exist=false;
		--tree[now].fact;
		check(root,now);
		return;
	}
	--tree[now].fact;
	if(val<tree[now].val)
		del(lc(now),val);
	else
		del(rc(now),val);
}
inline int getrank(int val)
{
	int now=root,rank=1;
	while(now)
	{
		if(val<=tree[now].val)
			now=lc(now);
		else
		{
			rank+=tree[now].exist+tree[lc(now)].fact;
			now=rc(now);
		}
	}
	return rank;
}
inline int getnum(int rank)
{
	int now=root;
	while(now)
	{
		if(tree[now].exist&&tree[lc(now)].fact+tree[now].exist==rank)
			break;
		else if(tree[lc(now)].fact>=rank)
			now=lc(now);
		else
		{
			rank-=tree[lc(now)].fact+tree[now].exist;
			now=rc(now);
		}
	}
	return tree[now].val;
}
int main()
{
	int T;
	read(T);
	while(T--)
	{
		int opt,x;
		read(opt),read(x);
		if(opt==1)
			insert(root,x);
		else if(opt==2)
			del(root,x);
		else if(opt==3)
			printf("%d\n",getrank(x));
		else if(opt==4)
			printf("%d\n",getnum(x));
		else if(opt==5)
			printf("%d\n",getnum(getrank(x)-1));
		else if(opt==6)
			printf("%d\n",getnum(getrank(x+1)));
	}
	return 0;
}
