#include <cstdio>
#include <cstring>
#define re register
#define ll long long
#define mod 252
using namespace std;
int k;
int digit[25];
ll dp[25][600][300];
inline ll dfs(int pos,int status,int r,bool limit)
{
	if(pos==0)
	{
		int cnt=0;
		for(re int i=1; i<=9; ++i)
			if((status&(1<<(i-1)))&&r%i==0)
				++cnt;
		return cnt>=k;
	}
	r%=252;
	if(!limit&&dp[pos][status][r]!=-1)
		return dp[pos][status][r];
	int maxx=limit?digit[pos]:9;
	ll res=0ll;
	for(re int i=0; i<=maxx; ++i)
		res+=dfs(pos-1,i?status|(1<<(i-1)):status,r*10+i,limit&&i==maxx);
	if(!limit)
		dp[pos][status][r]=res;
	return res;
}
inline ll solve(ll val)
{
	int len=0;
	while(val)
	{
		digit[++len]=val%10;
		val/=10;
	}
	memset(dp,-1,sizeof(dp));
	return dfs(len,0,0,true);
}
int main()
{
	ll L,R;
	scanf("%d%lld%lld",&k,&L,&R);
	printf("%lld\n",solve(R)-solve(L-1));
	return 0;
}
