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
const int N=2e4+5;
struct node
{
	int pre,suf,sum;
	node(int _pre=0,int _suf=0,int _sum=0):pre(_pre),suf(_suf),sum(_sum) {}
	inline node operator +(const node &rhs)const
	{
		return node(max(pre,sum+rhs.pre),max(rhs.suf,suf+rhs.sum),sum+rhs.sum);
	}
};
struct Tree
{
	int l,r;
	node val;
} tree[N*50];
int root[N],cnt;
#define lc(x) tree[x].l
#define rc(x) tree[x].r
inline void pushup(int rt)
{
	tree[rt].val=tree[lc(rt)].val+tree[rc(rt)].val;
}
inline void build(int &rt,int l,int r)
{
	rt=++cnt;
	if(l==r)
	{
		tree[rt].val=node(1,1,1);
		return;
	}
	int mid=(l+r)>>1;
	build(lc(rt),l,mid);
	build(rc(rt),mid+1,r);
	pushup(rt);
}
inline void update(int pre,int &rt,int l,int r,int pos)
{
	rt=++cnt;
	tree[rt]=tree[pre];
	if(l==r)
	{
		tree[rt].val=node(-1,-1,-1);
		return;
	}
	int mid=(l+r)>>1;
	if(pos<=mid)
		update(lc(pre),lc(rt),l,mid,pos);
	else
		update(rc(pre),rc(rt),mid+1,r,pos);
	pushup(rt);
}
inline node query(int rt,int l,int r,int x,int y)
{
	if(x<=l&&r<=y)
		return tree[rt].val;
	int mid=(l+r)>>1;
	if(y<=mid)
		return query(lc(rt),l,mid,x,y);
	if(x>mid)
		return query(rc(rt),mid+1,r,x,y);
	return query(lc(rt),l,mid,x,y)+query(rc(rt),mid+1,r,x,y);
}
int n,m;
vector<int>g[N];
int lastans=0;
inline bool check(int a,int b,int c,int d,int v)
{
	int now=0;
	if(b+1<=c-1)
		now+=query(root[v],1,n,b+1,c-1).sum;
	now+=query(root[v],1,n,a,b).suf;
	now+=query(root[v],1,n,c,d).pre;
	return now>=0;
}
int p[N],tot;
inline void work()
{
	int q[4];
	for(int i=0; i<4; ++i)
	{
		read(q[i]);
		q[i]=(q[i]+lastans)%n+1;
	}
	sort(q,q+4);
	int a=q[0],b=q[1],c=q[2],d=q[3];
//	printf("%d %d %d %d %d\n",a,b,c,d,check(a,b,c,d,4));
	int l=1,r=tot,ans=1;
	while(l<=r)
	{
		int mid=(l+r)>>1;
		if(check(a,b,c,d,mid))
		{
			ans=mid;
			l=mid+1;
		}
		else
			r=mid-1;
	}
	printf("%d\n",lastans=p[ans]);
}
int a[N];
signed main()
{
	read(n);
	for(int i=1; i<=n; ++i)
	{
		read(a[i]);
		p[i]=a[i];
	}
	sort(p+1,p+1+n);
	tot=(int)(unique(p+1,p+1+n)-p-1);
//	for(int i=1; i<=tot; ++i)
//		printf("%d ",p[i]);
//	putchar('\n');
	for(int i=1; i<=n; ++i)
	{
		a[i]=(int)(lower_bound(p+1,p+1+tot,a[i])-p);
		g[a[i]].push_back(i);
	}
	build(root[1],1,n);
	for(int i=2; i<=tot; ++i)
	{
		update(root[i-1],root[i],1,n,g[i-1][0]);
		for(int j=1; j<(int)g[i-1].size(); ++j)
			update(root[i],root[i],1,n,g[i-1][j]);
	}
//	printf("%d\n",query(root[5],1,n,1,n).sum);
	read(m);
	while(m--)
		work();
	return 0;
}


