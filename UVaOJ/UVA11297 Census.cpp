#include <vector>
#include <cstdio>
#define lowbit(x) (x&(-x))
#define re register
#define ll long long
#define ull unsigned long long
#define rep(i,a,b) for(re int i=a;i<=b;++i)
#define per(i,a,b) for(re int i=a;i>=b;--i)
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
template<typename T,typename ...T1>
inline void read(T&x,T1&...x1)
{
	read(x);
	read(x1...);
}
const int N=505,INF=0x3f3f3f3f;
int n,a[N][N];
#define lc(x) (x<<1)
#define rc(x) (x<<1|1)

struct Tree
{
	int maxx[N<<2][N<<2],minn[N<<2][N<<2];
	inline void pushup(int rtx,int rt)
	{
		maxx[rtx][rt]=max(maxx[rtx][lc(rt)],maxx[rtx][rc(rt)]);
		minn[rtx][rt]=min(minn[rtx][lc(rt)],minn[rtx][rc(rt)]);
	}
	inline void build(int rtx,int posx,int rt,int l,int r)
	{
		if(l==r)
		{
			if(posx!=-1)
				minn[rtx][rt]=maxx[rtx][rt]=a[posx][l];
			else
			{
				maxx[rtx][rt]=max(maxx[lc(rtx)][rt],maxx[rc(rtx)][rt]);
				minn[rtx][rt]=min(minn[lc(rtx)][rt],minn[rc(rtx)][rt]);
			}
			return;
		}
		int mid=(l+r)>>1;
		build(rtx,posx,lc(rt),l,mid);
		build(rtx,posx,rc(rt),mid+1,r);
		pushup(rtx,rt);
	}
	inline void build(int rt,int l,int r)
	{
		if(l==r)
		{
			build(rt,l,1,1,n);
			return;
		}
		int mid=(l+r)>>1;
		build(lc(rt),l,mid);
		build(rc(rt),mid+1,r);
		build(rt,-1,1,1,n);
	}
	inline void update(int rtx,int posx,int rt,int l,int r,int pos,int val)
	{
		if(l==r)
		{
			if(posx!=-1)
				minn[rtx][rt]=maxx[rtx][rt]=val;
			else
			{
				maxx[rtx][rt]=max(maxx[lc(rtx)][rt],maxx[rc(rtx)][rt]);
				minn[rtx][rt]=min(minn[lc(rtx)][rt],minn[rc(rtx)][rt]);
			}
			return;
		}
		int mid=(l+r)>>1;
		if(pos<=mid)
			update(rtx,posx,lc(rt),l,mid,pos,val);
		else
			update(rtx,posx,rc(rt),mid+1,r,pos,val);
		pushup(rtx,rt);
	}
	inline void update(int rt,int l,int r,pair<int,int> pos,int val)
	{
		if(l==r)
		{
			update(rt,pos.first,1,1,n,pos.second,val);
			return;
		}
		int mid=(l+r)>>1;
		if(pos.first<=mid)
			update(lc(rt),l,mid,pos,val);
		else
			update(rc(rt),mid+1,r,pos,val);
		update(rt,-1,1,1,n,pos.second,val);
	}
	inline int querymax(int rtx,int rt,int l,int r,pair<int,int>pos)
	{
		if(r<pos.first||l>pos.second)
			return -INF;
		if(pos.first<=l&&r<=pos.second)
			return maxx[rtx][rt];
		int mid=(l+r)>>1;
		return max(querymax(rtx,lc(rt),l,mid,pos),querymax(rtx,rc(rt),mid+1,r,pos));
	}
	inline int querymax(int rt,int l,int r,pair<int,int>posx,pair<int,int>posy)
	{
		if(r<posx.first||l>posx.second)
			return -INF;
		if(posx.first<=l&&r<=posx.second)
			return querymax(rt,1,1,n,posy);
		int mid=(l+r)>>1;
		return max(querymax(lc(rt),l,mid,posx,posy),querymax(rc(rt),mid+1,r,posx,posy));
	}
	inline int querymin(int rtx,int rt,int l,int r,pair<int,int>pos)
	{
		if(r<pos.first||l>pos.second)
			return INF;
		if(pos.first<=l&&r<=pos.second)
			return minn[rtx][rt];
		int mid=(l+r)>>1;
		return min(querymin(rtx,lc(rt),l,mid,pos),querymin(rtx,rc(rt),mid+1,r,pos));
	}
	inline int querymin(int rt,int l,int r,pair<int,int>posx,pair<int,int>posy)
	{
		if(r<posx.first||l>posx.second)
			return INF;
		if(posx.first<=l&&r<=posx.second)
			return querymin(rt,1,1,n,posy);
		int mid=(l+r)>>1;
		return min(querymin(lc(rt),l,mid,posx,posy),querymin(rc(rt),mid+1,r,posx,posy));
	}
} tree;
signed main()
{
	read(n);
	for(re int i=1; i<=n; ++i)
		for(re int j=1; j<=n; ++j)
			read(a[i][j]);
	tree.build(1,1,n);
	int q;
	read(q);
	while(q--)
	{
		char opt[2];
		scanf("%s",opt);
		if(opt[0]=='q')
		{
			int x1,y1,x2,y2;
			read(x1,y1,x2,y2);
			printf("%d %d\n",tree.querymax(1,1,n,make_pair(x1,x2),make_pair(y1,y2)),tree.querymin(1,1,n,make_pair(x1,x2),make_pair(y1,y2)));
		}
		else if(opt[0]=='c')
		{
			int x,y,c;
			read(x,y,c);
			tree.update(1,1,n,make_pair(x,y),c);
		}
	}
	return 0;
}


