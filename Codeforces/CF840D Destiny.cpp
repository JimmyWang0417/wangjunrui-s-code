#include <bits/stdc++.h>
#define lowbit(x) ((x)&(-(x)))
#define re register
#define ll long long
#define ull unsigned long long
#define rep(i,a,b) for(re int i=a;i<=b;++i)
#define per(i,a,b) for(re int i=a;i>=b;--i)
static char buf[1 << 20], *fs, *ft;
inline char gc()
{
	if (fs == ft)
	{
		ft = (fs = buf) + fread(buf, 1, 1 << 20, stdin);
		if (fs == ft) return EOF;
	}
	return *fs++;
}
#define getchar() gc()
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
const int N=3e5+5;
const int INF=0x3f3f3f3f;
struct Tree
{
	int l,r;
	int size;
} tree[N*40];
int cnt,root[N];
#define lc(rt) tree[rt].l
#define rc(rt) tree[rt].r
inline void update(int &rt,int pre,int l,int r,int pos)
{
	rt=++cnt;
	tree[rt]=tree[pre];
	++tree[rt].size;
	if(l==r)
		return;
	int mid=(l+r)>>1;
	if(pos<=mid)
		update(lc(rt),lc(pre),l,mid,pos);
	else
		update(rc(rt),rc(pre),mid+1,r,pos);
}
inline int query(int rtl,int rtr,int l,int r,int size)
{
//	printf("%d %d %d %d\n",l,r,tree[rtr].size-tree[rtl].size);
	if(tree[rtr].size-tree[rtl].size<=size)
		return 0;
//	printf("[%d,%d]\n",l,r);
	if(l==r)
		return l;
	int mid=(l+r)>>1,nowans;
	if((nowans=query(lc(rtl),lc(rtr),l,mid,size))!=0)
		return nowans;
	if((nowans=query(rc(rtl),rc(rtr),mid+1,r,size))!=0)
		return nowans;
	return 0;
}
int n,m;
int a[N],p[N];
signed main()
{
	read(n,m);
	for(int i=1; i<=n; ++i)
	{
		read(a[i]);
		p[i]=a[i];
	}
	sort(p+1,p+1+n);
	p[0]=-1;
	int tot=(int)(unique(p+1,p+1+n)-p-1);
	for(int i=1; i<=n; ++i)
	{
		update(root[i],root[i-1],1,tot,(int)(lower_bound(p+1,p+1+tot,a[i])-p));
//		printf("%d\n",(int)(lower_bound(p+1,p+1+tot,a[i])-p));
	}
	for(int i=1; i<=m; ++i)
	{
		int l,r,k;
		read(l,r,k);
//		printf(" %d\n",(r-l+1)/k);
		printf("%d\n",p[query(root[l-1],root[r],1,tot,(r-l+1)/k)]);
	}
	return 0;
}

