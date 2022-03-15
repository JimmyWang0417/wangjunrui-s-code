#include <cstdio>
#include <cstring>
#define re register
#define max(x,y) ((x)>(y)?(x):(y))
#define ll long long
using namespace std;
const int mod=10000007;
ll dp[55][55];
int digit[55];
inline ll quickpow(ll a,ll b)
{
	ll res=1;
	while(b)
	{
		if(b&1)
			res=res*a%mod;
		a=a*a%mod;
		b>>=1;
	}
	return res;
}
int need;
inline ll dfs(int pos,int cnt,bool limit)
{
	if(pos==0)
		return cnt==need;
	if(!limit&&dp[pos][cnt]!=-1)
		return dp[pos][cnt];
	int maxx=limit?digit[pos]:1;
	ll res=0;
	for(re int i=0; i<=maxx; ++i)
		res+=dfs(pos-1,cnt+(i==1),limit&&i==maxx);
	if(!limit)
		dp[pos][cnt]=res;
	return res;
}
inline ll solve(ll val)
{
	int len=0;
	while(val)
	{
		digit[++len]=val&1;
		val>>=1;
	}
	ll ans=1ll;
	for(re int i=1; i<=50; ++i)
	{
		memset(dp,-1,sizeof(dp));
		need=i;
//		printf("%lld\n",tmp);
		ans=ans*quickpow(i,dfs(len,0,true))%mod;
//		printf("%lld\n",ans);
	}
	return ans;
}
int main()
{
	ll n;
	scanf("%lld",&n);
	printf("%lld\n",solve(n));
	return 0;
}
