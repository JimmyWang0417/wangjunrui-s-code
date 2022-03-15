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
const int N=1e5+5,B=3,M=N/B+10;
std::bitset<N>sum[M],now;
int block,belong[N];
struct Queue
{
	int l,r,id;
	inline bool operator <(const Queue&rhs)const
	{
		return belong[l]==belong[rhs.l]?(belong[l]&1?r<rhs.r:r>rhs.r):l<rhs.l;
	}
} q[M*3];
int ans[N/B+5];
int n,m,a[N],p[N];
int cnt[N];
inline void add(int val)
{
	now.set(val+cnt[val]);
	++cnt[val];
}
inline void del(int val)
{
	--cnt[val];
	now.reset(val+cnt[val]);
}
inline void solve()
{
	int _n=0;
	re int tot=1;
	for(; tot<=M-10&&m; ++tot)
	{
		ans[tot]=0;
		for(re int i=1; i<=3; ++i)
		{
			++_n;
			read(q[_n].l,q[_n].r);
			q[_n].id=tot;
			ans[tot]+=q[_n].r-q[_n].l+1;
		}
		--m;
		sum[tot].set();
	}
	std::sort(q+1,q+1+_n);
	int l=1,r=0;
	for(re int i=1; i<=_n; ++i)
	{
		const int &ql=q[i].l,&qr=q[i].r;
		while(ql<l)
			add(a[--l]);
		while(qr>r)
			add(a[++r]);
		while(ql>l)
			del(a[l++]);
		while(qr<r)
			del(a[r--]);
		sum[q[i].id]&=now;
	}
	now.reset();
	memset(cnt,0,sizeof(cnt));
	for(re int i=1; i<tot; ++i)
		printf("%d\n",ans[i]-3*sum[i].count());
}
signed main()
{
	read(n,m);
	for(re int i=1; i<=n; ++i)
	{
		read(a[i]);
		p[i]=a[i];
	}
	block=(int)sqrt(n);
	for(re int i=1; i<=n; ++i)
		belong[i]=(i-1)/block+1;
	std::sort(p+1,p+1+n);
	for(re int i=1; i<=n; ++i)
		a[i]=(int)(std::lower_bound(p+1,p+1+n,a[i])-p);
	while(m)
		solve();
	return 0;
}


