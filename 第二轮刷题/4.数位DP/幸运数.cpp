#include<cstdio>
#include<cstring>
#define re register
#define ll unsigned long long
#define LL long long
using namespace std;
const int N=25;
LL dp[N][15];
int digit[N],mid;
inline ll dfs(int pos,bool exist,bool limit)
{
	if(pos==0)
		return 1;
	if(!limit&&dp[pos][exist]!=-1)
		return dp[pos][exist];
	int maxx=limit?digit[pos]:9;
	ll res=0ll;
	for(re int i=0; i<=maxx; ++i)
	{
		if(pos==mid&&i!=4||pos==mid-1&&i!=9||pos>=mid&&exist&&i==9)
			continue;
		res+=dfs(pos-1,i==4,limit&&i==maxx);
	}
	if(!limit)
		dp[pos][exist]=res;
	return res;
}
char str[N];
int main()
{
	scanf("%s",str);
	int len=strlen(str);
	for(re int i=0; i<len; ++i)
		digit[len-i]=str[i]-'0';
	ll ans=0;
	for(re int i=2; i<=len; ++i)
	{
		memset(dp,-1,sizeof(dp));
		mid=i;
		ans+=dfs(len,0,true);
	}
	printf("%llu\n",ans);
	return 0;
}
