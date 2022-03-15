#include <cstdio>
#include <cstring>
#include <algorithm>
#define re register
#define ll long long
#define mod 1000000003
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
ll dp[55][35][2],power[35];
unsigned int a[55];
int n,k;
inline ll dfs(int pos,int val,int len)
{
	val&=(~((1<<len)-1));
	if(pos==n+1)
		return !val;
	bool flag=(val>>len)&1;
	ll &ans=dp[pos][len][flag];
	if(ans!=-1)
		return ans;
	ans=0ll;
	int res=0;
	for(re int i=31; i>=0; --i)
		if((a[pos]>>i)&1)
		{
			(ans+=dfs(pos+1,val^res,max(len,i))*power[min(len,i)]%mod)%=mod;
			res|=(1<<i);
//			printf("%d ",res);
		}
//	printf("dp[%d][%d][%d][%d]=%lld\n",pos,val,len,ans);
//	putchar('\n');
	return ans;
}
inline void work()
{
	for(re int i=1; i<=n; ++i)
	{
		read(a[i]);
		++a[i];
	}
	memset(dp,-1,sizeof(dp));
	printf("%lld\n",dfs(1,k,0));
}
int main()
{
	power[0]=1;
	for(re int i=1; i<=31; ++i)
		power[i]=(power[i-1]<<1)%mod;
//	for(re int i=0; i^31; ++i)
//		printf("%lld\n",power[i]);
	while(read(n),read(k),n||k)
		work();
}
