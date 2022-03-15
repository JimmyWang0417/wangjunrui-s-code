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
const int N=2e5+5;
int n,k,a[N];
int ans[N];
inline int calc_one(int x)
{
	return min(max(a[x-1],a[x+1]),a[x]);
}
inline void solve_one()
{
	int l=(n+1)>>1,r=l+((n&1)^1);
	int res=max(calc_one(l),calc_one(r));
	for(int i=(n&1)^1; i<n; i+=2)
	{
		ans[i]=res;
		--l,++r;
		res=max(res,max(calc_one(l),calc_one(r)));
	}
}
inline int calc_two(int x)
{
	return max(a[x],a[x+1]);
}
inline void solve_two()
{
	int l=n>>1,r=(n+1)>>1;
	int res=max(calc_two(l),calc_two(r));
	for(int i=n&1; i<n; i+=2)
	{
		ans[i]=res;
		--l,++r;
		res=max(res,max(calc_two(l),calc_two(r)));
	}
}
signed main()
{
	freopen("game.in","r",stdin);
	freopen("game.out","w",stdout);
	read(n,k);
	for(int i=1; i<=n; ++i)
		read(a[i]);
	solve_one();
	solve_two();
	ans[n-1]=ans[n-2];
	if(k==-1)
	{
		for(int i=0; i<n; ++i)
			printf("%d ",ans[i]);
		putchar('\n');
	}
	else
		printf("%d\n",ans[k]);
	return 0;
}


