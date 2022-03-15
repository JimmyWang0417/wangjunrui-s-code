#include<cstdio>
#define re register
#define max(x,y) (x>y?x:y)
using namespace std;
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
int dp[10000],n,t,x,kase,T;
int main()
{
	read(T);
	while(T--)
	{
		read(n);
		read(t);
		for(re int i=0; i<=t; i++)
			dp[i]=-1;
		dp[0]=0;
		for(re int i=1; i<=n; i++)
		{
			read(x);
			for(re int j=t-1; j>=x; j--)
				dp[j]=max(dp[j-x]+1,dp[j]);
		}
		int ans=t-1;
		for(re int i=t-2; i>=0; i--)
			if(dp[ans]<dp[i])
				ans=i;
		printf("Case %d: %d %d\n",++kase,dp[ans]+1,ans+678);
	}
	return 0;
}
