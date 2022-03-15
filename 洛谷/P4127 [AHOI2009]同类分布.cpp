#include <cstdio>
#include <cstring>
#define re register
#define ll long long
using namespace std;
const int N=20,M=N*9;
int need,digit[N];
ll dp[N][M][M];
inline ll dfs(int pos,int cnt,int r,bool limit)
{
	if(pos==0&&cnt==0)
		return 0;
	if(pos==0)
		return (ll)(cnt==need&&r==0);
	if(!limit&&dp[pos][cnt][r]!=-1)
		return dp[pos][cnt][r];
	int maxx=limit?digit[pos]:9;
	ll res=0ll;
	for(re int i=0; i<=maxx; ++i)
	{
		if(cnt+i>need)
			break;
		res+=dfs(pos-1,cnt+i,(r*10+i)%need,limit&&i==maxx);
	}
	if(!limit)
		dp[pos][cnt][r]=res;
	return res;
}
inline ll solve(ll val)
{
	int len=0;
	while(val)
	{
		digit[++len]=(int)(val%10);
		val/=10;
	}
	ll ans=0ll;
//	for(re int i=len; i>=1; --i)
//		printf("%d",digit[i]);
	for(re int i=1; i<=len*9; ++i)
	{
		need=i;
		memset(dp,-1,sizeof(dp));
		ans+=dfs(len,0,0,true);
//		printf("%lld\n",ans);
	}
	return ans;
}
int main()
{
	ll a,b;
	scanf("%lld%lld",&a,&b);
	printf("%lld\n",solve(b)-solve(a-1));
	return 0;
}
