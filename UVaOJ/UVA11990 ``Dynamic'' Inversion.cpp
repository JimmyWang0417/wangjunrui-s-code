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
inline void clear(T*a,int l,int r,int val)
{
	memset(&a[l],val,sizeof(T)*(r-l+1));
}
const int N=2e5+5;
int n,m;
struct Tree
{
	int l,r,size;
} tree[N*400];
int cnt,root[N];
#define lc(rt) tree[rt].l
#define rc(rt) tree[rt].r
inline void pushup(int rt)
{
	tree[rt].size=tree[lc(rt)].size+tree[rc(rt)].size;
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
inline int query(int rt,int l,int r,int x,int y)
{
	if(r<x||l>y)
		return 0;
	if(x<=l&&r<=y)
		return tree[rt].size;
	int mid=(l+r)>>1;
	return query(lc(rt),l,mid,x,y)+query(rc(rt),mid+1,r,x,y);
}
inline void update(int rt,int pos,int val)
{
	for(re int i=rt; i<=n; i+=lowbit(i))
		update(root[i],1,n,pos,val);
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
int pos[N];
ll ans;
signed main()
{
	while(scanf("%d%d",&n,&m)!=EOF)
	{
		for(re int i=1; i<=n; ++i)
		{
			int val;
			read(val);
			pos[val]=i;
			ans+=query(i,val+1,n);
			update(i,val,1);
		}
		for(re int i=1; i<=m; ++i)
		{
			int val;
			read(val);
			printf("%lld\n",ans);
			ans-=query(1,pos[val],val+1,n)+query(pos[val]+1,n,1,val-1);
			update(pos[val],val,-1);
		}
		clear(tree,1,cnt,0);
		clear(root,1,n,0);
		ans=cnt=0;
	}
	return 0;
}


