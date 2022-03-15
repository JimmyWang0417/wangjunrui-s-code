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
int n;
int X[N];
struct Line
{
	int sum;

	int cnt;
	bool suf,pre;

	int len;
} tree[N*4];
#define lc (rt<<1)
#define rc (rt<<1|1)
inline void pushup(int rt,int l,int r)
{
	if(tree[rt].sum)
	{
		tree[rt].len=X[r+1]-X[l];
		tree[rt].cnt=tree[rt].pre=tree[rt].suf=true;
	}
	else if(l==r)
		tree[rt].len=tree[rt].cnt=tree[rt].pre=tree[rt].suf=false;
	else
	{
		tree[rt].len=tree[lc].len+tree[rc].len;
		tree[rt].cnt=tree[lc].cnt+tree[rc].cnt-(tree[lc].suf&&tree[rc].pre);
		tree[rt].pre=tree[lc].pre,tree[rt].suf=tree[rc].suf;
	}
}
inline void build(int rt,int l,int r)
{
	tree[rt].len=tree[rt].sum=0;
	tree[rt].cnt=tree[rt].suf=tree[rt].pre=false;
	if(l==r)
		return;
	int mid=(l+r)>>1;
	build(lc,l,mid);
	build(rc,mid+1,r);
}
inline void update(int rt,int l,int r,int x,int y,int val)
{
	if(r<x||l>y)
		return;
	if(x<=l&&r<=y)
	{
		tree[rt].sum+=val;
		pushup(rt,l,r);
		return;
	}
	int mid=(l+r)>>1;
	update(lc,l,mid,x,y,val);
	update(rc,mid+1,r,x,y,val);
	pushup(rt,l,r);
}
struct node
{
	int l,r,h;
	int mark;
	node(int _l=0,int _r=0,int _h=0,int _mark=0):l(_l),r(_r),h(_h),mark(_mark) {}
	inline bool operator <(const node &rhs)const
	{
		return h==rhs.h?mark>rhs.mark:h<rhs.h;
	}
} a[N];
int m;
int tot;
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	while(cin>>n&&n)
	{
		tot=m=0;
		for(int i=1; i<=n; ++i)
		{
			int x1,y1,x2,y2;
			cin>>x1>>y1>>x2>>y2;
			X[++tot]=x1,X[++tot]=x2;
			a[++m]=node(x1,x2,y1,1);
			a[++m]=node(x1,x2,y2,-1);
		}

		sort(X+1,X+tot+1);
		tot=(int)(unique(X+1,X+1+tot)-X-1);

		sort(a+1,a+1+m);
		build(1,1,tot-1);

		ll ans=0;
		int las=0;
		for(int i=1; i<m; ++i)
		{
			int l=(int)(lower_bound(X+1,X+1+tot,a[i].l)-X);
			int r=(int)(lower_bound(X+1,X+1+tot,a[i].r)-X);
			if(l<r)
				update(1,1,tot-1,l,r-1,a[i].mark);
			ans+=2*tree[1].cnt*(a[i+1].h-a[i].h)+abs(tree[1].len-las);
			las=tree[1].len;
//			printf("%d %d\n",tree[1].cnt,tree[1].len);
		}
		ans+=las;
		cout<<ans<<'\n';
	}
	return 0;
}

