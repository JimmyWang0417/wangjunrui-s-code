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
const int N=1e6+5;
int n,m;
int car[N];
struct Tree
{
	int l,r;
	int size;
	int lmax,rmax,max,maxpos;
} tree[N*4];
#define lc (rt<<1)
#define rc (rt<<1|1)
inline void build(int rt,int l,int r)
{
	tree[rt].l=l,tree[rt].r=r;
	tree[rt].lmax=tree[rt].rmax=tree[rt].max=tree[rt].size=r-l+1;
	tree[rt].maxpos=l;
	if(l==r)
		return;
	int mid=(l+r)>>1;
	build(lc,l,mid);
	build(rc,mid+1,r);
}
inline int calc(int len)
{
	if(!len)
		return 0;
	return (len-1)/2+1;
}
inline void update(int rt,int pos,int len)
{
	int pre=calc(tree[rt].max),now=calc(len);
	if(pre<now)
	{
		tree[rt].max=len;
		tree[rt].maxpos=pos;
	}
	else if(pre==now&&tree[rt].maxpos>pos)
		tree[rt].maxpos=pos;
}
inline void pushup(int rt)
{
	if(tree[lc].lmax==tree[lc].size)
		tree[rt].lmax=tree[lc].size+tree[rc].lmax;
	else
		tree[rt].lmax=tree[lc].lmax;
	if(tree[rc].rmax==tree[rc].size)
		tree[rt].rmax=tree[lc].rmax+tree[rc].size;
	else
		tree[rt].rmax=tree[rc].rmax;
	tree[rt].max=0;
	update(rt,tree[lc].r-tree[lc].rmax+1 ,tree[lc].rmax+tree[rc].lmax);
	update(rt,tree[lc].maxpos,tree[lc].max);
	update(rt,tree[rc].maxpos,tree[rc].max);
}
inline void update(int rt,int l,int r,int pos,int val)
{
	if(l==r)
	{
		tree[rt].lmax=tree[rt].rmax=tree[rt].max=val;
		if(val)
			tree[rt].maxpos=l;
		else
			tree[rt].maxpos=0;
		return;
	}
	int mid=(l+r)>>1;
	if(pos<=mid)
		update(lc,l,mid,pos,val);
	else
		update(rc,mid+1,r,pos,val);
	pushup(rt);
}
inline int query()
{
	int len=(tree[1].max-1)/2+1,res=(tree[1].maxpos*2+tree[1].max-1)/2;
	if(tree[1].lmax>=len)
		res=1;
	else if(tree[1].rmax>len)
		res=n;
	return res;
}
signed main()
{
	freopen("park.in","r",stdin);
	freopen("park.out","w",stdout);
	read(n,m);
	build(1,1,n);
	for(int i=1; i<=m; ++i)
	{
		int opt,x;
		read(opt,x);
		if(opt==1)
		{
			car[x]=query();
			update(1,1,n,car[x],0);
			printf("%d\n",car[x]);
		}
		else
			update(1,1,n,car[x],1);
	}
	return 0;
}


