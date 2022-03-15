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
int n,m,a[N],p[N],tot;
struct Tree
{
	int l,r,size;
} tree[N*400];
int cnt;
#define lc(x) tree[x].l
#define rc(x) tree[x].r
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
inline int query(int rt,int l,int r,int x,int y)
{
	if(!rt||r<x||l>y)
		return 0;
	if(x<=l&&r<=y)
		return tree[rt].size;
	int mid=(l+r)>>1;
	return query(lc(rt),l,mid,x,y)+query(rc(rt),mid+1,r,x,y);
}
int root[N];
inline void update(int rt,int pos,int val)
{
	for(int i=rt; i<=n; i+=lowbit(i))
		update(root[i],1,tot,pos,val);
}
inline int query(int rt,int x,int y)
{
	int ans=0;
	for(int i=rt; i; i-=lowbit(i))
		ans+=query(root[i],1,tot,x,y);
	return ans;
}
inline int query(int l,int r,int x,int y)
{
	return query(r,x,y)-query(l-1,x,y);
}
int ans=0;
inline void insert(int pos,int val)
{
	ans+=query(1,pos-1,val+1,tot);
	ans+=query(pos+1,n,1,val-1);
	update(pos,val,1);
}
inline void del(int pos,int val)
{
	ans-=query(1,pos-1,val+1,tot);
	ans-=query(pos+1,n,1,val-1);
	update(pos,val,-1);
}
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
	for(int i=1; i<=n; ++i)
		a[i]=(int)(lower_bound(p+1,p+1+tot,a[i])-p);
	for(int i=1; i<=n; ++i)
		insert(i,a[i]);
	printf("%d\n",ans);
	read(m);
	for(int i=1; i<=m; ++i)
	{
		int x,y;
		read(x,y);
		del(x,a[x]);
//		printf("1:%d\n",ans);
		del(y,a[y]);
//		printf("2:%d\n",ans);
		swap(a[x],a[y]);
		insert(x,a[x]);
//		printf("3:%d\n",ans);
		insert(y,a[y]);
		printf("%d\n",ans);
	}
	return 0;
}


