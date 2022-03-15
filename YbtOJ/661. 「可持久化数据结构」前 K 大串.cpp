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
const ll INF=1e18;
int n,k,a[N];
int p[N],tot,c[N];
int pos[N],pre[N];
struct Tree
{
	int l,r,id;
	ll max,add;
} tree[N*100];
int root[N],cnt;
#define lc(x) tree[x].l
#define rc(x) tree[x].r
inline void pushup(int rt)
{
	if(!tree[rc(rt)].id||(tree[lc(rt)].id&&tree[lc(rt)].max>tree[rc(rt)].max))
	{
		tree[rt].max=tree[lc(rt)].max;
		tree[rt].id=tree[lc(rt)].id;
	}
	else
	{
		tree[rt].max=tree[rc(rt)].max;
		tree[rt].id=tree[rc(rt)].id;
	}
}
inline void pushdown(int rt)
{
	if(tree[rt].add)
	{
		int x1,x2;
		tree[x1=++cnt]=tree[lc(rt)];
		tree[x2=++cnt]=tree[rc(rt)];
		tree[x1].max+=tree[rt].add;
		tree[x1].add+=tree[rt].add;
		tree[x2].max+=tree[rt].add;
		tree[x2].add+=tree[rt].add;
		tree[rt].add=0;
		lc(rt)=x1;
		rc(rt)=x2;
	}
}
inline void build(int &rt,int l,int r)
{
	rt=++cnt;
	tree[rt].max=-INF;
	if(l==r)
	{
		tree[rt].id=l;
		return;
	}
	int mid=(l+r)>>1;
	build(lc(rt),l,mid);
	build(rc(rt),mid+1,r);
}
inline void update(int prert,int &rt,int l,int r,int x,int y,ll val)
{
	if(r<x||l>y)
		return;
	tree[rt=++cnt]=tree[prert];
	if(x<=l&&r<=y)
	{
		tree[rt].add+=val;
		tree[rt].max+=val;
		if(!tree[rt].id)
			tree[rt].id=l;
		return;
	}
	pushdown(prert);
	pushdown(rt);
	int mid=(l+r)>>1;
	update(lc(prert),lc(rt),l,mid,x,y,val);
	update(rc(prert),rc(rt),mid+1,r,x,y,val);
	pushup(rt);
}
inline pair<ll,int> ckmax(pair<ll,int> rhsx,pair<ll,int> rhsy)
{
	return !rhsy.second||rhsx.first>rhsy.first?rhsx:rhsy;
}
inline pair<ll,int> query(int rt,int l,int r,int x,int y)
{
	if(x<=l&&r<=y)
		return make_pair(tree[rt].max,tree[rt].id);
	pushdown(rt);
	int mid=(l+r)>>1;
	if(y<=mid)
		return query(lc(rt),l,mid,x,y);
	else if(x>mid)
		return query(rc(rt),mid+1,r,x,y);
	else
		return ckmax(query(lc(rt),l,mid,x,y),query(rc(rt),mid+1,r,x,y));
}
struct node
{
	int leftl,leftr,right,id;
	ll val;
	node(int _l1=0,int _l2=0,int _r=0,int _id=0,ll _val=0):leftl(_l1),leftr(_l2),right(_r),id(_id),val(_val) {}
	inline bool operator <(const node &rhs)const
	{
		return val<rhs.val;
	}
};
signed main()
{
	freopen("seq.in", "r", stdin);
	freopen("seq.out", "w", stdout);
	read(n,k);
	for(int i=1; i<=n; ++i)
	{
		read(a[i]);
		p[i]=a[i];
	}
	sort(p+1,p+1+n);
	tot=(int)(unique(p+1,p+1+n)-p-1);
	for(int i=1; i<=n; ++i)
	{
		c[i]=(int)(lower_bound(p+1,p+1+tot,a[i])-p);
		pre[i]=pos[c[i]];
		pos[c[i]]=i;
	}
	build(root[0],1,n);
	for(int i=1; i<=n; ++i)
	{
		update(root[i-1],root[i],1,n,i,i,INF);
		update(root[i],root[i],1,n,pre[i]+1,i,a[i]);
	}
//	for(int i=1; i<=n; ++i)
//	{
//		for(int j=i; j<=n; ++j)
//		{
//			printf("%d %d %lld\n",i,j,query(root[j],1,n,i,i).first);
//		}
//	}
	priority_queue<node>q;
	for(int i=1; i<=n; ++i)
	{
		pair<ll,int>now=query(root[i],1,n,1,i);
		q.push(node(1,i,i,now.second,now.first));
	}
	while(k--)
	{
		node u=q.top();
		q.pop();
		if(k==0)
		{
			printf("%lld\n",u.val);
			break;
		}
		if(u.leftl<u.id)
		{
			pair<ll,int>now=query(root[u.right],1,n,u.leftl,u.id-1);
			q.push(node(u.leftl,u.id-1,u.right,now.second,now.first));
		}
		if(u.id<u.leftr)
		{
			pair<ll,int>now=query(root[u.right],1,n,u.id+1,u.leftr);
			q.push(node(u.id+1,u.leftr,u.right,now.second,now.first));
		}
	}
	return 0;
}

