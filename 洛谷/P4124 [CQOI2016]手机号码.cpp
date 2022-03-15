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
const int N=15;
int a[N];
ll dp[N][N][N][2][2][2];
inline ll dfs(int pos,int bebefore,int before,bool flag,bool _4,bool _8,bool limit)
{
	if(_4&&_8)
		return 0;
	if(pos==0)
		return flag;
	if(!limit&&dp[pos][bebefore][before][flag][_4][_8]!=-1)
		return dp[pos][bebefore][before][flag][_4][_8];
	int maxx=(limit?a[pos]:9);
	ll res=0;
	for(int i=0; i<=maxx; ++i)
		res+=dfs(pos-1,before,i,(bebefore==before&&before==i)||flag,_4||i==4,_8||i==8,limit&&i==maxx);
	if(!limit)
		dp[pos][bebefore][before][flag][_4][_8]=res;
	return res;
}
inline ll solve(ll n)
{
	int tot=0;
	ll val=n;
	memset(a,0,sizeof(a));
	while(val)
	{
		a[++tot]=val%10;
		val/=10;
	}
//	printf("%d\n",tot);
	ll res=0;
	for(int i=1; i<=a[11]; ++i)
	{
		memset(dp,-1,sizeof(dp));
		res+=dfs(10,0,i,false,i==4,i==8,i==a[11]);
	}
	return res;
}
signed main()
{
	ll l,r;
	read(l,r);
	printf("%lld\n",solve(r)-solve(l-1));
	return 0;
}


