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
const int N=2e5+5;
int n,m;
struct Query
{
	int l,r,t;
} q[N];
int a[N];
int p[N],tot;

struct Tree
{
	int l,r;
	int size;
} tree[N*40];
#define lc(x) tree[x].l
#define rc(x) tree[x].r
int root[N],cnt;
inline void update(int pre,int &rt,int l,int r,int pos)
{
	rt=++cnt;
	tree[rt]=tree[pre];
	++tree[rt].size;
	if(l==r)
		return;
	int mid=(l+r)>>1;
	if(pos<=mid)
		update(lc(pre),lc(rt),l,mid,pos);
	else
		update(rc(pre),rc(rt),mid+1,r,pos);
}
inline int query(int rootl,int rootr,int l,int r,int k_th)
{
	if(l==r)
	{
		int sum=tree[rootr].size-tree[rootl].size;
		if(sum>=k_th)
			return l;
		else
			return n+1;
	}
	int mid=(l+r)>>1;
	int sum=tree[lc(rootr)].size-tree[lc(rootl)].size;
	if(k_th<=sum)
		return query(lc(rootl),lc(rootr),l,mid,k_th);
	else
		return query(rc(rootl),rc(rootr),mid+1,r,k_th-sum);
}
int answer[N];
vector<int>g[N];
signed main()
{
	read(m,n);
	for(int i=1; i<=m; ++i)
		read(q[i].l,q[i].r,q[i].t);

	for(int i=1; i<=n; ++i)
	{
		read(a[i]);
		p[i]=a[i];
	}

	sort(p+1,p+1+n);
	tot=(int)(unique(p+1,p+1+n)-p-1);

	for(int i=1; i<=n; ++i)
	{
		a[i]=(int)(lower_bound(p+1,p+1+tot,a[i])-p);
		g[a[i]].push_back(i);
	}
	for(int i=1; i<=tot; ++i)
	{
		update(root[i-1],root[i],1,n,g[i][0]);
		for(unsigned j=1; j<g[i].size(); ++j)
			update(root[i],root[i],1,n,g[i][j]);
	}

	for(int i=1; i<=m; ++i)
	{
		const int ql=(int)(lower_bound(p+1,p+1+tot,q[i].l)-p),
		          qr=(int)(upper_bound(p+1,p+1+tot,q[i].r)-p-1),
		          &qt=q[i].t;
		int res=query(root[ql-1],root[qr],1,n,qt);
		++answer[res];
	}
	for(int i=1; i<=n; ++i)
		printf("%d\n",answer[i]);
	return 0;
}


