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
const int N=5e5+5;
inline int gcd(int n,int m)
{
	if(m==0)
		return n;
	return gcd(m,n%m);
}
struct Tree
{
	int gcd;
} tree[N*4];
#define lc (rt<<1)
#define rc (rt<<1|1)
int n,m,a[N];
inline void pushup(int rt)
{
	tree[rt].gcd=gcd(tree[lc].gcd,tree[rc].gcd);
}
inline void build(int rt,int l,int r)
{
	if(l==r)
	{
		tree[rt].gcd=a[l];
		return;
	}
	int mid=(l+r)>>1;
	build(lc,l,mid);
	build(rc,mid+1,r);
	pushup(rt);
}
inline void update(int rt,int l,int r,int pos,int val)
{
	if(l==r)
	{
		tree[rt].gcd=val;
		return;
	}
	int mid=(l+r)>>1;
	if(pos<=mid)
		update(lc,l,mid,pos,val);
	else
		update(rc,mid+1,r,pos,val);
	pushup(rt);
}
int cnt=0;
inline void query(int rt,int l,int r,int x,int y,int val)
{
	if(cnt>1)
		return;
	if(l==r)
	{
		++cnt;
		return;
	}
	int mid=(l+r)>>1;
	if((tree[lc].gcd%val&&x<=mid))
		query(lc,l,mid,x,y,val);
	if(tree[rc].gcd%val&&y>mid)
		query(rc,mid+1,r,x,y,val);
	return;
}
signed main()
{
	read(n);
	for(int i=1; i<=n; ++i)
		read(a[i]);
	build(1,1,n);
	read(m);
	while(m--)
	{
		int opt;
		read(opt);
		if(opt==1)
		{
			int l,r,x;
			read(l,r,x);
			cnt=0;
			query(1,1,n,l,r,x);
			puts(cnt<=1?"YES":"NO");
		}
		else
		{
			int x,y;
			read(x,y);
			update(1,1,n,x,y);
		}
	}
	return 0;
}


