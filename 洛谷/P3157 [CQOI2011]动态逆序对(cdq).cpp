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
inline void clear(T*a,int l,int r,int val)
{
	memset(&a[l],val,sizeof(T)*(r-l+1));
}
const int N=1e5+5;
int n,m;
struct node
{
	int val,tim,ans;
	inline bool operator <(const node&rhs)const
	{
		return val<rhs.val;
	}
} a[N];
int c[N];
inline void update(int pos)
{
	for(re int i=pos; i<=N-5; i+=lowbit(i))
		++c[i];
}
inline int query(int pos)
{
	int res=0;
	for(re int i=pos; i; i-=lowbit(i))
		res+=c[i];
	return res;
}
inline void clear(int pos)
{
	for(re int i=pos; i<=N-5; i+=lowbit(i))
		if(c[i])
			c[i]=0;
		else
			return;
}
inline int query(int l,int r)
{
	return query(r)-query(l-1);
}
inline void cdq(int l,int r)
{
	if(l==r)
		return;
	int mid=(l+r)>>1;
	cdq(l,mid),cdq(mid+1,r);
	for(re int i=l; i<=r; ++i)
		clear(a[i].tim);
	re int i=l,j=mid+1;
	while(i<=mid)
	{
		while(a[i].val>a[j].val&&j<=r)
			update(a[j++].tim);
		a[i].ans+=query(a[i].tim,m+1);
		++i;
	}
	for(i=l; i<=r; ++i)
		clear(a[i].tim);
	i=mid,j=r;
	while(j>mid)
	{
		while(a[i].val>a[j].val&&i>=l)
			update(a[i--].tim);
		a[j].ans+=query(a[j].tim,m+1);
		--j;
	}
	for(i=l; i<=r; ++i)
		clear(a[i].tim);
	std::sort(a+l,a+r+1);
}
int ans[N],id[N];
signed main()
{
	read(n,m);
	ll answer=0;
	for(re int i=1; i<=n; ++i)
	{
		read(a[i].val);
		id[a[i].val]=i;
		update(a[i].val);
		answer+=query(a[i].val+1,n);
	}
	for(re int i=1; i<=n; ++i)
		clear(a[i].val);
	for(re int i=1; i<=m; ++i)
	{
		int val;
		read(val);
		a[id[val]].tim=i;
	}
	for(re int i=1; i<=n; ++i)
		if(!a[i].tim)
			a[i].tim=m+1;
	cdq(1,n);
	for(re int i=1; i<=n; ++i)
		ans[a[i].tim]=a[i].ans;
//	for(re int i=1; i<=m; ++i)
//		printf("%d\n",ans[i]);
	for(re int i=1; i<=m; ++i)
	{
		printf("%lld\n",answer);
		answer-=ans[i];
	}
	return 0;
}


