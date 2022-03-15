#include <cmath>
#include <cstdio>
#include <bitset>
#include <cstring>
#include <algorithm>
#include <iostream>
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
const int N=1e5+5,MAX=1e5;
int n,m,a[N];
int block,belong[N];
struct Queue
{
	int opt,l,r,val,id;
	inline bool operator < (const Queue&rhs)const
	{
		return belong[l]==belong[rhs.l]?r<rhs.r:belong[l]<belong[rhs.l];
	}
} q[N];
bitset<N>s1,s2;
int cnt[N];
inline void add(int val)
{
	if(!cnt[val])
		s1[val]=s2[MAX-val]=true;
	++cnt[val];
}
inline void del(int val)
{
	--cnt[val];
	if(!cnt[val])
		s1[val]=s2[MAX-val]=false;
}
bool answer[N];
signed main()
{
	read(n,m);
	block=(int)sqrt(n);
	for(re int i=1; i<=n; ++i)
	{
		read(a[i]);
		belong[i]=(i-1)/block+1;
	}
	for(re int i=1; i<=m; ++i)
	{
		read(q[i].opt,q[i].l,q[i].r,q[i].val);
		q[i].id=i;
	}
	sort(q+1,q+1+m);
	int l=1,r=0;
	for(re int i=1; i<=m; ++i)
	{
		const int &opt=q[i].opt,&ql=q[i].l,&qr=q[i].r;
		const int &val=q[i].val;
		bool &ans=answer[q[i].id];
		while(ql<l)
			add(a[--l]);
		while(ql>l)
			del(a[l++]);
		while(qr<r)
			del(a[r--]);
		while(qr>r)
			add(a[++r]);
		if(opt==1)
		{
			if((s1&(s1<<val)).any())
				ans=true;
		}
		else if(opt==2)
		{
			if((s1&(s2>>(MAX-val))).any())
				ans=true;
		}
		else if(opt==3)
		{
			for(re int j=1; j*j<=val; ++j)
				if(val%j==0)if(s1[j]&&s1[val/j])
					{
						ans=true;
						break;
					}
		}
	}
	for(re int i=1; i<=m; ++i)
		printf("%s\n",answer[i]?"hana":"bi");
	return 0;
}

