#include <cstdio>
#include <algorithm>
#define re register
#define ll long long
using namespace std;
template <typename T>
inline void read(T &x)
{
	x=0;
	char s=(char)getchar();
	bool flag=false;
	while(s<'0'||s>'9')
	{
		if(s=='-')
			flag=true;
		s=(char)getchar();
	}
	while(s>='0'&&s<='9')
	{
		x=(x<<1)+(x<<3)+(s^'0');
		s=(char)getchar();
	}
	if(flag)
		x=~x+1;
	return;
}
const int N=5e4+5;
struct Tree
{
	int size,ans,suf,pre;
	int lazy;
} tree[N*4];
#define lc (rt<<1)
#define rc (rt<<1|1)
inline void pushdown(int rt)
{
	if(tree[rt].lazy==-1)
		return;
	tree[lc].pre=tree[lc].suf=tree[lc].ans=tree[lc].size*tree[rt].lazy;
	tree[rc].pre=tree[rc].suf=tree[rc].ans=tree[rc].size*tree[rt].lazy;
	tree[lc].lazy=tree[rc].lazy=tree[rt].lazy;
	tree[rt].lazy=-1;
}
inline void pushup(int rt)
{
	tree[rt].ans=max(max(tree[lc].ans,tree[rc].ans),tree[lc].suf+tree[rc].pre);
	if(tree[lc].ans==tree[lc].size)
		tree[rt].pre=tree[lc].size+tree[rc].pre;
	else
		tree[rt].pre=tree[lc].pre;
	if(tree[rc].ans==tree[rc].size)
		tree[rt].suf=tree[lc].suf+tree[rc].size;
	else
		tree[rt].suf=tree[rc].suf;
}
inline void build(int rt,int l,int r)
{
	tree[rt].size=r-l+1;
	if(l==r)
		return;
	int mid=(l+r)>>1;
	build(lc,l,mid);
	build(rc,mid+1,r);
}
inline void update(int rt,int l,int r,int x,int y,int val)
{
	if(r<x||l>y)
		return;
	if(x<=l&&r<=y)
	{
		tree[rt].pre=tree[rt].suf=tree[rt].ans=tree[rt].size*val;
		tree[rt].lazy=val;
		return;
	}
	pushdown(rt);
	int mid=(l+r)>>1;
	update(lc,l,mid,x,y,val);
	update(rc,mid+1,r,x,y,val);
	pushup(rt);
}
inline int query(int rt,int l,int r,int len)
{
	if(l==r)
		return l;
	pushdown(rt);
	int mid=(l+r)>>1;
	if(tree[lc].ans>=len)
		return query(lc,l,mid,len);
	else if(tree[lc].suf+tree[rc].pre>=len)
		return mid-tree[lc].suf+1;
	else
		return query(rc,mid+1,r,len);
}
int n,m;
int main()
{
	read(n),read(m);
	build(1,1,n);
	update(1,1,n,1,n,1);
	while(m--)
	{
		int opt;
		read(opt);
		if(opt==1)
		{
			int len;
			read(len);
			if(tree[1].ans>=len)
			{
				int left=query(1,1,n,len);
				printf("%d\n",left);
				update(1,1,n,left,left+len-1,0);
			}
			else
				printf("0\n");
		}
		else if(opt==2)
		{
			int pos,len;
			read(pos),read(len);
			update(1,1,n,pos,pos+len-1,1);
		}
	}
}
