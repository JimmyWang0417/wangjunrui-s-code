#include<cstdio>
#include<cstring>
#define re register
#define ll long long
using namespace std;
int digit[15],findnum;
ll dp[15][15];
inline ll dfs(int pos,int cnt,bool lead,bool limit)
{
	if(pos==0)
		return (ll)cnt;
	if(!lead&&!limit&&dp[pos][cnt]!=-1)
		return dp[pos][cnt];
	int maxx=limit?digit[pos]:9;
	ll res=0;
	for(re int i=0; i<=maxx; ++i)
	{
		if(i==findnum&&(!lead||i))
			res+=dfs(pos-1,cnt+1,lead&&i==0,limit&&i==maxx);
		else
			res+=dfs(pos-1,cnt,lead&&i==0,limit&&i==maxx);
	}
	if(!lead&&!limit)
		dp[pos][cnt]=res;
	return res;
}
inline ll solve(ll val,int num)
{
	int len=0;
	while(val)
	{
		digit[++len]=(int)(val%10);
		val/=10;
	}
	findnum=num;
	memset(dp,-1,sizeof dp);
	return dfs(len,0,true,true);
}
int main()
{
	ll a,b;
	scanf("%lld%lld",&a,&b);
	for(re int i=0; i<=9; ++i)
		printf("%lld ",solve(b,i)-solve(a-1,i));
	putchar('\n');
	return 0;
}
