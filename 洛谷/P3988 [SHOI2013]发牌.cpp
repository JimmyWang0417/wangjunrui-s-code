#include <ctime>
#include <cstdio>
#include <random>
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
const int N=7e5+5;
struct Tree
{
	int l,r,size;
	int val,key;
} tree[N];
#define lc(x) tree[x].l
#define rc(x) tree[x].r
mt19937 rnd((unsigned int)time(0));
int root,cnt;
inline int newnode(int val)
{
	tree[++cnt].val=val;
	tree[cnt].key=rnd();
	tree[cnt].size=1;
	return cnt;
}
inline void update(int now)
{
	tree[now].size=tree[lc(now)].size+tree[rc(now)].size+1;
	return;
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
			split(rc(now),size-tree[lc(now)].size-1,rc(x),y);
		}
		else
		{
			y=now;
			split(lc(now),size,x,lc(y));
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
inline void dfs(int now)
{
	if(!now)
		return;
	dfs(lc(now));
	printf("%d ",tree[now].val);
	dfs(rc(now));
}
inline void print(int now)
{
	dfs(now);
	putchar('\n');
}
int n;
int main()
{
	read(n);
	for(re int i=1; i<=n; ++i)
		root=merge(root,newnode(i));
//	printf("%d\n",tree[root].size);
	while(n--)
	{
		int val;
		read(val);
		val%=tree[root].size;
		int x,y,z;
		split(root,val,x,y);
		split(y,1,y,z);
		printf("%d\n",tree[y].val);
		root=merge(z,x);
	}
	return 0;
}
