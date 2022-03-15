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
const int N=1e5+5;
int n,a[N];
int p[N],tot;
ll k;
struct Tree_array
{
	int c[N];
	inline void update(int pos,int val)
	{
		for(int i=pos; i<=tot; i+=lowbit(i))
			c[i]+=val;
	}
	inline int query(int pos)
	{
		int res=0;
		for(int i=pos; i; i-=lowbit(i))
			res+=c[i];
		return res;
	}
	inline int query(int l,int r)
	{
		return query(r)-query(l-1);
	}
} pre,suf;
signed main()
{
	read(n,k);
	for(int i=1; i<=n; ++i)
	{
		read(a[i]);
		p[i]=a[i];
	}
	sort(p+1,p+1+n);
	tot=(int)(unique(p+1,p+1+n)-p-1);
	for(int i=1; i<=n; ++i)
		a[i]=(int)(lower_bound(p+1,p+1+tot,a[i])-p);
	ll now=0;
	for(int i=n; i>=1; --i)
	{
		now+=suf.query(a[i]-1);
		suf.update(a[i],1);
	}
	ll ans=0;
	for(int l=1,r=1;l<=n;++l)
	{
		now+=pre.query(a[l]+1,tot)+suf.query(a[l]-1);
//		printf("%lld\n",now);
		pre.update(a[l],1);
		while(l==r||(now>k&&r<=n))
		{
			now-=suf.query(a[r]-1)+pre.query(a[r]+1,tot);
			suf.update(a[r],-1);
			++r;
		}
		ans+=n-r+1;
//		printf("%d %d %lld\n",l,r,now);
	}
	printf("%lld\n",ans);
	return 0;
}


