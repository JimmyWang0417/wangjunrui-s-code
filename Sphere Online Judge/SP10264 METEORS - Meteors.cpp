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
const int N=3e5+5;
int n,m;
ull c[N];
inline void update(int pos,int val)
{
	assert(pos!=0);
	for(re int i=pos; i<=m; i+=lowbit(i))
		c[i]+=val;
}
inline void update(int l,int r,int val)
{
	if(l<=r)
	{
		update(l,val);
		update(r+1,-val);
	}
	else
	{
		update(l,val);
		update(1,val);
		update(r+1,-val);
	}
}
inline ull query(int pos)
{
	ull res=0;
	for(re int i=pos; i; i-=lowbit(i))
		res+=c[i];
	return res;
}
inline void clear(int pos)
{
	for(re int i=pos; i<=m; i+=lowbit(i))
		if(c[i])
			c[i]=0;
		else return;
}
inline void clear(int l,int r)
{
	if(l<=r)
	{
		clear(l);
		clear(r+1);
	}
	else
	{
		clear(l);
		clear(1);
		clear(r+1);
	}
}
struct Queue
{
	int val,id;
} q[N],q1[N],q2[N];
struct Change
{
	int l,r,a;
} a[N];
int ans[N];
std::vector<int>son[N];
inline void solve(int ql,int qr,int l,int r)
{
	if(ql>qr)
		return;
	if(l==r)
	{
		for(re int i=ql; i<=qr; ++i)
			ans[q[i].id]=l;
		return;
	}
	int mid=(l+r)>>1,cnt1=0,cnt2=0;
	for(re int i=l; i<=mid; ++i)
		update(a[i].l,a[i].r,a[i].a);
//	printf("%d %d %d\n",l,mid,r);
	for(re int i=ql; i<=qr; ++i)
	{
//		printf("%d %d\n",q[i].val,q[i].id);
		ull cnt=0;
		for(auto v:son[q[i].id])
			cnt+=query(v);
		if(cnt>=q[i].val)
			q1[++cnt1]=q[i];
		else
		{
			q[i].val-=cnt;
			q2[++cnt2]=q[i];
		}
	}
	for(re int i=l; i<=mid; ++i)
		clear(a[i].l,a[i].r);
	for(re int i=1; i<=cnt1; ++i)
		q[ql+i-1]=q1[i];
	for(re int i=1; i<=cnt2; ++i)
		q[ql+cnt1+i-1]=q2[i];
	solve(ql,ql+cnt1-1,l,mid),solve(ql+cnt1,qr,mid+1,r);
}
signed main()
{
	read(n,m);
	for(re int i=1; i<=m; ++i)
	{
		int fa;
		read(fa);
		son[fa].push_back(i);
	}
	for(re int i=1; i<=n; ++i)
	{
		read(q[i].val);
		q[i].id=i;
	}
	int k;
	read(k);
	for(re int i=1; i<=k; ++i)
		read(a[i].l,a[i].r,a[i].a);
//	for(re int i=1; i<=k; ++i)
//		printf("%d %d %d\n",a[i].l,a[i].r,a[i].a);
	solve(1,n,1,k+1);
	for(re int i=1; i<=n; ++i)
	{
		if(ans[i]==k+1)
			printf("NIE\n");
		else
			printf("%d\n",ans[i]);
	}
	return 0;
}

