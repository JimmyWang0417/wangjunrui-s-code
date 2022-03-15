#include <cmath>
#include <cstdio>
#include <algorithm>
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
const int N=5e4+5,MAX=1e6+5;
int n,m,a[N];
int block,belong[N];
struct Change
{
	int pos,val;
} c[N];
struct Queue
{
	int l,r,t,id;
	inline bool operator <(const Queue&rhs)const
	{
		return belong[l]==belong[rhs.l]?(belong[r]==belong[rhs.r]?t<rhs.t:belong[r]<belong[rhs.r]):belong[l]<belong[rhs.l];
	}
} q[N];
int cntc,cntq;
int cnt[MAX];
int ans,answer[N];
inline void add(int val)
{
	if(!cnt[val])
		++ans;
	++cnt[val];
}
inline void del(int val)
{
	--cnt[val];
	if(!cnt[val])
		--ans;
}
signed main()
{
	using std::sort;
	using std::swap;
	read(n,m);
	block=(int)pow(n,2.0/3.0);
	rep(i,0,n-1)
	{
		read(a[i]);
		belong[i]=(i-1)/block+1;
	}
	rep(i,1,m)
	{
		char opt[2];
		scanf("%s",opt);
		if(opt[0]=='Q')
		{
			++cntq;
			read(q[cntq].l,q[cntq].r);
			--q[cntq].r; 
			q[cntq].t=cntc;
			q[cntq].id=cntq;
		}
		else
		{
			++cntc;
			read(c[cntc].pos,c[cntc].val);
		}
	}
	sort(q+1,q+1+cntq);
	int l=1,r=0,t=0;
	rep(i,1,cntq)
	{
#define ql q[i].l
#define qr q[i].r
#define qt q[i].t
		while(ql<l)
			add(a[--l]);
		while(ql>l)
			del(a[l++]);
		while(qr<r)
			del(a[r--]);
		while(qr>r)
			add(a[++r]);
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
		answer[q[i].id]=ans;
#undef ql
#undef qr
#undef qt
	}
	rep(i,1,cntq)
	printf("%d\n",answer[i]);
	return 0;
}
