#include <cstdio>
#include <algorithm>
#define re register
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
const int N=5e5+5;
int n,m,p[N],a[N];
struct Tree
{
	int l,r,size;
} tree[N*40];
int cnt;
#define lc(x) tree[x].l
#define rc(x) tree[x].r
inline void insert(int pre,int &rt,int l,int r,int pos)
{
	rt=++cnt;
	tree[rt]=tree[pre];
	++tree[rt].size;
	if(l==r)
		return;
	int mid=(l+r)>>1;
	if(pos<=mid)
		insert(lc(pre),lc(rt),l,mid,pos);
	else
		insert(rc(pre),rc(rt),mid+1,r,pos);
}
inline int query(int rtl,int rtr,int l,int r,int rk)
{
//	printf("%d %d %d %d\n",tree[rtl].size,tree[rtr].size,l,r,);
	if(tree[rtr].size-tree[rtl].size<=rk)
		return 0;
	if(l==r)
		return l;
	int mid=(l+r)>>1;
	return max(query(lc(rtl),lc(rtr),l,mid,rk),query(rc(rtl),rc(rtr),mid+1,r,rk));
}
int root[N];
int main()
{
	read(n),read(m);
	for(re int i=1; i<=n; ++i)
	{
		read(a[i]);
		p[i]=a[i];
	}
	sort(p+1,p+1+n);
	int tot=(int)(unique(p+1,p+1+n)-p-1);
	for(re int i=1; i<=n; ++i)
		insert(root[i-1],root[i],1,tot,(int)(lower_bound(p+1,p+1+tot,a[i])-p));
	while(m--)
	{
		int l,r;
		read(l),read(r);
		printf("%d\n",p[query(root[l-1],root[r],1,tot,(r-l+1)/2)]);
	}
	return 0;
}
