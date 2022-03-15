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
const int N=1e5+5;
int n,m;
struct Tree_array
{
	int sum[N];
	inline void update(int pos,int val)
	{
		for(int i=pos; i<=n; i+=lowbit(i))
			sum[i]+=val;
	}
	inline int query(int pos)
	{
		int res=0;
		for(int i=pos; i; i-=lowbit(i))
			res+=sum[i];
		return res;
	}
} tree;
struct node
{
	int tim,pos,val;
	int ans;
	inline bool operator <(const node &rhs)const
	{
		return tim<rhs.tim;
	}
	inline bool operator >(const node &rhs)const
	{
		return tim>rhs.tim;
	}
} a[N],b[N];
inline void cdq1(int l,int r)
{
	if(l==r)
		return;
	int mid=(l+r)>>1;
	cdq1(l,mid),cdq1(mid+1,r);
	int i=l,j=mid+1,now=l;
	while(i<=mid&&j<=r)
	{
		if(a[i].pos<a[j].pos)
		{
			tree.update(a[i].val,1);
			b[now++]=a[i++];
		}
		else
		{
			a[j].ans+=tree.query(n)-tree.query(a[j].val);
			b[now++]=a[j++];
		}
	}
	while(i<=mid)
	{
		tree.update(a[i].val,1);
		b[now++]=a[i++];
	}
	while(j<=r)
	{
		a[j].ans+=tree.query(n)-tree.query(a[j].val);
		b[now++]=a[j++];
	}
	for(i=l; i<=mid; ++i)
		tree.update(a[i].val,-1);
	for(i=l; i<=r; ++i)
		a[i]=b[i];
}
inline void cdq2(int l,int r)
{
	if(l==r)
		return;
	int mid=(l+r)>>1;
	cdq2(l,mid),cdq2(mid+1,r);
	int i=l,j=mid+1,now=l;
	while(i<=mid&&j<=r)
	{
		if(a[i].pos>a[j].pos)
		{
			tree.update(a[i].val,1);
			b[now++]=a[i++];
		}
		else
		{
			a[j].ans+=tree.query(a[j].val);
			b[now++]=a[j++];
		}
	}
	while(i<=mid)
	{
		tree.update(a[i].val,1);
		b[now++]=a[i++];
	}
	while(j<=r)
	{
		a[j].ans+=tree.query(a[j].val);
		b[now++]=a[j++];
	}
	for(i=l; i<=mid; ++i)
		tree.update(a[i].val,-1);
	for(i=l; i<=r; ++i)
		a[i]=b[i];
}
int id[N];
bool vis[N];
ll answer[N];
signed main()
{
	read(n,m);
	for(int i=1; i<=n; ++i)
	{
		int val;
		read(val);
		id[val]=i;
	}
	for(int i=1; i<=m; ++i)
	{
		int val;
		read(val);
		vis[val]=true;
		a[i].tim=i;
		a[i].pos=id[val];
		a[i].val=val;
	}
	int cnt=m;
	for(int i=1; i<=n; ++i)
	{
		if(vis[i])
			continue;
		++cnt;
		a[cnt].tim=cnt;
		a[cnt].pos=id[i];
		a[cnt].val=i;
	}
	reverse(a+1,a+1+n);
//	for(int i=1; i<=n; ++i)
//		printf("%d %d %d\n",a[i].pos,a[i].val,a[i].ans);
//	putchar('\n');
	cdq1(1,n);
	sort(a+1,a+1+n,greater<node>());
//	for(int i=1; i<=n; ++i)
//		printf("%d %d %d\n",a[i].pos,a[i].val,a[i].ans);
//	putchar('\n');
	cdq2(1,n);
	sort(a+1,a+1+n);
//	for(int i=1; i<=n; ++i)
//		printf("%d %d %d\n",a[i].pos,a[i].val,a[i].ans);
//	putchar('\n');
	for(int i=1; i<=n; ++i)
		answer[a[i].tim]=a[i].ans;
	for(int i=n-1; i>=1; --i)
		answer[i]+=answer[i+1];
	for(int i=1; i<=m; ++i)
		printf("%lld\n",answer[i]);
	return 0;
}

