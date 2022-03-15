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
inline void clear(T*array,int l,int r,int val)
{
	memset(&array[l],val,sizeof(T)*(r-l+1));
}
using namespace std;
const int N=1e5+5;
int n,k,A,B;
struct Tree
{
	int l,r;
	int sum;
} tree[N*50];
#define lc(rt) tree[rt].l
#define rc(rt) tree[rt].r
int root,cnt;
inline void update(int &rt,int l,int r,int pos,int val)
{
	if(!rt)
		rt=++cnt;
	tree[rt].sum+=val;
	if(l==r)
		return;
	int mid=(l+r)>>1;
	if(pos<=mid)
		update(lc(rt),l,mid,pos,val);
	else
		update(rc(rt),mid+1,r,pos,val);
}
inline ll solve(int rt,int l,int r)
{
	if(!tree[rt].sum)
		return A;
	if(l==r)
		return (ll)B*tree[rt].sum;
	int mid=(l+r)>>1;
	return min(solve(lc(rt),l,mid)+solve(rc(rt),mid+1,r),(ll)B*(r-l+1)*tree[rt].sum);
}
signed main()
{
	read(n,k,A,B);
	n=(1<<n);
	for(int i=1; i<=k; ++i)
	{
		int x;
		read(x);
		update(root,1,n,x,1);
	}
	printf("%lld\n",solve(root,1,n));
	return 0;
}


