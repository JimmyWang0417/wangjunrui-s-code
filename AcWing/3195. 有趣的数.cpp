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
const int N=1005;
const int mod=1e9+7;
int dp[N][2][2][2][2];
inline int dfs(int pos,int _0,int _1,int _2,int _3)
{
	if(pos==0)
		return _0&&_1&&_2&&_3;
	if(dp[pos][_0][_1][_2][_3]!=-1)
		return dp[pos][_0][_1][_2][_3];
	int &ans=dp[pos][_0][_1][_2][_3]=0;
	if((_2||_3)&&!_1)
		(ans+=dfs(pos-1,true,_1,_2,_3))%=mod;
	if(_0)
		(ans+=dfs(pos-1,_0,true,_2,_3))%=mod;
	if(!_3)
		(ans+=dfs(pos-1,_0,_1,true,_3))%=mod;
	if(_2)
		(ans+=dfs(pos-1,_0,_1,_2,true))%=mod;
//	printf("%d %d %d %d %d = %d\n",pos,_0,_1,_2,_3,ans);
	return ans;
}
int n;
signed main()
{
	read(n);
	memset(dp,-1,sizeof(dp));
	printf("%d\n",dfs(n,false,false,false,false));
	return 0;
}


