#include <bits/stdc++.h>
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
const int N=2e5+5;
int mod,hash[N];
char str[N];
int block,belong[N];
int n;
struct Queue
{
	int l,r,id;
	inline bool operator <(const Queue &rhs)const
	{
		return belong[l]==belong[rhs.l]?(belong[l]&1?r<rhs.r:r>rhs.r):belong[l]<belong[rhs.l];
	}
} q[N];
int p[N];
int cnt[N];
ll answer[N],ans;
inline void add(int val)
{
	ans+=cnt[val];
	++cnt[val];
}
inline void del(int val)
{
	--cnt[val];
	ans-=cnt[val];
}
inline void work1()
{
	for(re int i=n,power=1; i>=1; --i,power=(int)((ll)power*10%mod))
	{
		hash[i]=(int)((hash[i+1]+(ll)power*(str[i]-'0')%mod)%mod);
		p[i]=hash[i];
	}
	block=(int)sqrt(++n);
	for(re int i=1; i<=n; ++i)
		belong[i]=(i-1)/block;
	std::sort(p+1,p+1+n);
	int tot=(int)(std::unique(p+1,p+1+n)-1-p);
	for(re int i=1; i<=n; ++i)
		hash[i]=(int)(std::lower_bound(p+1,p+1+tot,hash[i])-p);
	int m;
	read(m);
	for(re int i=1; i<=m; ++i)
	{
		read(q[i].l,q[i].r);
		++q[i].r;
		q[i].id=i;
	}
	std::sort(q+1,q+1+m);
	int l=0,r=-1;
	for(re int now=1; now<=m; ++now)
	{
		const int &ql=q[now].l,&qr=q[now].r;
		while(l<ql)
			del(hash[l++]);
		while(l>ql)
			add(hash[--l]);
		while(r<qr)
			add(hash[++r]);
		while(r>qr)
			del(hash[r--]);
		answer[q[now].id]=ans;
	}
	for(re int i=1; i<=m; ++i)
		printf("%lld\n",answer[i]);
}
inline void work2()
{
	int m;
	for(re int i=1; i<=n; ++i)
		hash[i]=(str[i]-'0')%mod;
	read(m);
	for(re int i=1; i<=m; ++i)
	{
		read(q[i].l,q[i].r);
		q[i].id=i;
	}
	std::sort(q+1,q+1+m);
	int sum=0,l=1,r=0;
	for(re int now=1; now<=m; ++now)
	{
		const int &ql=q[now].l,&qr=q[now].r;
		while(l<ql)
		{
			ans-=sum;
			if(!hash[l])
				--sum;
			++l;
		}
		while(l>ql)
		{
			--l;
			if(!hash[l])
				++sum;
			ans+=sum;
		}
		while(r<qr)
		{
			++r;
			if(!hash[r])
			{
				ans+=r-l+1;
				++sum;
			}
		}
		while(r>qr)
		{
			if(!hash[r])
			{
				ans-=r-l+1;
				--sum;
			}
			--r;
		}
		answer[q[now].id]=ans;
	}
	for(re int i=1; i<=m; ++i)
		printf("%lld\n",answer[i]);
}
signed main()
{
	read(mod);
	scanf("%s",str+1);
	n=(int)strlen(str+1);
	if(mod!=2&&mod!=5)
		work1();
	else work2();
	return 0;
}


