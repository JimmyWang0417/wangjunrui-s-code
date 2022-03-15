#include <ctime>
#include <cstdio>
#include <random>
#include <algorithm>
#define re register
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
const int N=500000+5,INF=0x3f3f3f3f;
struct Tree
{
	int l,r,size;
	int val,key;
	int sum,ans,suf,pre;
	bool reverse,lazy;
} tree[N];
mt19937 rnd((unsigned int)time(0));
#define lc(now) tree[now].l
#define rc(now) tree[now].r
int recycle[N],top;
int cnt,root;
inline int newnode(int val)
{
	int now=top?recycle[top--]:++cnt;
	tree[now].key=rnd();
	tree[now].val=tree[now].suf=tree[now].sum=tree[now].pre=tree[now].ans=val;
	tree[now].size=1;
	lc(now)=rc(now)=0;
	tree[now].reverse=tree[now].lazy=false;
	return now;
}
inline void _lazy(int now,int val)
{
	if(!now)
		return;
	tree[now].val=val;
	tree[now].suf=tree[now].pre=tree[now].ans=max(val,tree[now].sum=tree[now].size*val);
	tree[now].lazy=true;
}
inline void _reverse(int now)
{
	if(!now)
		return;
	tree[now].reverse^=1;
	swap(tree[now].suf,tree[now].pre);
}
inline void update(int now)
{
	tree[now].size=tree[lc(now)].size+tree[rc(now)].size+1;
	tree[now].sum=tree[lc(now)].sum+tree[rc(now)].sum+tree[now].val;
	tree[now].pre=max(tree[lc(now)].pre,tree[lc(now)].sum+tree[now].val+max(tree[rc(now)].pre,0));
	tree[now].suf=max(tree[rc(now)].suf,tree[rc(now)].sum+tree[now].val+max(tree[lc(now)].suf,0));
	tree[now].ans=max(max(tree[lc(now)].ans,tree[rc(now)].ans),max(0,tree[lc(now)].suf)+tree[now].val+max(tree[rc(now)].pre,0));
}
inline void pushdown(int now)
{
	if(tree[now].reverse)
	{
		_reverse(lc(now));
		_reverse(rc(now));
		swap(lc(now),rc(now));
		tree[now].reverse=false;
	}
	if(tree[now].lazy)
	{
		_lazy(lc(now),tree[now].val);
		_lazy(rc(now),tree[now].val);
		tree[now].lazy=false;
	}
}
int sta[N];
inline int build(int tot)
{
	re int size;
	int val;
	read(val);
	sta[size=1]=newnode(val);
	for(re int i=1; i<tot; ++i)
	{
		read(val);
		int last=0,cur=newnode(val);
		while(size&&tree[cur].key>tree[sta[size]].key)
		{
			update(sta[size]);
			last=sta[size];
			sta[size--]=0;
		}
		lc(cur)=last;
		update(cur);
		if(size)
		{
			rc(sta[size])=cur;
			update(sta[size]);
		}
		sta[++size]=cur;
	}
	while(size)
		update(sta[size--]);
	return sta[1];
}
inline void split(int now,int size,int &x,int &y)
{
	if(!now)
		x=y=0;
	else
	{
		pushdown(now);
		if(tree[lc(now)].size<size)
		{
			x=now;
			split(tree[now].r,size-tree[lc(now)].size-1,tree[now].r,y);
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
		return x|y;
	if(tree[x].key>tree[y].key)
	{
		pushdown(x);
		rc(x)=merge(rc(x),y);
		update(x);
		return x;
	}
	else
	{
		pushdown(y);
		lc(y)=merge(x,lc(y));
		update(y);
		return y;
	}
}
inline void insert(int pos,int tot)
{
	int x,y;
	split(root,pos,x,y);
	root=merge(merge(x,build(tot)),y);
}
inline void rebuild(int now)
{
	if(lc(now))
		rebuild(lc(now));
	recycle[++top]=now;
	if(rc(now))
		rebuild(rc(now));
}
inline void del(int pos,int tot)
{
	int x,y,z;
	split(root,pos-1,x,y);
	split(y,tot,y,z);
	rebuild(y);
	root=merge(x,z);
}
inline void makesame(int pos,int tot)
{
	int x,y,z,val;
	read(val);
	split(root,pos-1,x,y);
	split(y,tot,y,z);
	_lazy(y,val);
	root=merge(x,merge(y,z));
}
inline void reverse(int pos,int tot)
{
	int x,y,z;
	split(root,pos-1,x,y);
	split(y,tot,y,z);
	_reverse(y);
	root=merge(x,merge(y,z));
}
inline void getsum(int pos,int tot)
{
	int x,y,z;
	split(root,pos-1,x,y);
	split(y,tot,y,z);
	printf("%d\n",tree[y].sum);
	root=merge(x,merge(y,z));
}
inline void maxsum()
{
	printf("%d\n",tree[root].ans);
}

//inline void dfs(int now)
//{
//	pushdown(now);
//	if(lc(now))
//		dfs(lc(now));
//	printf("%d ",tree[now].val);
//	if(rc(now))
//		dfs(rc(now));
//}
//inline void print(int now)
//{
//	dfs(now);
//	putchar('\n');
//}

char str[20];
int n,m;
int main()
{
//	printf("%lld\n",sizeof(tree)+sizeof recycle);
	tree[0].ans=tree[0].pre=tree[0].suf=-INF;
	read(n),read(m);
	root=build(n);
//	print(root);
	while(m--)
	{
//		print(root);
		scanf("%s",str);
		if(str[0]=='M'&&str[2]=='X')
		{
			maxsum();
			continue;
		}
		int pos,tot;
		read(pos),read(tot);
		switch(str[0])
		{
			case 'I':
				insert(pos,tot);
				break;
			case 'D':
				del(pos,tot);
				break;
			case 'M':
				makesame(pos,tot);
				break;
			case 'R':
				reverse(pos,tot);
				break;
			case 'G':
				getsum(pos,tot);
				break;
		}
	}
	return 0;
}
