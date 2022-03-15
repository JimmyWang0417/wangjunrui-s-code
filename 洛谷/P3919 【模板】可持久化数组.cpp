#include<cstdio>
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
const int N=1e6+10;
int tot,n,m,a[N],root[N*25];
struct node
{
	int lc,rc,val;
} tree[N*25];
inline void build(int &root,int l,int r)
{
	root=++tot;
	if(l==r)
	{
		tree[root].val=a[l];
		return;
	}
	int mid=l+r>>1;
	build(tree[root].lc,l,mid);
	build(tree[root].rc,mid+1,r);
}
inline void change(int &root,int pre,int l,int r,int q,int cnt)
{
	root=++tot;
	tree[root]=tree[pre];
	if(l==r)
	{
		tree[root].val=cnt;
		return;
	}
	int mid=l+r>>1;
	if(q<=mid)
		change(tree[root].lc,tree[pre].lc,l,mid,q,cnt);
	else
		change(tree[root].rc,tree[pre].rc,mid+1,r,q,cnt);
}
inline int query(int root,int l,int r,int q)
{
	if(l==r)
		return tree[root].val;
	int mid=l+r>>1;
	if(q<=mid)
		return query(tree[root].lc,l,mid,q);
	else
		return query(tree[root].rc,mid+1,r,q);
}
int main()
{
	read(n);
	read(m);
	for(re int i=1; i<=n; i++)
		read(a[i]);
	build(root[0],1,n);
	re int pre,loc,value,o;
	for(re int i=1; i<=m; i++)
	{
		read(pre);
		read(o);
		read(loc);
		if(o==1)
		{
			read(value);
			change(root[i],root[pre],1,n,loc,value);
		}
		else if(o==2)
		{
			printf("%d\n",query(root[pre],1,n,loc));
			root[i]=root[pre];
		}
	}
	return 0;
}
