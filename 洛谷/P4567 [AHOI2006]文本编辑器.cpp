#include <ctime>
#include <cstdio>
#include <algorithm>
#define ll long long
#define re register
using namespace std;
template<typename T>
inline void read(T&x)
{
	x=0;
	char ch=(char)getchar();
	bool f=false;
	while(!(ch>='0'&&ch<='9'))
	{
		if(ch=='-')
			f=true;
		ch=(char)getchar();
	}
	while(ch>='0'&&ch<='9')
	{
		x=(x<<1)+(x<<3)+ch-'0';
		ch=(char)getchar();
	}
	if(f)
		x=(~x)+1;
}
const int N=(1<<24)+5;
struct Tree
{
	int l,r,size;
	char val;
	int key;
	bool reverse;
} tree[N];
int cnt,root;
#define lc(x) tree[x].l
#define rc(x) tree[x].r
inline int newnode(char val)
{
	tree[++cnt].val=val;
	tree[cnt].key=rand();
	tree[cnt].size=1;
	return cnt;
}
inline void update(int now)
{
	tree[now].size=tree[lc(now)].size+tree[rc(now)].size+1;
	return;
}
inline void pushdown(int now)
{
	if(!tree[now].reverse)
		return;
	if(lc(now))
		tree[lc(now)].reverse^=1;
	if(rc(now))
		tree[rc(now)].reverse^=1;
	tree[now].reverse=false;
	swap(lc(now),rc(now));
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
			split(rc(now),size-tree[lc(now)].size-1,rc(now),y);
		}
		else
		{
			y=now;
			split(lc(now),size,x,lc(now));
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
int sta[N];
inline int build(int tot)
{
	int tp;
	char ch=(char)getchar();
	while((ch<32||ch>126)&&ch!='\n')
		ch=(char)getchar();
	sta[tp=1]=newnode(ch);
	for(re int i=1; i<tot; ++i)
	{
		ch=(char)getchar();
		while((ch<32||ch>126)&&ch!='\n')
			ch=(char)getchar();
		int last=0,cur=newnode(ch);
		while(tp&&tree[cur].key>tree[sta[tp]].key)
		{
			update(sta[tp]);
			last=sta[tp--];
		}
		lc(cur)=last;
		update(cur);
		if(tp)
		{
			rc(sta[tp])=cur;
			update(sta[tp]);
		}
		sta[++tp]=cur;
	}
	while(tp)
		update(sta[tp--]);
	return sta[1];
}
inline void dfs(int now)
{
	if(!now)
		return;
	pushdown(now);
	dfs(lc(now));
	putchar(tree[now].val);
	dfs(rc(now));
}
inline void print(int now)
{
	dfs(now);
	putchar('\n');
}
char str[100];
int pos;
inline void work()
{
	scanf("%s",str);
	if(str[0]=='M')
	{
		int n;
		read(n);
		pos=n;
	}
	else if(str[0]=='I')
	{
		int n;
		read(n);
		int x,y;
		split(root,pos,x,y);
		root=merge(x,merge(build(n),y));
	}
	else if(str[0]=='D')
	{
		int n;
		read(n);
		int x,y,z;
		split(root,pos,x,y);
		split(y,n,y,z);
		root=merge(x,z);
	}
	else if(str[0]=='R')
	{
		int n;
		read(n);
		int x,y,z;
		split(root,pos,x,y);
		split(y,n,y,z);
		tree[y].reverse^=1;
		root=merge(x,merge(y,z));
	}
	else if(str[0]=='G')
	{
		int x,y,z;
		split(root,pos,x,y);
		split(y,1,y,z);
		if(tree[y].val!='\n')
			putchar(tree[y].val);
		putchar('\n');
		root=merge(x,merge(y,z));
	}
	else if(str[0]=='P')
		--pos;
	else if(str[0]=='N')
		++pos;
//	printf("%d ",pos),print(root);
}
int m;
int main()
{
	srand((unsigned int)time(0));
	read(m);
	while(m--)
		work();
	return 0;
}
