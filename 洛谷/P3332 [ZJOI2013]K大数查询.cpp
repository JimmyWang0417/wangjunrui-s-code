#include <cstdio>
#define re register
#define ll long long
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
const int N=5e4+5,M=30;
struct Tree
{
	int l,r;
	int size1;
	ll size2;
} tree[N*550];
int cnt;
#define lc(rt) tree[rt].l
#define rc(rt) tree[rt].r
int root[N];
int a[N],n,m;
inline void update(int &rt,int l,int r,int pos,int val1,ll val2)
{
	if(!rt)
		rt=++cnt;
	tree[rt].size1+=val1;
	tree[rt].size2+=val2;
	if(l==r)
		return;
	int mid=(l+r)>>1;
	if(pos<=mid)
		update(lc(rt),l,mid,pos,val1,val2);
	else
		update(rc(rt),mid+1,r,pos,val1,val2);
}
inline void update(int pos,int val,int v)
{
	for(re int i=pos; i<=n; i+=lowbit(i))
		update(root[i],-n,n,val,v,1ll*pos*v);
}
int rtadd[M],rtdec[M],totadd,totdec;
inline ll getcnt(int l,int r)
{
	ll ans1=0,ans2=0;
	for(re int i=1; i<=totadd; ++i)
		ans1+=1ll*tree[rc(rtadd[i])].size1*(r+1)-tree[rc(rtadd[i])].size2;
	for(re int i=1; i<=totdec; ++i)
		ans2+=1ll*tree[rc(rtdec[i])].size1*(l+1)-tree[rc(rtdec[i])].size2;
	return ans1-ans2;
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
inline int query(int l,int r,int x,int y,ll rk)
{
	if(l==r)
		return l;
	int mid=(l+r)>>1;
	ll sum=getcnt(x,y);
//	printf("%d %d | %d %d | %lld %lld\n",l,mid,mid+1,r,sum,rk);
	if(rk<=sum)
	{
		rtright();
		return query(mid+1,r,x,y,rk);
	}
	else
	{
		rtleft();
		return query(l,mid,x,y,rk-sum);
	}
}
inline int query(int l,int r,ll rk)
{
	totadd=totdec=0;
	for(re int i=r; i; i-=lowbit(i))
		rtadd[++totadd]=root[i];
	for(re int i=l-1; i; i-=lowbit(i))
		rtdec[++totdec]=root[i];
	return query(-n,n,l-1,r,rk);
}
signed main()
{
	read(n),read(m);
	while(m--)
	{
		int opt,l,r;
		read(opt),read(l),read(r);
		if(opt==1)
		{
			int c;
			read(c);
			update(l,c,1);
			update(r+1,c,-1);
		}
		else if(opt==2)
		{
			ll rk;
			read(rk);
			printf("%d\n",query(l,r,rk));
		}
	}
	return 0;
}
