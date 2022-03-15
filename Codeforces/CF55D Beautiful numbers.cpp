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
const int mod=2520;
inline int gcd(int a,int b)
{
	return b==0?a:gcd(b,a%b);
}
inline int lcm(int a,int b)
{
	return a/gcd(a,b)*b;
}
int mp[mod+5],color;
inline void init()
{
	for(int i=1; i<=mod; ++i)
	{
		if(mod%i==0)
			mp[i]=++color;
	}
}
ll dp[25][mod+1][50];
int dight[25],tot;
inline ll dfs(int pos,int val,int now,bool limit)
{
	if(pos==0)
		return val%now==0;
	if(!limit&&dp[pos][val][mp[now]]!=-1)
		return dp[pos][val][mp[now]];
	int maxx=limit?dight[pos]:9;
	ll ans=0;
	for(int i=0; i<=maxx; ++i)
	{
		if(i)
			ans+=dfs(pos-1,(val*10+i)%mod,lcm(now,i),limit&&i==maxx);
		else
			ans+=dfs(pos-1,val*10%mod,now,limit&&i==maxx);
	}
	if(!limit)
		dp[pos][val][mp[now]]=ans;
	return ans;
}
inline ll calc(ll val)
{
	tot=0;
	while(val)
	{
		dight[++tot]=val%10;
		val/=10;
	}
//	for(int i=1; i<=tot; ++i)
//		printf("%d ",dight[i]);
//	putchar('\n');
	return dfs(tot,0,1,true);
}
signed main()
{
	memset(dp,-1,sizeof(dp));
	init();
	int T;
	read(T);
	while(T--)
	{
		ll l,r;
		read(l,r);
		printf("%lld\n",calc(r)-calc(l-1));
	}
	return 0;
}


