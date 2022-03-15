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
const int N=1e6+5,mod=998244353;
int n,dp[N];
inline void work()
{
	int a,b;
	read(n,a,b);
	if(a>b)
		swap(a,b);
	int sum=b-a-1;
	if(a==1)
		++sum;
	if(b==n)
		++sum;
	printf("%d\n",dp[sum]);
}
signed main()
{
	freopen("achen.in","r",stdin);
	freopen("achen.out","w",stdout);
	dp[1]=1;
	dp[2]=1;
	dp[3]=1;

	for(int i=4; i<=1e6; ++i)
		dp[i]=(dp[i-1]+dp[i-3])%mod;

	int T;
	read(T);
	while(T--)
		work();

	return 0;
}

