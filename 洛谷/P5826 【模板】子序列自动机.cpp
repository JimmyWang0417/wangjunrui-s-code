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
struct Tree
{
	int l,r;
	int pos;
} tree[N*50];
int root[N],cnt;
#define lc(x) tree[x].l
#define rc(x) tree[x].r
inline void update(int &rt,int pre,int l,int r,int pos,int val)
{
	rt=++cnt;
	tree[rt]=tree[pre];
	if(l==r)
	{
		tree[rt].pos=val;
		return;
	}
	int mid=(l+r)>>1;
	if(pos<=mid)
		update(lc(rt),lc(pre),l,mid,pos,val);
	else
		update(rc(rt),rc(pre),mid+1,r,pos,val);
}
inline int query(int rt,int l,int r,int pos)
{
	if(l==r)
		return tree[rt].pos;
	int mid=(l+r)>>1;
	if(pos<=mid)
		return query(lc(rt),l,mid,pos);
	else
		return query(rc(rt),mid+1,r,pos);
}
int type,n,q,m;
int a[N],b[N];
inline void work()
{
	int l;
	read(l);
	for(int i=1; i<=l; ++i)
		read(b[i]);
	int now=0;
	for(int i=1; i<=l; ++i)
	{
		int nxt=query(root[now],1,m,b[i]);
		if(!nxt)
		{
			printf("No\n");
			return;
		}
		now=nxt;
	}
	printf("Yes\n");
}
signed main()
{
	read(type,n,q,m);
	for(int i=1; i<=n; ++i)
		read(a[i]);
	for(int i=n; i>=1; --i)
		update(root[i-1],root[i],1,m,a[i],i);
	while(q--)
		work();
	return 0;
}


