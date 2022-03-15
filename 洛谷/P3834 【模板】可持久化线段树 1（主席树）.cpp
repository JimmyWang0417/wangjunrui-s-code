#include<cstdio>
#include<algorithm>
#define re register
using namespace std;
template<typename T>
inline void read(T&x)
{
	x=0;
	char s=getchar();
	bool f=false;
	while(!(s>='0'&&s<='9'))
	{
		if(s=='-')
			f=true;
		s=getchar();
	}
	while(s>='0'&&s<='9')
	{
		x=(x<<1)+(x<<3)+s-'0';
		s=getchar();
	}
	if(f)
		x=(~x)+1;
}
const int N=2e5+10;
int n,m,root[N],q,tot,a[N],b[N];
struct node
{
	int sum,l,r;
} tree[N*25];
inline void build(int &root,int l,int r)
{
	root=++tot;
	tree[root].sum=0;
	if(l<r)
	{
		int mid=l+r>>1;
		build(tree[root].l,l,mid);
		build(tree[root].r,mid+1,r);
	}
	return;
}
inline void update(int &root,int pre,int l,int r,int x)
{
	root=++tot;
	tree[root]=tree[pre];
	tree[root].sum++;
	if(l<r)
	{
		int mid=l+r>>1;
		if(x<=mid)
			update(tree[root].l,tree[pre].l,l,mid,x);
		else
			update(tree[root].r,tree[pre].r,mid+1,r,x);
	}
}
inline int query(int x,int y,int l,int r,int k)
{
	if(l>=r)
		return l;
	int size=tree[tree[y].l].sum-tree[tree[x].l].sum,mid=l+r>>1;
	if(size>=k)
		return query(tree[x].l,tree[y].l,l,mid,k);
	return query(tree[x].r,tree[y].r,mid+1,r,k-size);
}
int main()
{
	read(n);
	read(q);
	for(re int i=1; i<=n; i++)
	{
		read(a[i]);
		b[i]=a[i];
	}
	sort(b+1,b+1+n);
	m=unique(b+1,b+1+n)-b-1;
	build(root[0],1,m);
	for(re int i=1,t; i<=n; i++)
	{
		t=lower_bound(b+1,b+1+m,a[i])-b;
		update(root[i],root[i-1],1,m,t);
	}
	re int l,r,k;
	while(q--)
	{
		read(l);
		read(r);
		read(k);
		printf("%d\n",b[query(root[l-1],root[r],1,m,k)]); 
	}
	return 0;
}
