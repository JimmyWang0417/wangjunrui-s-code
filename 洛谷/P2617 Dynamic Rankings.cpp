#include <cstdio>
#define re register
#define lowbit(x) (x&(-x))
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
const int N=1e5+5,MLOGN=40000005;
int root[N];
struct Tree
{
	int l,r;
	int size;
} tree[MLOGN];
#define lc(x) tree[x].l
#define rc(x) tree[x].r
int cnt;
int n,m,a[N];
int rtadd[N],rtdec[N],totadd,totdec;
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
inline void update(int pos,int val)
{
	for(re int i=pos; i<=n; i+=lowbit(i))
		update(root[i],0,1e9,a[pos],val);
}
inline int getcnt()
{
	int ans=0;
	for(re int i=1; i<=totadd; ++i)
		ans+=tree[lc(rtadd[i])].size;
	for(re int i=1; i<=totdec; ++i)
		ans-=tree[lc(rtdec[i])].size;
	return ans;
}
inline void rtleft()
{
	for(re int i=1; i<=totadd; ++i)
		rtadd[i]=lc(rtadd[i]);
	for(re int i=1; i<=totdec; ++i)
		rtdec[i]=lc(rtdec[i]);
}
inline void rtright()
{
	for(re int i=1; i<=totadd; ++i)
		rtadd[i]=rc(rtadd[i]);
	for(re int i=1; i<=totdec; ++i)
		rtdec[i]=rc(rtdec[i]);
}
inline int query(int l,int r,int x,int y,int rk)
{
	if(l==r)
		return l;
	int mid=(l+r)>>1,sum=getcnt();
	if(rk<=sum)
	{
		rtleft();
		return query(l,mid,x,y,rk);
	}
	else
	{
		rtright();
		return query(mid+1,r,x,y,rk-sum);
	}
}
inline int query(int l,int r,int rk)
{
	totadd=totdec=0;
	for(re int i=r; i; i-=lowbit(i))
		rtadd[++totadd]=root[i];
	for(re int i=l-1; i; i-=lowbit(i))
		rtdec[++totdec]=root[i];
	return query(0,1e9,l,r,rk);
}
signed main()
{
//	freopen("ans.in","r",stdin);
//	freopen("ans.out","w",stdout);
	read(n),read(m);
	for(re int i=1; i<=n; ++i)
	{
		read(a[i]);
		update(i,1);
	}
	while(m--)
	{
		char opt[5];
		scanf("%s",opt);
		if(opt[0]=='Q')
		{
			int l,r,rk;
			read(l),read(r),read(rk);
			printf("%d\n",query(l,r,rk));
		}
		else if(opt[0]=='C')
		{
			int pos,val;
			read(pos),read(val);
			update(pos,-1);
			a[pos]=val;
			update(pos,1);
		}
	}
//	printf("%d\n",cnt);
	return 0;
}

