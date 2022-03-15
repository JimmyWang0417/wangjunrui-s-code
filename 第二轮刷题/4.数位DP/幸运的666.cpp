#pragma GCC optimize(3)
#pragma GCC optimize("Ofast")
#pragma GCC optimize("inline")
#pragma GCC optimize("-fgcse")
#pragma GCC optimize("-fgcse-lm")
#pragma GCC optimize("-fipa-sra")
#pragma GCC optimize("-ftree-pre")
#pragma GCC optimize("-ftree-vrp")
#pragma GCC optimize("-fpeephole2")
#pragma GCC optimize("-ffast-math")
#pragma GCC optimize("-fsched-spec")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("-falign-jumps")
#pragma GCC optimize("-falign-loops")
#pragma GCC optimize("-falign-labels")
#pragma GCC optimize("-fdevirtualize")
#pragma GCC optimize("-fcaller-saves")
#pragma GCC optimize("-fcrossjumping")
#pragma GCC optimize("-fthread-jumps")
#pragma GCC optimize("-funroll-loops")
#pragma GCC optimize("-fwhole-program")
#pragma GCC optimize("-freorder-blocks")
#pragma GCC optimize("-fschedule-insns")
#pragma GCC optimize("inline-functions")
#pragma GCC optimize("-ftree-tail-merge")
#pragma GCC optimize("-fschedule-insns2")
#pragma GCC optimize("-fstrict-aliasing")
#pragma GCC optimize("-fstrict-overflow")
#pragma GCC optimize("-falign-functions")
#pragma GCC optimize("-fcse-skip-blocks")
#pragma GCC optimize("-fcse-follow-jumps")
#pragma GCC optimize("-fsched-interblock")
#pragma GCC optimize("-fpartial-inlining")
#pragma GCC optimize("no-stack-protector")
#pragma GCC optimize("-freorder-functions")
#pragma GCC optimize("-findirect-inlining")
#pragma GCC optimize("-fhoist-adjacent-loads")
#pragma GCC optimize("-frerun-cse-after-loop")
#pragma GCC optimize("inline-small-functions")
#pragma GCC optimize("-finline-small-functions")
#pragma GCC optimize("-ftree-switch-conversion")
#pragma GCC optimize("-foptimize-sibling-calls")
#pragma GCC optimize("-fexpensive-optimizations")
#pragma GCC optimize("-funsafe-loop-optimizations")
#pragma GCC optimize("inline-functions-called-once")
#pragma GCC optimize("-fdelete-null-pointer-checks")
#include <cstdio>
#include <cstring>
#define ll long long
#define re register
template<typename T>
inline void read(T&x)
{
	x=0;
	char s=getchar();
	bool f=false;
	while(!(s>='0'&&s<='9'))
	{
		if(s=='-')
			f=true;
		s=getchar();
	}
	while(s>='0'&&s<='9')
	{
		x=(x<<1)+(x<<3)+s-'0';
		s=getchar();
	}
	if(f)
		x=(~x)+1;
}
int digit[15];
ll dp[15][15][15];
inline ll dfs(int pos,int bebefore,int before,bool limit)
{
	if(pos==0)
		return 1;
	if(!limit&&dp[pos][bebefore][before]!=-1)
		return dp[pos][bebefore][before];
	int maxx=limit?digit[pos]:9;
	ll res=0;
	for(re int i=0; i<=maxx; ++i)
	{
		if(bebefore==6&&before==6&&i==6)
			continue;
		res+=dfs(pos-1,before,i,limit&&i==maxx);
	}
	if(!limit)
		dp[pos][bebefore][before]=res;
	return res;
}
inline ll solve(ll val)
{
	int len=0;
	ll n=val;
	while(val)
	{
		digit[++len]=val%10;
		val/=10;
	}
	memset(dp,-1,sizeof(dp));
	return n-dfs(len,0,0,true)+1;
}
inline void work()
{
	int n;
	read(n);
	ll l=666,r=6668056399,ans=0;
//	solve(1);
//	solve(66650000000+10) ;
	while(l<=r)
	{
		ll mid=(l+r)>>1;
		if(solve(mid)>=n)
		{
			ans=mid;
			r=mid-1;
		}
		else l=mid+1;
	}
//	solve(666);
	printf("%lld\n",ans);
}
int main()
{
	int T;
//	printf("%d\n",solve(666));
	read(T);
	while(T--)
		work();
}
