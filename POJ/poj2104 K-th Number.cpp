#include<cstdio>
#include<algorithm>
#define re register
using namespace std;
template<typename T>
inline void read(T &x)
{
	x=0;
	char s=(char)getchar();
	bool flag=false;
	while(s<'0'||s>'9')
	{
		if(s=='-')
			flag=true;
		s=(char)getchar();
	}
	while(s>='0'&&s<='9')
	{
		x=(x<<1)+(x<<3)+(s^'0');
		s=(char)getchar();
	}
	if(flag)
		x=~x+1;
	return;
}
const int N=100000+5;
int n,m;
struct Tree
{
	int l,r,size;
} tree[N*40];
#define lc(x) tree[x].l
#define rc(x) tree[x].r
int root[N],p[N],a[N],cnt;
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
inline int query(int rootl,int rootr,int l,int r,int rk)
{
	if(l==r)
		return p[l];
	int mid=(l+r)>>1,sum=tree[lc(rootr)].size-tree[lc(rootl)].size;
	if(rk<=sum)
		return query(lc(rootl),lc(rootr),l,mid,rk);
	else
		return query(rc(rootl),rc(rootr),mid+1,r,rk-sum);
}
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
		insert(root[i-1],root[i],1,n,(int)(lower_bound(p+1,p+1+tot,a[i])-p));
	for(re int i=1; i<=m; ++i)
	{
		int l,r,rk;
		read(l),read(r),read(rk);
		printf("%d\n",query(root[l-1],root[r],1,n,rk));
	}
	return 0;
}
