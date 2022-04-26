#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cmath>
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
const int N=3e4+5,M=2e5+5,MAX=1e6+5;
int n,m,a[N];
int block,belong[N];
struct Queue
{
	int l,r,id;
	inline bool operator <(const Queue&rhs)const
	{
		if(belong[l]==belong[rhs.l])
			return r<rhs.r;
		return belong[l]<belong[rhs.l];
	}
} q[M];
int cnt[MAX];
int ans;
inline void add(int pos)
{
	if(!cnt[a[pos]])
		++ans;
	++cnt[a[pos]];
}
inline void del(int pos)
{
	--cnt[a[pos]];
	if(!cnt[a[pos]])
		--ans;
}
int answer[M];
signed main()
{
	read(n);
	block=(int)sqrt(n);
	for(re int i=1; i<=n; ++i)
	{
		read(a[i]);
		belong[i]=(i-1)/block+1;
	}
	read(m);
	for(re int i=1; i<=m; ++i)
	{
		read(q[i].l,q[i].r);
		q[i].id=i;
	}
	sort(q+1,q+1+m);
	int l=0,r=0;
	for(re int i=1; i<=m; ++i)
	{
		const int &ql=q[i].l,&qr=q[i].r;
		while(ql<l)
			add(--l);
		while(ql>l)
			del(l++);
		while(qr<r)
			del(r--);
		while(qr>r)
			add(++r);
		answer[q[i].id]=ans;
	}
	for(re int i=1; i<=m; ++i)
		printf("%d\n",answer[i]);
	return 0;
}

