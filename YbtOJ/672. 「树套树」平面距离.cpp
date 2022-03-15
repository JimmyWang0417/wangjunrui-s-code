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
const int N=2e5+5,base=1e5,M=2e5;
struct Tree
{
	int l,r;
	int size;
} tree[N*400];
int root[N],cnt;
#define lc(x) tree[x].l
#define rc(x) tree[x].r
struct Point
{
	int x,y,tim;
} point[N];
inline void update(int &rt,int l,int r,int pos)
{
	if(!rt)
		rt=++cnt;
	++tree[rt].size;
	if(l==r)
		return;
	int mid=(l+r)>>1;
	if(pos<=mid)
		update(lc(rt),l,mid,pos);
	else
		update(rc(rt),mid+1,r,pos);
}
inline void update(int rt,int pos)
{
	for(int i=rt; i<=M; i+=lowbit(i))
		update(root[i],1,M,pos);
}
inline int query(int rt,int l,int r,int x,int y)
{
	if(r<x||l>y)
		return 0;
	if(x<=l&&r<=y)
		return tree[rt].size;
	int mid=(l+r)>>1;
	return query(lc(rt),l,mid,x,y)+query(rc(rt),mid+1,r,x,y);
}
inline int query(int rt,int x,int y)
{
	int ans=0;
	for(int i=rt; i; i-=lowbit(i))
		ans+=query(root[i],1,M,x,y);
	return ans;
}
int n,q;
int a[N];
signed main()
{
	freopen("light.in","r",stdin);
	freopen("light.out","w",stdout);
	read(n,q);
	for(int i=1; i<=n; ++i)
	{
		read(a[i]);
		update(i-a[i]+base,i+a[i]);
	}
	char opt[10];
	for(int i=1; i<=q; ++i)
	{
		scanf("%s",opt);
		if(opt[0]=='M')
		{
			int x,k;
			read(x,k);
			a[x]=k;
			update(x-a[x]+base,x+k);
		}
		else if(opt[0]=='Q')
		{
			int x,k;
			read(x,k);
			int xl=max(x-a[x]-k+base,1),
			    xr=min(x-a[x]+k+base,M),
			    yl=max(x+a[x]-k,1),
			    yr=min(x+a[x]+k,M);
			printf("%d\n",query(xr,yl,yr)-query(xl-1,yl,yr));
		}
	}
	return 0;
}


