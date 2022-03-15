#include <ctime>
#include <cstdio>
#include <random>
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
mt19937 rnd((unsigned int)time(0));
const int N=(1<<21)+5;
#define lc(x) tree[x].l
#define rc(x) tree[x].r
struct Tree
{
	char val;
	int key;
	int l,r,size;
} tree[N];
int cnt,root;
inline int newnode(char val)
{
	tree[++cnt].val=val;
	tree[cnt].key=rnd();
	tree[cnt].size=1;
	lc(cnt)=rc(cnt)=0;
	return cnt;
}
inline void update(int now)
{
	tree[now].size=tree[lc(now)].size+tree[rc(now)].size+1;
	return;
}
char str[N];
int sta[N];
inline int build(int n)
{
	char ch;
	int tp;
	for(re int i=0; i<n; ++i)
	{
		ch=(char)getchar();
		while(ch<32||ch>126)
			ch=(char)getchar();
		str[i]=ch;
	}
	sta[tp=1]=newnode(str[0]);
	for(re int i=1; i<n; ++i)
	{
		int last=0,cur=newnode(str[i]);
		while(tp&&tree[cur].key>tree[sta[tp]].key)
		{
			last=sta[tp];
			update(sta[tp--]);
		}
		lc(cur)=last;
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
inline void split(int now,int size,int &x,int &y)
{
	if(!now)
		x=y=0;
	else
	{
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
int pos,m;
inline void dfs(int now)
{
	if(!now)
		return;
	dfs(lc(now));
	putchar(tree[now].val);
	dfs(rc(now));
}
inline void print(int now)
{
	dfs(now);
	putchar('\n');
}
inline void work()
{
//	printf("%d ",id);
	static char s[10];
	scanf("%s",s);
	if(s[0]=='M')
	{
		int n;
		read(n);
		pos=n;
	}
	else if(s[0]=='I')
	{
		int n;
		read(n);
		int x,y;
		split(root,pos,x,y);
		root=merge(x,merge(build(n),y));
	}
	else if(s[0]=='D')
	{
		int n;
		read(n);
		int x,y,z;
		split(root,pos,x,y);
		split(y,n,y,z);
		root=merge(x,z);
	}
	else if(s[0]=='G')
	{
		int n;
		read(n);
		int x,y,z;
		split(root,pos,x,y);
		split(y,n,y,z);
		print(y);
		root=merge(x,merge(y,z));
	}
	else if(s[0]=='P')
		--pos;
	else if(s[0]=='N')
		++pos;
//	print(root);
}
int main()
{
	read(m);
	while(m--)
		work();
	return 0;
}
