#include <set>
#include <map>
#include <cmath>
#include <queue>
#include <vector>
#include <cstdio>
#include <bitset>
#include <cstring>
#include <iostream>
#include <algorithm>
#define lowbit(x) (x&(-x))
#define re register
#define ll long long
#define ull unsigned long long
#define rep(i,a,b) for(re int i=a;i<=b;++i)
#define per(i,a,b) for(re int i=a;i>=b;--i)
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
template<typename T,typename ...T1>
inline void read(T&x,T1&...x1)
{
	read(x);
	read(x1...);
}
template<typename T>
inline void clear(T*a,int l,int r,T val)
{
	memset(&a[l],val,sizeof(T)*(r-l+1));
}
const int N=1e3+5,INF=0x7fffffff;
int n,m,q;
class Segmenty
{
	public:
		struct Tree
		{
			int max,tag;
		} tree[N*3];
#define lc (rt<<1)
#define rc (rt<<1|1)
		inline void update(int rt,int l,int r,pair<int,int>pos,int val)
		{
			if(r<pos.first||l>pos.second)
				return;
			tree[rt].max=max(tree[rt].max,val);
			if(pos.first<=l&&r<=pos.second)
			{
				tree[rt].tag=max(tree[rt].tag,val);
				return;
			}
			int mid=(l+r)>>1;
			update(lc,l,mid,pos,val);
			update(rc,mid+1,r,pos,val);
		}
		inline int query(int rt,int l,int r,pair<int,int>pos)
		{
			if(r<pos.first||l>pos.second)
				return ~INF;
			if(pos.first<=l&&r<=pos.second)
				return tree[rt].max;
			int mid=(l+r)>>1;
			return max(tree[rt].tag,max(query(lc,l,mid,pos),query(rc,mid+1,r,pos)));
		}
};
class Segmentx
{
	public:
		struct Tree
		{
			Segmenty max,tag;
		} tree[N*3];
		inline void update(int rt,int l,int r,pair<int,int>x,pair<int,int>y,int val)
		{
			if(r<x.first||l>x.second)
				return;
//			printf("%d %d\n",l,r);
			tree[rt].max.update(1,0,m-1,y,val);
			if(x.first<=l&&r<=x.second)
			{
				tree[rt].tag.update(1,0,m-1,y,val);
				return;
			}
			int mid=(l+r)>>1;
			update(lc,l,mid,x,y,val);
			update(rc,mid+1,r,x,y,val);
		}
		inline int query(int rt,int l,int r,pair<int,int>x,pair<int,int>y)
		{
			if(r<x.first||l>x.second)
				return -INF;
			if(x.first<=l&&r<=x.second)
				return tree[rt].max.query(1,0,m-1,y);
			int mid=(l+r)>>1;
			return max(tree[rt].tag.query(1,0,m-1,y),max(query(lc,l,mid,x,y),query(rc,mid+1,r,x,y)));
		}
} tree;
signed main()
{
	read(n,m,q);
	while(q--)
	{
		int d,s,w,x,y;
		read(d,s,w,x,y);
		tree.update(1,0,n-1,make_pair(x,x+d-1),make_pair(y,y+s-1),tree.query(1,0,n-1,make_pair(x,x+d-1),make_pair(y,y+s-1))+w);
//		printf("need:%d %d %d %d\n",x,y,x+d-1,y+s-1);
	}
	printf("%d\n",tree.query(1,0,n-1,make_pair(0,n-1),make_pair(0,m-1)));
	return 0;
}


