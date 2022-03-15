#include <cstdio>
#include <cctype> 
#include <algorithm>
#define re register
using namespace std;
const int N=1e6+5;
namespace IO
{
	const int SIZE=N*10+N*20;
	char ibuf[SIZE],*iS,*iT;
#define gc() (char)(iS==iT?(iT=(iS=ibuf)+fread(ibuf,1,SIZE,stdin),iS==iT?EOF:*iS++):*iS++)
	template<typename T>
	inline void read(T & x)
	{
		x=0;
		bool b=false;
		char ch=gc();
		while(!isdigit(ch)&&ch^'-')
			ch=gc();
		if(ch=='-')
		{
			b=true;
			ch=gc();
		}
		while(isdigit(ch))
		{
			x=(x<<1)+(x<<3)+(ch^'0');
			ch=gc();
		}
		if(b)
			x=~x+1;
		return;
	}
#undef gc
	char Out[N*10],*fe=Out,ch[25];
	int num=0;
	template<typename T>
	inline void write(T x)
	{
		if(!x)
			*fe++='0';
		if(x<0)
		{
			*fe++='-';
			x=-x;
		}
		while(x)
		{
			ch[++num]=(char)(x%10+'0');
			x/=10;
		}
		while(num)
			*fe++=ch[num--];
		*fe++='\n';
	}
	inline void flush()
	{
		fwrite(Out,1,fe-Out,stdout);
		fe=Out;
	}
}
using namespace IO;
struct Question
{
	int l,r,id;
	inline bool operator < (const Question&rhs)const
	{
		return r<rhs.r;
	}
} q[N];
int n,m;
int pos[N],pre[N],a[N];
struct Tree
{
	int lazy,max;
} tree[N<<2];
#define lc (rt<<1)
#define rc (rt<<1|1)
inline void pushdown(int rt)
{
	if(!tree[rt].lazy)
		return;
	tree[lc].max+=tree[rt].lazy;
	tree[rc].max+=tree[rt].lazy;
	tree[lc].lazy+=tree[rt].lazy;
	tree[rc].lazy+=tree[rt].lazy;
	tree[rt].lazy=0;
}
inline void change(int rt,int l,int r,int x,int y,int val)
{
	if(r<x||l>y)
		return;
	if(x<=l&&r<=y)
	{
		tree[rt].lazy+=val;
		tree[rt].max+=val;
		return;
	}
	pushdown(rt);
	int mid=(l+r)>>1;
	change(lc,l,mid,x,y,val);
	change(rc,mid+1,r,x,y,val);
	tree[rt].max=max(tree[lc].max,tree[rc].max);
}
inline int query(int rt,int l,int r,int x,int y)
{
	if(r<x||l>y)
		return -0x7fffffff;
	if(x<=l&&r<=y)
		return tree[rt].max;
	pushdown(rt);
	int mid=(l+r)>>1;
	return max(query(lc,l,mid,x,y),query(rc,mid+1,r,x,y));
}
int ans[N];
int main()
{
	read(n);
	for(re int i=1; i<=n; ++i)
	{
		read(a[i]);
		pre[i]=pos[a[i]];
		pos[a[i]]=i;
	}
	read(m);
	for(re int i=1; i<=m; ++i)
	{
		read(q[i].l),read(q[i].r);
		q[i].id=i;
	}
	stable_sort(q+1,q+1+m);
	for(re int i=1,j=1; i<=n; ++i)
	{
		change(1,1,n,pre[i]+1,i,1);
		while(q[j].r<=i&&j<=m)
		{
			ans[q[j].id]=query(1,1,n,q[j].l,q[j].r);
			++j;
		}
	}
	for(re int i=1; i<=m; ++i)
		write(ans[i]);
	flush();
	return 0;
}
