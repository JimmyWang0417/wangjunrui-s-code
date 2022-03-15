#include <cstdio>
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
const int N=1e6+5,mod=1e9+7;
int n,tot;
int a[N],p[N];
int pre[N],pos[N];
struct Tree
{
	int tag,size;
	ll sum1,sum2;
	inline void update(int vall)
	{
		(sum2+=2ll*vall*sum1+1ll*size*vall*vall)%=mod;
		(sum1+=1ll*vall*size)%=mod;
		(tag+=vall)%=mod;
	}
} tree[N*4];
#define lc (rt<<1)
#define rc (rt<<1|1)
inline void pushup(int rt)
{
	(tree[rt].sum1=tree[lc].sum1+tree[rc].sum1)%=mod;
	(tree[rt].sum2=tree[lc].sum2+tree[rc].sum2)%=mod;
}
inline void pushdown(int rt)
{
	if(tree[rt].tag)
	{
		tree[lc].update(tree[rt].tag);
		tree[rc].update(tree[rt].tag);
		tree[rt].tag=0;
	}
}
inline void build(int rt,int l,int r)
{
	tree[rt].size=r-l+1;
	if(l==r)
		return;
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
		tree[rt].update(val);
		return;
	}
	int mid=(l+r)>>1;
	pushdown(rt);
	update(lc,l,mid,x,y,val);
	update(rc,mid+1,r,x,y,val);
	pushup(rt);
}
inline ll query(int rt,int l,int r,int x,int y)
{
	if(r<x||l>y)
		return 0;
	if(x<=l&&r<=y)
		return tree[rt].sum2;
	int mid=(l+r)>>1;
	pushdown(rt);
	return (query(lc,l,mid,x,y)+query(rc,mid+1,r,x,y))%mod;
}
signed main()
{
//	print();
	read(n);
	for(re int i=1; i<=n; ++i)
	{
		read(a[i]);
		p[i]=a[i];
	}
//	clock_t start = clock();
	build(1,1,n);
	sort(p+1,p+1+n);
	tot=(int)(unique(p+1,p+1+n)-p-1);
	for(re int i=1; i<=n; ++i)
	{
		a[i]=(int)(lower_bound(p+1,p+1+tot,a[i])-p);
		pre[i]=pos[a[i]];
		pos[a[i]]=i;
	}
	ll ans=0;
	for(re int i=1; i<=n; ++i)
	{
		update(1,1,n,pre[i]+1,i,1);
		(ans+=query(1,1,n,1,i))%=mod;
	}
//	cerr<< clock() - start;
	printf("%lld\n",ans);
	return 0;
}
