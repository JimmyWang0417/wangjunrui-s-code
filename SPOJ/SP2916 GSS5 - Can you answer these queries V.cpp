#include<cstdio>
#include<algorithm>
using namespace std;

#define re register
#define ll long long
#define lc (rt<<1)
#define rc (rt<<1|1)

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
const int N=1e4+5;
int n,m,a[N],T;
struct Tree
{
	int suf,pre,sum,ans;
} tree[N<<2];
inline void pushup(int rt)
{
	tree[rt].suf=max(tree[rc].suf,tree[lc].suf+tree[rc].sum);
	tree[rt].pre=max(tree[lc].pre,tree[lc].sum+tree[rc].pre);
	tree[rt].sum=tree[lc].sum+tree[rc].sum;
	tree[rt].ans=max(max(tree[lc].ans,tree[rc].ans),tree[lc].suf+tree[rc].pre);
}
inline void build(int rt,int l,int r)
{
	if(l==r)
	{
		tree[rt].suf=tree[rt].pre=tree[rt].sum=tree[rt].ans=a[l];
		return;
	}
	int mid=(l+r)>>1;
	build(lc,l,mid);
	build(rc,mid+1,r);
	pushup(rt);
}
inline Tree query(int rt,int l,int r,int x,int y)
{
	if(x<=l&&r<=y)
		return tree[rt];
	int mid=(l+r)>>1;
	if(y<=mid)
		return query(lc,l,mid,x,y);
	if(mid<x)
		return query(rc,mid+1,r,x,y);
	Tree L=query(lc,l,mid,x,y),R=query(rc,mid+1,r,x,y),ans;
	ans.suf=max(R.suf,L.suf+R.sum);
	ans.pre=max(L.pre,L.sum+R.pre);
	ans.sum=L.sum+R.sum;
	ans.ans=max(max(L.ans,R.ans),L.suf+R.pre);
	return ans;
}
#define Query(x,y) query(1,1,n,x,y)
inline void getans()
{
	int l1,r1,l2,r2;
	read(l1),read(r1),read(l2),read(r2);
	if(r1<l2)
	{
		printf("%d\n",Query(l1,r1).suf+Query(r1,l2).sum+Query(l2,r2).pre-a[r1]-a[l2]);
		return;
	}
	int ans=Query(l2,r1).ans;
//	printf("%d %d %d\n",ans,Query(l1,l2).suf+Query(l2,r2).pre-a[l2],Query(l1,r1).suf+Query(r1,r2).pre-a[r1]);
	if(l1<l2)
		ans=max(ans,Query(l1,l2).suf+Query(l2,r2).pre-a[l2]);
	if(r1<r2)
		ans=max(ans,Query(l1,r1).suf+Query(r1,r2).pre-a[r1]);
	printf("%d\n",ans);
	return;
}
int main()
{
	read(T);
	while(T--)
	{
		read(n);
		for(re int i=1; i<=n; ++i)
			read(a[i]);
		build(1,1,n);
		read(m);
		while(m--)
			getans();
	}
	return 0;
}
