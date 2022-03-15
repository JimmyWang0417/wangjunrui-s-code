#include<cstdio>
#define re register
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
const int N=4200+5;
int n,p,ans,dp[2][N];
int main()
{
	read(n),read(p);
	dp[0][2]=1;
	for(re int i=3; i<=n; ++i)
		for(re int j=2; j<=i; ++j)
			dp[i&1][j]=(dp[i&1][j-1]+dp[(i-1)&1][i-j+1])%p;
	for(re int i=2; i<=n; ++i)
		(ans+=dp[n&1][i])%=p;
	printf("%d\n",(ans<<1)%p);
	return 0;
}
