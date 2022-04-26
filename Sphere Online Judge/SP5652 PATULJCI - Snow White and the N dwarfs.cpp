#include <cstdio>
#include <algorithm>
#define ll long long
#define re register
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
const int N=3e5+5,INF=0x7fffffff;
struct Tree
{
	int size;
	int l,r;
} tree[N*50];
#define lc(x) tree[x].l
#define rc(x) tree[x].r
int root[N],cnt;
inline void update(int pre,int &rt,int l,int r,int pos,int val)
{
	rt=++cnt;
	tree[rt]=tree[pre];
	tree[rt].size+=val;
	if(l==r)
		return;
	int mid=(l+r)>>1;
	if(pos<=mid)
		update(lc(pre),lc(rt),l,mid,pos,val);
	else
		update(rc(pre),rc(rt),mid+1,r,pos,val);
}
inline int query(int pre,int rt,int l,int r,int size)
{
	if(tree[rt].size-tree[pre].size<size)
		return INF;
	if(l==r)
		return l;
	int mid=(l+r)>>1;
	return min(query(lc(pre),lc(rt),l,mid,size),query(rc(pre),rc(rt),mid+1,r,size));
}
int n,m,limit;
int main()
{
	read(n),read(limit);
	for(re int i=1; i<=n; ++i)
	{
		int val;
		read(val);
		update(root[i-1],root[i],1,limit,val,1);
	}
	read(m);
	while(m--)
	{
		int l,r;
		read(l),read(r);
		int ans=query(root[l-1],root[r],1,limit,((r-l+1)>>1)+1);
		if(ans==INF)
			printf("no\n");
		else
			printf("yes %d\n",ans);
	}
	return 0;
}
