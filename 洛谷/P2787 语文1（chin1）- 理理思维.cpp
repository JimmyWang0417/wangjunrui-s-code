#include <cstdio>
#include <cstring>
#define re register
using namespace std;
template <typename T>
inline void read(T &x)
{
	x=0;
	char s=(char)getchar();
	bool flag=false;
	while(s<'0'||s>'9')
	{
		if(s=='-')
			flag=true;
		s=(char)getchar();
	}
	while(s>='0'&&s<='9')
	{
		x=(x<<1)+(x<<3)+(s^'0');
		s=(char)getchar();
	}
	if(flag)
		x=~x+1;
	return;
}
#define calc(x) (x-'A')
inline char change(char x)
{
	if(x>='a'&&x<='z')
		return x-'a'+'A';
	return x;
}
const int N=5e4+5;
struct Tree
{
	int cnt[26],lazy,size;
	inline void clear()
	{
		memset(cnt,0,sizeof(cnt));
		lazy=-1;
	}
} tree[N<<2];
char str[N];
#define lc (rt<<1)
#define rc (rt<<1|1)
inline void update(int rt,int col)
{
	tree[rt].clear();
	tree[rt].cnt[col]=tree[rt].size;
	tree[rt].lazy=col;
	return;
}
inline void pushdown(int rt)
{
	if(tree[rt].lazy==-1)
		return;
	update(lc,tree[rt].lazy);
	update(rc,tree[rt].lazy);
	tree[rt].lazy=-1;
}
inline void pushup(int rt)
{
	for(re int i=0; i<26; ++i)
		tree[rt].cnt[i]=tree[lc].cnt[i]+tree[rc].cnt[i];
}
inline void build(int rt,int l,int r)
{
	tree[rt].clear();
	tree[rt].size=r-l+1;
	if(l==r)
	{
		tree[rt].cnt[calc(change(str[l]))]=1;
		return;
	}
	int mid=(l+r)>>1;
	build(lc,l,mid);
	build(rc,mid+1,r);
	pushup(rt);
}
inline void change(int rt,int l,int r,int x,int y,int col)
{
	if(r<x||l>y)
		return;
	if(x<=l&&r<=y)
	{
		update(rt,col);
		return;
	}
	int mid=(l+r)>>1;
	pushdown(rt);
	change(lc,l,mid,x,y,col);
	change(rc,mid+1,r,x,y,col);
	pushup(rt);
}
inline Tree query(int rt,int l,int r,int x,int y)
{
	if(x<=l&&r<=y)
		return tree[rt];
	int mid=(l+r)>>1;
	pushdown(rt);
	if(y<=mid)
		return query(lc,l,mid,x,y);
	if(mid<x)
		return query(rc,mid+1,r,x,y);
	Tree rhsa=query(lc,l,mid,x,y),rhsb=query(rc,mid+1,r,x,y),ans;
	for(re int i=0; i<26; ++i)
		ans.cnt[i]=rhsa.cnt[i]+rhsb.cnt[i];
	return ans;
}
int n,m;
char rhsk[5];
inline void solve()
{
	int x,y;
	read(x),read(y);
	Tree ans=query(1,1,n,x,y);
	for(re int i=0; i<26; ++i)
		if(ans.cnt[i])
		{
			change(1,1,n,x,x+ans.cnt[i]-1,i);
			x+=ans.cnt[i];
		}
}
int main()
{
	read(n),read(m);
	scanf("%s",str+1);
	build(1,1,n);
	while(m--)
	{
		int opt;
		read(opt);
		if(opt==1)
		{
			int x,y;
			read(x),read(y);
			scanf("%s",rhsk);
			printf("%d\n",query(1,1,n,x,y).cnt[calc(change(rhsk[0]))]);
		}
		else if(opt==2)
		{
			int x,y;
			read(x),read(y);
			scanf("%s",rhsk);
			change(1,1,n,x,y,calc(change(rhsk[0])));
		}
		else if(opt==3)
			solve();
	}
	return 0;
}
