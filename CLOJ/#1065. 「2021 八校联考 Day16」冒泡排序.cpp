#include <bits/stdc++.h>
#define lowbit(x) ((x)&(-(x)))
#define re register
#define ll long long
#define ull unsigned long long
#define rep(i,a,b) for(re int i=a;i<=b;++i)
#define per(i,a,b) for(re int i=a;i>=b;--i)
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
template<typename T,typename ...T1>
inline void read(T&x,T1&...x1)
{
	read(x);
	read(x1...);
}
template<typename T>
inline void clear(T*array,int l,int r,int val)
{
	memset(&array[l],val,sizeof(T)*(r-l+1));
}
using namespace std;
const int N=1e6+5,INF=0x7fffffff;
struct Tree
{
	int min,max;
	int add;
	inline void update(int _add)
	{
		add+=_add;
		min+=_add;
		max+=_add;
	}
} tree[N*4];
#define lc (rt<<1)
#define rc (rt<<1|1)
int n,m,a[N],b[N];
inline void pushup(int rt)
{
	tree[rt].min=min(tree[lc].min,tree[rc].min);
	tree[rt].max=max(tree[lc].max,tree[rc].max);
}
inline void pushdown(int rt)
{
	if(tree[rt].add)
	{
		tree[lc].update(tree[rt].add);
		tree[rc].update(tree[rt].add);
		tree[rt].add=0;
	}
}
inline void update(int rt,int l,int r,int x,int y,int val)
{
	if(r<x||l>y)
		return;
	if(x<=l&&r<=y)
		return tree[rt].update(val);
	int mid=(l+r)>>1;
	pushdown(rt);
	update(lc,l,mid,x,y,val);
	update(rc,mid+1,r,x,y,val);
	pushup(rt);
}
signed main()
{
	read(n,m);
	for(int i=1; i<=n; ++i)
		read(a[i]);
	for(int i=1; i<=n; ++i)
		update(1,1,1e6,a[i],1e6,(i&1)?1:-1);
	for(int i=1; i<=m; ++i)
	{
		int x,y;
		read(x,y);
		if(x&1)
		{
			update(1,1,1e6,a[x],1e6,-1);
			update(1,1,1e6,a[x]=y,1e6,1);
		}
		else
		{
			update(1,1,1e6,a[x],1e6,1);
			update(1,1,1e6,a[x]=y,1e6,-1);
		}
		if(0<=tree[1].min&&tree[1].max<=1)
			printf("Yes\n");
		else
			printf("No\n");
	}
	return 0;
}


