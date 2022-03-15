#include <cstdio>
#include <iostream>
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
const int N=805,INF=0x3f3f3f3f;
struct Tree
{
	int max,min;
} tree[N*4][N*4];
#define lc(rt) (rt<<1)
#define rc(rt) (rt<<1|1)
int n,a[N][N];
inline void buildy(int rtx,int rt,int l,int r,int x)
{
	if(l==r)
	{
		if(~x)
			tree[rtx][rt].max=tree[rtx][rt].min=a[x][l];
		else
		{
			tree[rtx][rt].max=max(tree[lc(rtx)][rt].max,tree[rc(rtx)][rt].max);
			tree[rtx][rt].min=min(tree[lc(rtx)][rt].min,tree[rc(rtx)][rt].min);
		}
		return;
	}
	int mid=(l+r)>>1;
	buildy(rtx,lc(rt),l,mid,x);
	buildy(rtx,rc(rt),mid+1,r,x);
	tree[rtx][rt].max=max(tree[rtx][lc(rt)].max,tree[rtx][rc(rt)].max);
	tree[rtx][rt].min=min(tree[rtx][lc(rt)].min,tree[rtx][rc(rt)].min);
}
inline void buildx(int rt,int l,int r)
{
	if(l==r)
	{
		buildy(rt,1,1,n,l);
		return;
	}
	int mid=(l+r)>>1;
	buildx(lc(rt),l,mid);
	buildx(rc(rt),mid+1,r);
	buildy(rt,1,1,n,-1);
}
int lx,ly,rx,ry;
int maxx,minn;
inline void queryy(int rtx,int rt,int l,int r)
{
	if(r<ly||l>ry)
		return;
	if(ly<=l&&r<=ry)
	{
		maxx=max(tree[rtx][rt].max,maxx);
		minn=min(tree[rtx][rt].min,minn);
		return;
	}
	int mid=(l+r)>>1;
	queryy(rtx,lc(rt),l,mid);
	queryy(rtx,rc(rt),mid+1,r);
}
inline void queryx(int rt,int l,int r)
{
	if(r<lx||l>rx)
		return;
	if(lx<=l&&r<=rx)
	{
		queryy(rt,1,1,n);
		return;
	}
	int mid=(l+r)>>1;
	queryx(lc(rt),l,mid);
	queryx(rc(rt),mid+1,r);
}
int posx,posy;
inline void updatey(int rtx,int rt,int l,int r,int val,int x)
{
	if(l==r)
	{
		if(~x)
			tree[rtx][rt].max=tree[rtx][rt].min=val;
		else
		{
			tree[rtx][rt].max=max(tree[lc(rtx)][rt].max,tree[rc(rtx)][rt].max);
			tree[rtx][rt].min=min(tree[lc(rtx)][rt].min,tree[rc(rtx)][rt].min);
		}
		return;
	}
	int mid=(l+r)>>1;
	if(posy<=mid)
		updatey(rtx,lc(rt),l,mid,val,x);
	else
		updatey(rtx,rc(rt),mid+1,r,val,x);
	tree[rtx][rt].max=max(tree[rtx][lc(rt)].max,tree[rtx][rc(rt)].max);
	tree[rtx][rt].min=min(tree[rtx][lc(rt)].min,tree[rtx][rc(rt)].min);
}
inline void updatex(int rt,int l,int r,int val)
{
	if(l==r)
	{
		updatey(rt,1,1,n,val,l);
		return;
	}
	int mid=(l+r)>>1;
	if(posx<=mid)
		updatex(lc(rt),l,mid,val);
	else
		updatex(rc(rt),mid+1,r,val);
	updatey(rt,1,1,n,val,-1);
}
inline void work()
{
	read(n);
	for(re int i=1; i<=n; ++i)
		for(re int j=1; j<=n; ++j)
			read(a[i][j]);
	buildx(1,1,n);
	int q;
	read(q);
	while(q--)
	{
		int l;
		read(posx),read(posy),read(l);
		l=(l+1)>>1;
		lx=max(1,posx-l+1),ly=max(1,posy-l+1);
		rx=min(n,posx+l-1),ry=min(n,posy+l-1);
		maxx=-INF,minn=INF;
		queryx(1,1,n);
		int ans=(maxx+minn)>>1;
		printf("%d\n",ans);
		updatex(1,1,n,ans);
	}
}
signed main()
{
	int T;
	read(T);
	for(re int i=1; i<=T; ++i)
	{
		printf("Case #%d:\n",i);
		work();
	}
	return 0;
}
