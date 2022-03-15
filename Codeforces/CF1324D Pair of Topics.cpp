#include<cstdio>
#include<set>
#include<random>
#include<ctime>
#include<iostream>
#include<cstring>
#define re register
#define ll long long
#define int ll
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
	return;
}
const int N=2e5+5;
int n,a[N],b[N];
mt19937 rnd((unsigned int)time(0));
struct Tree
{
	int val,key,size;
	int l,r;
} tree[N];
int cnt,root;
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
	return;
}
inline int merge(int x,int y)
{
	if(!x||!y)
		return x+y;
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

inline void work()
{
	read(n);
	for(re int i=1; i<=n; ++i)
		read(a[i]);
	for(re int i=1; i<=n; ++i)
		read(b[i]);
	int ans=0;
	for(re int i=1; i<=n; ++i)
	{
		int x,y;
		split(root,a[i]-b[i]-1,x,y);
		ans+=tree[x].size;
		root=merge(x,y);
		split(root,b[i]-a[i]-1,x,y);
		root=merge(x,merge(newnode(b[i]-a[i]),y));
	}
	printf("%lld\n",ans);
}
signed main()
{
	work();
	return 0;
}
