#include<cstdio>
#include<vector>
#include<cstring>
#define re register
int dp[12][12],a,b;
using namespace std;
vector<int>digit;
inline int dfs(int pos,int statu,int done)
{
	if(pos==-1)
		return 1;
	if((!done)&&(~dp[pos][statu]))
		return dp[pos][statu];
	int res=0,end=done?digit[pos]:9;
	for(re int i=statu; i<=end; i++)
		res+=dfs(pos-1,i,done&&i==end);
	if(!done)
		dp[pos][statu]=res;
	return res;
}
inline int solve(int num)
{
	memset(dp,-1,sizeof(dp));
	digit.clear();
	while(num>0)
	{
		digit.push_back(num%10);
		num/=10;
	}
	return dfs(digit.size()-1,0,1);
}
int main()
{
	while(scanf("%d%d",&a,&b)==2)
		printf("%d\n",solve(b)-solve(a-1));
	return 0;
}

