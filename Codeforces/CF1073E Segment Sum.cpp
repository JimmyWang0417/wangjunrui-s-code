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
#define node pair<ll,int>
const int N=(1<<10)+5;
const int mod=998244353;
ll l,r;
int m;
inline int calc(int x)
{
	int res=0;
	for(int i=0; i<=9; ++i)
		if((x>>i)&1)
			++res;
	return res;
}
node dp[25][N];
bool vis[25][N];
int dight[N],tot;
ll power[N];
inline node dfs(int pos,int S,bool zero,bool limit)
{
	if(pos==0)
		return make_pair(0,1);
	if(!zero&&!limit&&vis[pos][S])
		return dp[pos][S];
	ll ans=0;
	int res=0;
	int maxx=limit?dight[pos]:9;
	for(int i=0; i<=maxx; ++i)
	{
		int nxtS=(zero&&i==0)?S:S|(1<<i);
		if(calc(nxtS)<=m)
		{
			node x=dfs(pos-1,nxtS,zero&&i==0,limit&&i==maxx);
			(ans+=(x.first+power[pos-1]*x.second%mod*i%mod)%mod)%=mod;
			(res+=x.second)%=mod;
		}
	}
	if(!zero&&!limit)
	{
		dp[pos][S]=make_pair(ans,res);
		vis[pos][S]=true;
	}
	return make_pair(ans,res);
}
inline ll calc(ll x)
{
	tot=0;
	while(x)
	{
		dight[++tot]=(int)(x%10);
		x/=10;
	}
	return dfs(tot,0,true,true).first;
}
signed main()
{
	power[0]=1;
	for(int i=1; i<=18; ++i)
		power[i]=power[i-1]*10%mod;
	read(l,r,m);
	printf("%lld\n",(calc(r)-calc(l-1)+mod)%mod);
	return 0;
}


