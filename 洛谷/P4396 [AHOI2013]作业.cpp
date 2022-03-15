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
const int N=1e5+5,MAX=1e5;
int n,m,a[N];
struct Tree
{
	int c[N];
	inline void update(int pos,int val)
	{
		for(re int i=pos; i<=MAX; i+=lowbit(i))
			c[i]+=val;
	}
	inline int query(int pos)
	{
		int res=0;
		for(re int i=pos; i; i-=lowbit(i))
			res+=c[i];
		return res;
	}
	inline int query(int l,int r)
	{
		return query(r)-query(l-1);
	}
} tree1,tree2;
int block,belong[N];
struct Queue
{
	int l,r,a,b,id;
	inline bool operator <(const Queue&rhs)const
	{
		return belong[l]==belong[rhs.l]?(belong[l]&1?r<rhs.r:r>rhs.r):l<rhs.l;
	}
} q[N];
int cnt[N];
inline void add(int val)
{
	tree1.update(val,1);
	if(!cnt[val]++)
		tree2.update(val,1);
}
inline void del(int val)
{
	tree1.update(val,-1);
	if(!--cnt[val])
		tree2.update(val,-1);
}
int answer1[N],answer2[N];
signed main()
{
	read(n,m);
	for(re int i=1; i<=n; ++i)
		read(a[i]);
	block=(int)sqrt(n);
	for(re int i=1; i<=n; ++i)
		belong[i]=(i-1)/block+1;
	for(re int i=1; i<=m; ++i)
	{
		read(q[i].l,q[i].r,q[i].a,q[i].b);
		q[i].id=i;
	}
	std::sort(q+1,q+1+m);
	int l=1,r=0;
	for(re int i=1; i<=m; ++i)
	{
		const int &ql=q[i].l,&qr=q[i].r;
		while(l>ql)
			add(a[--l]);
		while(l<ql)
			del(a[l++]);
		while(r>qr)
			del(a[r--]);
		while(r<qr)
			add(a[++r]);
		answer1[q[i].id]=tree1.query(q[i].a,q[i].b);
		answer2[q[i].id]=tree2.query(q[i].a,q[i].b);
	}
	for(re int i=1; i<=m; ++i)
		printf("%d %d\n",answer1[i],answer2[i]);
	return 0;
}


