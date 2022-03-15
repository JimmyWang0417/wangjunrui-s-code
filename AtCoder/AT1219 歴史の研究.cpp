#include <cmath>
#include <cstdio>
#include <bitset>
#include <cstring>
#include <algorithm>
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
template<typename T,typename ...T1>
inline void read(T&x,T1&...x1)
{
	read(x);
	read(x1...);
}
const int N=1e5+5;
int n,m,a[N],p[N],c[N];
int block,belong[N];
int num,L[N],R[N];
int cnt[N],nowcnt[N];
struct Queue
{
	int l,r,id;
	inline bool operator <(const Queue&rhs)const
	{
		return belong[l]==belong[rhs.l]?r<rhs.r:belong[l]<belong[rhs.l];
	}
} q[N];
ll answer[N],ans;
inline void add(int pos)
{
	++cnt[c[pos]];
	ans=max(ans,1ll*a[pos]*cnt[c[pos]]);
}
signed main()
{
	read(n,m);
	block=(int)sqrt(n);
	num=n/block+(n%block!=0);
	for(re int i=1; i<=n; ++i)
	{
		read(a[i]);
		p[i]=a[i];
		belong[i]=(i-1)/block+1;
	}
	for(re int i=1; i<=num; ++i)
	{
		L[i]=R[i-1]+1;
		R[i]=R[i-1]+block;
	}
	R[num]=n;
	for(re int i=1; i<=m; ++i)
	{
		read(q[i].l,q[i].r);
		q[i].id=i;
	}
	sort(p+1,p+1+n);
	sort(q+1,q+1+m);
	int tot=(int)(unique(p+1,p+1+n)-1-p);
	for(re int i=1; i<=n; ++i)
		c[i]=(int)(lower_bound(p+1,p+1+tot,a[i])-p);
	int lastblock=0,r=0;
	for(re int now=1; now<=m; ++now)
	{
		const int &ql=q[now].l,&qr=q[now].r;
		ll &nowans=answer[q[now].id];
		if(belong[ql]!=lastblock)
		{
			memset(cnt,0,sizeof(cnt));
			lastblock=belong[ql];
			r=R[lastblock]-1;
			ans=0;
		}
		if(belong[ql]==belong[qr])
		{
			for(re int i=ql; i<=qr; ++i)
			{
				++nowcnt[c[i]];
				nowans=max(nowans,1ll*a[i]*nowcnt[c[i]]);
			}
			for(re int i=ql; i<=qr; ++i)
				nowcnt[c[i]]=0;
			continue;
		}
		while(r<qr)
			add(++r);
		nowans=ans;
		for(re int i=ql; i<R[lastblock]; ++i)
		{
			++nowcnt[c[i]];
			nowans=max(nowans,1ll*a[i]*(nowcnt[c[i]]+cnt[c[i]]));
		}
		for(re int i=ql; i<R[lastblock]; ++i)
			nowcnt[c[i]]=0;
	}
	for(re int i=1; i<=m; ++i)
		printf("%lld\n",answer[i]);
	return 0;
}


