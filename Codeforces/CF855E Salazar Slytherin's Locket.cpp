#include <cstdio>
#include <cstring>
#define re register
#define ll long long
#define rep(i,a,b) for(re int i=a;i<=b;++i)
#define per(i,a,b) for(re int i=a;i>=b;--i)
using namespace std;
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
const int N=75,M=(1<<11)+5;
int b;
ll dp[15][N][M];
int digit[N],len;
inline ll DP(int pos,int status,bool limit,bool lead)
{
	if(pos==0)
		return status==0;
	if(!limit&&!lead&&dp[b][pos][status]!=-1)
		return dp[b][pos][status];
	int MAX=limit?digit[pos]:b-1;
	ll ans=0;
	for(re int i=0; i<=MAX; ++i)
	{
		if(lead&&i==0)
			ans+=DP(pos-1,status,limit&&i==MAX,lead&&i==0);
		else
			ans+=DP(pos-1,status^(1<<i),limit&&i==MAX,lead&&i==0);
	}
	if(!limit&&!lead)
		dp[b][pos][status]=ans;
	return ans;
}
inline ll solve(ll val)
{
	len=0;
	while(val)
	{
		digit[++len]=val%b;
		val/=b;
	}
	return DP(len,0,true,true);
}
signed main()
{
	int T;
	ll l,r;
	memset(dp,-1,sizeof(dp));
	read(T);
	while(T--)
	{
		read(b,l,r);
		printf("%lld\n",solve(r)-solve(l-1));
	}
	return 0;
}

