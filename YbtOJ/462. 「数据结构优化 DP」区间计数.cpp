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
const int N=3e5+5,INF=0x3f3f3f3f;
struct node
{
	int min1,cnt1,min2,cnt2;
	node(int _min=INF,int _cntmin=0,int _min1=INF,int _cntmin1=0):
		min1(_min),cnt1(_cntmin),min2(_min1),cnt2(_cntmin1) {}
	inline node friend operator +(node a,node b)
	{
		if(a.min1>b.min1)
			swap(a,b);
		if(a.min2<b.min1)
			return a;
		if(a.min2==b.min1)
		{
			a.cnt2+=b.cnt1;
			return a;
		}
		else if(a.min1==b.min1)
		{
			a.cnt1+=b.cnt1;
			if(a.min2>b.min2)
				return node(a.min1,a.cnt1,b.min2,b.cnt2);
			else
			{
				if(a.min2==b.min2)
					a.cnt2+=b.cnt2;
				return a;
			}
		}
		else
			return node(a.min1,a.cnt1,b.min1,b.cnt1);
	}
	inline void print()
	{
		printf("%d %d %d %d\n",min1,cnt1,min2,cnt2);
	}
} tree[N*4];
int tag[N*4];
inline void update(int rt,int val)
{
	tree[rt].min1+=val;
	tree[rt].min2+=val;
	tag[rt]+=val;
}
#define lc (rt<<1)
#define rc (rt<<1|1)
inline void pushdown(int rt)
{
	if(tag[rt])
	{
		update(lc,tag[rt]);
		update(rc,tag[rt]);
		tag[rt]=0;
	}
}
inline void pushup(int rt)
{
	tree[rt]=tree[lc]+tree[rc];
}
inline void build(int rt,int l,int r)
{
	if(l==r)
	{
		tree[rt]=node(0,1,INF,0);
		return;
	}
	int mid=(l+r)>>1;
	build(lc,l,mid);
	build(rc,mid+1,r);
	pushup(rt);
}
inline void update(int rt,int l,int r,int x,int y,int val)
{
	if(r<x||l>y)
		return;
	if(x<=l&&r<=y)
	{
		update(rt,val);
		return;
	}
	int mid=(l+r)>>1;
	pushdown(rt);
	update(lc,l,mid,x,y,val);
	update(rc,mid+1,r,x,y,val);
	pushup(rt);
}
inline node query(int rt,int l,int r,int x,int y)
{
	if(r<x||l>y)
		return node();
	if(x<=l&&r<=y)
		return tree[rt];
	int mid=(l+r)>>1;
	pushdown(rt);
	node left=query(lc,l,mid,x,y),right=query(rc,mid+1,r,x,y);
	node ans=left+right;
	return ans;
}
inline void print(int rt,int l,int r)
{
	if(l==r)
		return;
	int mid=(l+r)>>1;
	pushdown(rt);
	print(lc,l,mid);
	print(rc,mid+1,r);
	pushup(rt);
}
int n,a[N],pos[N];
inline void print()
{
	print(1,1,n);
}
signed main()
{
	freopen("interval.in","r",stdin),freopen("interval.out","w",stdout);
	read(n);
	for(int i=1; i<=n; ++i)
	{
		read(a[i]);
		pos[a[i]]=i;
	}
	build(1,1,n);
	ll ans=0;
	for(int i=n; i>=1; --i)
	{
		int l=a[pos[i]-1],r=a[pos[i]+1];
		if(l>r)
			swap(l,r);
		if(l<i&&i<r)
			update(1,1,n,i,r-1,1);
		else if(r<i)
			update(1,1,n,i,n,1);
		else
		{
			update(1,1,n,i,l-1,1);
			update(1,1,n,r,n,-1);
		}
		node now=query(1,1,n,i+1,n);
		if(now.min1==1||now.min1==2)
			ans+=now.cnt1;
		if(now.min2==1||now.min2==2)
			ans+=now.cnt2;
	}
	printf("%lld\n",ans);
	return 0;
}

