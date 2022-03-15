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
const int N=5e4+5,mod=1e9+7;
int prime[N],id[N],tot;
int inv[N];
bool vis[N];
inline ll quickpow(ll a,int b)
{
	ll res=1;
	while(b)
	{
		if(b&1)
			res=res*a%mod;
		a=a*a%mod;
		b>>=1;
	}
	return res;
}
inline void getprime(int n)
{
	for(int i=2; i<=n; ++i)
	{
		if(!vis[i])
		{
			prime[++tot]=i;
			inv[tot]=quickpow(i,mod-2);
			id[i]=tot;
		}
		for(int j=1; j<=tot; ++j)
		{
			if(prime[j]*i>n)
				break;
			vis[i*prime[j]]=true;
			if(i%prime[j]==0)
				break;
		}
	}
}
#define node bitset<5137>
struct Tree
{
	int sum;
	ll mul;
	node pri;
} tree[N*4];
#define lc (rt<<1)
#define rc (rt<<1|1)
inline node change(int val)
{
	node ans;
	for(int i=1; prime[i]*prime[i]<=val; ++i)
		if(val%prime[i]==0)
		{
			ans.set(i);
			while(val%prime[i]==0)
				val/=prime[i];
		}
	if(val>1)
		ans.set(id[val]);
	return ans;
}
inline int getphi(int val)
{
	int ans=val;
	for(int i=1; prime[i]*prime[i]<=val; ++i)
	{
		if(val%prime[i]==0)
		{
			ans=ans/prime[i]*(prime[i]-1);
			while(val%prime[i]==0)
				val/=prime[i];
		}
	}
	if(val>1)
		ans=ans/val*(val-1);
	return ans;
}
int n,m,a[N];
inline void pushup(int rt)
{
	tree[rt].sum=tree[lc].sum+tree[rc].sum;
	tree[rt].mul=tree[lc].mul*tree[rc].mul%mod;
	tree[rt].pri=tree[lc].pri|tree[rc].pri;
}
inline void build(int rt,int l,int r)
{
	if(l==r)
	{
		tree[rt].mul=tree[rt].sum=a[l];
		tree[rt].pri=change(a[l]);
//		printf("%d:",l);
//		for(int i=1; i<=tot; ++i)
//			if(tree[rt].pri[i])
//			{
////				ans=ans*inv[i]%mod*(prime[i]-1)%mod;
//				printf("%d ",prime[i]);
//			}
//		putchar('\n');
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
		tree[rt].mul=tree[rt].sum=val;
		tree[rt].pri=change(val);
		return;
	}
	int mid=(l+r)>>1;
	if(pos<=mid)
		update(lc,l,mid,pos,val);
	else
		update(rc,mid+1,r,pos,val);
	pushup(rt);
}
inline int querysum(int rt,int l,int r,int x,int y)
{
	if(r<x||l>y)
		return 0;
	if(x<=l&&r<=y)
		return tree[rt].sum;
	int mid=(l+r)>>1;
	return (querysum(lc,l,mid,x,y)+querysum(rc,mid+1,r,x,y));
}
inline ll querymul(int rt,int l,int r,int x,int y)
{
	if(r<x||l>y)
		return 1;
	if(x<=l&&r<=y)
		return tree[rt].mul;
	int mid=(l+r)>>1;
	return (querymul(lc,l,mid,x,y)*querymul(rc,mid+1,r,x,y))%mod;
}
inline node querypri(int rt,int l,int r,int x,int y)
{
	if(r<x||l>y)
		return node();
	if(x<=l&&r<=y)
		return tree[rt].pri;
	int mid=(l+r)>>1;
	return querypri(lc,l,mid,x,y)|querypri(rc,mid+1,r,x,y);
}
inline void work()
{
	int opt;
	read(opt);
	if(opt==0)
	{
		int pos,val;
		read(pos,val);
		update(1,1,n,pos,val);
	}
	else if(opt==1)
	{
		int l,r;
		read(l,r);
		printf("%d\n",getphi(querysum(1,1,n,l,r)));
	}
	else if(opt==2)
	{
		int l,r;
		read(l,r);
		ll ans=querymul(1,1,n,l,r);
//		printf("%d\n",ans);
		node res=querypri(1,1,n,l,r);
		for(int i=1; i<=tot; ++i)
			if(res[i])
			{
				ans=ans*inv[i]%mod*(prime[i]-1)%mod;
//				printf("%d ",prime[i]);
			}
//		putchar('\n');
		printf("%lld\n",ans);
	}
}
signed main()
{
	freopen("phi.in","r",stdin);
	freopen("phi.out","w",stdout);
	getprime(5e4);
//	printf("%d\n",tot);
	read(n,m);
	for(int i=1; i<=n; ++i)
		read(a[i]);
	build(1,1,n);
	for(int i=1; i<=m; ++i)
		work();
	return 0;
}

