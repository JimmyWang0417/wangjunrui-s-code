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
const int N=3e4+5;
struct Tree
{
	int l,r,size;
} tree[N*60];
int root[N],cnt;
#define lc(x) tree[x].l
#define rc(x) tree[x].r
inline void update(int pre,int &rt,int l,int r,int pos,int val)
{
	rt=++cnt;
	tree[rt]=tree[pre];
	tree[rt].size+=val;
	if(l==r)
		return;
	int mid=(l+r)>>1;
	if(pos<=mid)
		update(lc(pre),lc(rt),l,mid,pos,val);
	else
		update(rc(pre),rc(rt),mid+1,r,pos,val);
}
inline int query(int pre,int rt,int l,int r,int pos)
{
	if(l==r)
		return 0;
	int mid=(l+r)>>1;
	if(pos<=mid)
		return query(lc(pre),lc(rt),l,mid,pos)+tree[rc(rt)].size-tree[rc(pre)].size;
	else
		return query(rc(pre),rc(rt),mid+1,r,pos);
}
int n,a[N];
signed main()
{
	read(n);
	int MAX=0;
	for(re int i=1; i<=n; ++i)
	{
		read(a[i]);
		MAX=std::max(MAX,a[i]);
	}
	for(re int i=1; i<=n; ++i)
		update(root[i-1],root[i],1,MAX,a[i],1);
	int q;
	read(q);
	while(q--)
	{
		int x,y,k;
		read(x,y,k);
		printf("%d\n",query(root[x-1],root[y],1,MAX,k));
	}
	return 0;
}


