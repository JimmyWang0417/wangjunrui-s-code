#include<cstdio>
#define re register


namespace IO
{
	const int SIZE=20*1e5;
	char ibuf[SIZE],*iS,*iT;
#define gc() (char)(iS==iT?(iT=(iS=ibuf)+fread(ibuf,1,SIZE,stdin),iS==iT?EOF:*iS++):*iS++)
	template<typename T>
	inline void read(T & x)
	{
		x=0;
		bool b=false;
		char ch=gc();
		while((ch<'0'||ch>'9')&&ch^'-')
			ch=gc();
		if(ch=='-')
		{
			b=true;
			ch=gc();
		}
		while(ch>='0'&&ch<='9')
		{
			x=(x<<1)+(x<<3)+(ch^'0');
			ch=gc();
		}
		if(b)
			x=~x+1;
		return;
	}
#undef gc
	char Out[(int)1e5*20],*fe=Out,ch[25];
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
using namespace std;
const int N=5e5+5;
struct Tree
{
	int l,r;
	int sum;
} tree[N*40];
#define lc(rt) tree[rt].l
#define rc(rt) tree[rt].r
int cnt,root[N];
inline void modify(int &rt,int l,int r,int pos,int val)
{
	if(!rt)
		rt=++cnt;
	tree[rt].sum+=val;
	if(l==r)
		return;
	int mid=(l+r)>>1;
	if(pos<=mid)
		modify(lc(rt),l,mid,pos,val);
	else
		modify(rc(rt),mid+1,r,pos,val);
}
inline int query(int rt,int l,int r,int x,int y)
{
	if(!rt||r<x||l>y)
		return 0;
	if(x<=l&&r<=y)
		return tree[rt].sum;
	int mid=(l+r)>>1;
	return query(lc(rt),l,mid,x,y)+query(rc(rt),mid+1,r,x,y);
}
#define lowbit(x) (x&(-x))
int n,m,a[N];
inline void update(int rt,int pos,int val)
{
	for(re int i=rt; i<=n; i+=lowbit(i))
		modify(root[i],1,n,pos,val);
}
inline int query(int rootl,int rootr,int x,int y)
{
	int res=0;
	for(re int i=rootr; i; i-=lowbit(i))
		res+=query(root[i],1,n,x,y);
	for(re int i=rootl-1; i; i-=lowbit(i))
		res-=query(root[i],1,n,x,y);
	return res;
}
int c[N];
inline void update(int pos,int val)
{
	for(re int i=pos; i<=n; i+=lowbit(i))
		c[i]+=val;
}
inline int Query(int pos)
{
	int res=0;
	for(re int i=pos; i; i-=lowbit(i))
		res+=c[i];
	return res;
}
long long ans;
int pos[N];
using namespace IO;
int main()
{
	read(n),read(m);
	for(re int i=1; i<=n; ++i)
	{
		read(a[i]);
		pos[a[i]]=i;
		ans+=Query(n)-Query(a[i]);
		update(a[i],1);
		update(i,a[i],1);
	}
	while(m--)
	{
		write(ans);
		int x;
		read(x);
		ans-=query(1,pos[x]-1,x+1,n)+query(pos[x]+1,n,1,x-1);
		update(pos[x],x,-1);
	}
	flush();
	return 0;
}
