#pragma GCC optimize(2)
#pragma GCC optimize(3)
#pragma GCC optimize("Ofast")
#pragma GCC optimize("inline")
#pragma GCC optimize("-fgcse")
#pragma GCC optimize("-fgcse-lm")
#pragma GCC optimize("-fipa-sra")
#pragma GCC optimize("-ftree-pre")
#pragma GCC optimize("-ftree-vrp")
#pragma GCC optimize("-fpeephole2")
#pragma GCC optimize("-ffast-math")
#pragma GCC optimize("-fsched-spec")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("-falign-jumps")
#pragma GCC optimize("-falign-loops")
#pragma GCC optimize("-falign-labels")
#pragma GCC optimize("-fdevirtualize")
#pragma GCC optimize("-fcaller-saves")
#pragma GCC optimize("-fcrossjumping")
#pragma GCC optimize("-fthread-jumps")
#pragma GCC optimize("-funroll-loops")
#pragma GCC optimize("-fwhole-program")
#pragma GCC optimize("-freorder-blocks")
#pragma GCC optimize("-fschedule-insns")
#pragma GCC optimize("inline-functions")
#pragma GCC optimize("-ftree-tail-merge")
#pragma GCC optimize("-fschedule-insns2")
#pragma GCC optimize("-fstrict-aliasing")
#pragma GCC optimize("-fstrict-overflow")
#pragma GCC optimize("-falign-functions")
#pragma GCC optimize("-fcse-skip-blocks")
#pragma GCC optimize("-fcse-follow-jumps")
#pragma GCC optimize("-fsched-interblock")
#pragma GCC optimize("-fpartial-inlining")
#pragma GCC optimize("no-stack-protector")
#pragma GCC optimize("-freorder-functions")
#pragma GCC optimize("-findirect-inlining")
#pragma GCC optimize("-frerun-cse-after-loop")
#pragma GCC optimize("inline-small-functions")
#pragma GCC optimize("-finline-small-functions")
#pragma GCC optimize("-ftree-switch-conversion")
#pragma GCC optimize("-foptimize-sibling-calls")
#pragma GCC optimize("-fexpensive-optimizations")
#pragma GCC optimize("-funsafe-loop-optimizations")
#pragma GCC optimize("inline-functions-called-once")
#pragma GCC optimize("-fdelete-null-pointer-checks")
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
const int N=2e5+5;
int n,m;
int a[N];
int belong[N],block;
struct Queue
{
	int l,r,t,id;
	inline bool operator <(const Queue &rhs)const
	{
		return belong[l]==belong[rhs.l]?(belong[r]==belong[rhs.r]?t<rhs.t:r<rhs.r):l<rhs.l;
	}
} q[N];
struct Change
{
	int pos,val;
} c[N];
int ccnt,qcnt;
int cnt[N];
ll ans,answer[N];
int p[N],tot;
inline void add(int pos)
{
	if(!cnt[pos]++)
		ans+=p[pos];
}
inline void del(int pos)
{
	if(!--cnt[pos])
		ans-=p[pos];
}
signed main()
{
	freopen("sum.in","r",stdin);
	freopen("sum.out","w",stdout);
	read(n);
	block=(int)pow(n,0.74);
	for(int i=1; i<=n; ++i)
	{
		read(a[i]);
		p[++tot]=a[i];
		belong[i]=(i-1)/block+1;
	}
	read(m);
	for(int i=1; i<=m; ++i)
	{
		char opt[4];
		scanf("%s",opt);
		if(opt[0]=='U')
		{
			++ccnt;
			read(c[ccnt].pos,c[ccnt].val);
			p[++tot]=c[ccnt].val;
		}
		else
		{
			++qcnt;
			read(q[qcnt].l,q[qcnt].r);
			q[qcnt].t=ccnt;
			q[qcnt].id=qcnt;
		}
	}
	sort(p+1,p+1+tot);
	tot=(int)(unique(p+1,p+1+tot)-p-1);
	for(int i=1; i<=n; ++i)
		a[i]=(int)(lower_bound(p+1,p+1+tot,a[i])-p);
	for(int i=1; i<=ccnt; ++i)
		c[i].val=(int)(lower_bound(p+1,p+1+tot,c[i].val)-p);
	sort(q+1,q+1+qcnt);
	int l=1,r=0,t=0;
	for(int kase=1; kase<=qcnt; ++kase)
	{
		const int ql=q[kase].l,qr=q[kase].r,qt=q[kase].t;
		while(ql<l)
			add(a[--l]);
		while(qr>r)
			add(a[++r]);
		while(ql>l)
			del(a[l++]);
		while(qr<r)
			del(a[r--]);
		while(qt>t)
		{
			++t;
			if(l<=c[t].pos&&c[t].pos<=r)
			{
				del(a[c[t].pos]);
				add(c[t].val);
			}
			swap(a[c[t].pos],c[t].val);
		}
		while(qt<t)
		{
			if(l<=c[t].pos&&c[t].pos<=r)
			{
				del(a[c[t].pos]);
				add(c[t].val);
			}
			swap(a[c[t].pos],c[t].val);
			--t;
		}
		answer[q[kase].id]=ans;
	}
	for(int i=1; i<=qcnt; ++i)
		printf("%lld\n",answer[i]);
	return 0;
}


