#include <cstdio>
#define re register
#define ll long long
#define swap(x,y) (x^=y^=x)
#define lowbit(x) (x&(-x))
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
const int N=2e5+5;
struct Tree
{
	int l,r,size;
} tree[N*200];
int cnt;
#define lc(x) tree[x].l
#define rc(x) tree[x].r
int n,a[N];
int root[N];
ll ans;
inline int query(int &rt,int l,int r,int x,int y)
{
	if(!rt||r<x||l>y)
		return 0;
	if(x<=l&&r<=y)
		return tree[rt].size;
	int mid=(l+r)>>1;
	return query(lc(rt),l,mid,x,y)+query(rc(rt),mid+1,r,x,y);
}
inline int query(int pos,int x,int y)
{
	int res=0;
	for(re int i=pos; i; i-=lowbit(i))
		res+=query(root[i],1,n,x,y);
	return res;
}
inline int query(int l,int r,int x,int y)
{
	return query(r,x,y)-query(l-1,x,y);
}
inline void update(int &rt,int l,int r,int pos,int val)
{
	if(!rt)
		rt=++cnt;
	tree[rt].size+=val;
	if(l==r)
		return;
	int mid=(l+r)>>1;
	if(pos<=mid)
		update(lc(rt),l,mid,pos,val);
	else
		update(rc(rt),mid+1,r,pos,val);
}
inline void update(int pos,int val)
{
	for(re int i=pos; i<=n; i+=lowbit(i))
		update(root[i],1,n,a[pos],val);
	ans+=(query(1,pos-1,a[pos]+1,n)+query(pos+1,n,1,a[pos]-1))*val;
}
inline void work()
{
}
signed main()
{
	int q;
	read(n),read(q);
	for(re int i=1; i<=n; ++i)
	{
		a[i]=i;
//		printf("%d ",i);
		update(i,1);
	}
	while(q--)
	{
		int x,y;
		read(x),read(y);
		int val1=a[x],val2=a[y];
		update(x,-1);
		a[x]=val2;
		update(x,1);
		update(y,-1);
		a[y]=val1;
		update(y,1);
		printf("%lld\n",ans);
	}
	return 0;
}

