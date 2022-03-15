#include <cstdio>
#define re register
#define ll long long
#define min(x,y) ((x)<(y)?(x):(y))
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
	int l,r;
	int size;
} tree[N*40];
int cnt;
#define lc(x) tree[x].l
#define rc(x) tree[x].r
ll ans,ans1,ans2;
inline void pushup(int rt)
{
	tree[rt].size=tree[lc(rt)].size+tree[rc(rt)].size;
}
inline int merge(int x,int y,int l=1,int r=2e5)
{
	if(!x||!y)
		return x|y;
	if(l==r)
	{
		tree[x].size+=tree[y].size;
		return x;
	}
	ans1+=1ll*tree[lc(x)].size*tree[rc(y)].size;
	ans2+=1ll*tree[rc(x)].size*tree[lc(y)].size;
	int mid=(l+r)>>1;
	lc(x)=merge(lc(x),lc(y),l,mid);
	rc(x)=merge(rc(x),rc(y),mid+1,r);
	pushup(x);
	return x;
}
inline void update(int &rt,int l,int r,int pos,int val)
{
	if(!rt)
		rt=++cnt;
//	printf("%d %d\n",l,r);
	tree[rt].size+=val;
	if(l==r)
		return;
	int mid=(l+r)>>1;
	if(pos<=mid)
		update(lc(rt),l,mid,pos,val);
	else
		update(rc(rt),mid+1,r,pos,val);
}
inline void dfs(int &rt)
{
	int x,l=0,r=0;
	read(x);
	if(!x)
	{
		dfs(l),dfs(r);
		rt=merge(l,r);
		ans+=min(ans1,ans2);
		ans1=ans2=0;
	}
	else
		update(rt,1,2e5,x,1);
}
int main()
{
	int n,root;
	read(n);
	dfs(root);
	printf("%lld\n",ans);
	return 0;
}

