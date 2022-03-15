#include<cstdio>
#define re register
#define ll long long
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
const int mod=1e9+7;
const int N=1e5+5;
ll a[N];
struct Tree
{
	ll sum1,sum2;
	Tree(ll s1=0,ll s2=0):sum1(s1),sum2(s2) {}
} tree[N*4];
#define lc (rt<<1)
#define rc (rt<<1|1)
inline Tree merge(Tree x,Tree y)
{
	return Tree((x.sum1+y.sum1)%mod,(x.sum2+y.sum2)%mod);
}
inline void pushup(int rt)
{
	tree[rt]=merge(tree[lc],tree[rc]);
}
inline void build(int rt,int l,int r)
{
	if(l==r)
	{
		tree[rt].sum1=a[l];
		tree[rt].sum2=a[l]*a[l]%mod;
		return;
	}
	int mid=(l+r)>>1;
	build(lc,l,mid);
	build(rc,mid+1,r);
	pushup(rt);
}
inline void update(int rt,int l,int r,int pos,ll val)
{
	if(l==r)
	{
		tree[rt].sum1=val;
		tree[rt].sum2=val*val%mod;
		return;
	}
	int mid=(l+r)>>1;
	if(pos<=mid)
		update(lc,l,mid,pos,val);
	else
		update(rc,mid+1,r,pos,val);
	pushup(rt);
}
inline Tree query(int rt,int l,int r,int x,int y)
{
	if(r<x||l>y)
		return Tree();
	if(x<=l&&r<=y)
		return tree[rt];
	int mid=(l+r)>>1;
	return merge(query(lc,l,mid,x,y),query(rc,mid+1,r,x,y));
}
inline ll quickpow(ll aa,ll b,ll p=mod)
{
	ll res=1;
	while(b)
	{
		if(b&1)
			res=res*aa%p;
		aa=aa*aa%p;
		b>>=1;
	}
	return res;
}
int main()
{
	int n,m;
	read(n),read(m);
	for(re int i=1; i<=n; ++i)
	{
		read(a[i]);
		a[i]%=mod;
	}
	build(1,1,n);
	while(m--)
	{
		int opt,l;
		read(opt),read(l);
		if(opt==1)
		{
			ll val;
			read(val);
			update(1,1,n,l,val%mod);
		}
		else if(opt==2)
		{
			int r;
			read(r);
			int len=r-l+1;
			Tree ans=query(1,1,n,l,r);
			ll inv=quickpow(len,mod-2);
			printf("%lld\n",(ans.sum2*inv%mod-(ans.sum1*inv%mod)*(ans.sum1*inv%mod)%mod+mod)%mod);
		}
	}
	return 0;
}
