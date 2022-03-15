#include <ctime>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <iostream>
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
using namespace std;
const int N=1e5+5;
struct Tree
{
	int l,r,size;
	int val,key;
	int fa;
	int min;
	bool reverse;
} tree[N];
int cnt,root;
int pos[N];
#define lc(x) tree[x].l
#define rc(x) tree[x].r
#define fa(x) tree[x].fa
struct node
{
	int val,id;
	inline bool operator < (const node&rhs)const
	{
		return val<rhs.val;
	}
} QwQ[N];
inline int newnode(int val)
{
	tree[++cnt].val=val;
	tree[cnt].min=val;
	pos[val]=cnt;
	tree[cnt].size=1;
	tree[cnt].key=rand();
	return cnt;
}
inline void pushup(int now)
{
	tree[now].size=tree[lc(now)].size+tree[rc(now)].size+1;
	tree[now].min=min(tree[now].val,min(tree[lc(now)].min,tree[rc(now)].min));
	if(lc(now))
		fa(lc(now))=now;
	if(rc(now))
		fa(rc(now))=now;
}
inline void pushdown(int now)
{
	if(!tree[now].reverse)
		return;
	swap(lc(now),rc(now));
	if(lc(now))
		tree[lc(now)].reverse^=1;
	if(rc(now))
		tree[rc(now)].reverse^=1;
	tree[now].reverse=false;
}
inline void split(int now,int size,int &x,int &y)
{
	if(!now)
		x=y=0;
	else
	{
		pushdown(now);
		if(size>tree[lc(now)].size)
		{
			x=now;
			split(rc(now),size-tree[lc(now)].size-1,rc(now),y);
		}
		else
		{
			y=now;
			split(lc(now),size,x,lc(now));
		}
		pushup(now);
	}
}
inline int merge(int x,int y)
{
	if(!x||!y)
		return x|y;
	if(tree[x].key>tree[y].key)
	{
		pushdown(x);
		rc(x)=merge(rc(x),y);
		pushup(x);
		return x;
	}
	else
	{
		pushdown(y);
		lc(y)=merge(x,lc(y));
		pushup(y);
		return y;
	}
}
inline int query(int now)
{
	pushdown(now);
	const int &res=tree[now].min;
	if(res==tree[lc(now)].min)
		return query(lc(now));
	else if(res==tree[rc(now)].min)
		return tree[lc(now)].size+1+query(rc(now));
	else
		return tree[lc(now)].size+1;
}
inline void dfs(int now)
{
	if(!now)
		return;
	pushdown(now);
	dfs(lc(now));
	printf("%d ",tree[now].val);
	dfs(rc(now));
}
inline void print(int now)
{
	dfs(now);
	putchar('\n');
}
int n,a[N];
int main()
{
	srand((unsigned)time(0));
	tree[0].min=0x7fffffff;
	read(n);
	for(re int i=1; i<=n; ++i)
	{
		read(QwQ[i].val);
		QwQ[i].id=i;
	}
	sort(QwQ+1,QwQ+1+n);
	for(re int i=1; i<=n; ++i)
		a[QwQ[i].id]=i;
	for(re int i=1; i<=n; ++i)
		root=merge(root,newnode(a[i]));
	for(re int i=1; i<=n; ++i)
	{
		int where=query(root);
		printf("%d ",where+i-1);
		int x,y,z;
		split(root,where-1,x,y);
		split(y,1,y,z);
		tree[x].reverse^=1;
		root=merge(x,z);
//		print(root);
	}
	putchar('\n');
	return 0;
}
