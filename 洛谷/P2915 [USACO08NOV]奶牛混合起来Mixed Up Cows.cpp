#include <cstdio>
#include <cmath>
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
const int N=16;
int n,m,a[N+5];
long long dp[N+15][(1<<N)+5];
inline int Count(int status)
{
	int ans=0;
	for(re int i=0; i<n; ++i)
		ans+=(bool)(status&(1<<i));
	return ans;
}
int main()
{
	read(n),read(m);
	for(re int i=0; i<n; ++i)
		read(a[i]);
	for(re int i=0; i<n; ++i)
		dp[i][1<<i]=1;
	for(re int status=1; status<(1<<n); ++status)
		for(re int j=0; j<n; ++j)
		{
			if(dp[j][status])
				continue;
			if((~status)&(1<<j))
				continue;
			int nxt=status^(1<<j);
			for(re int i=0; i<n; ++i)
			{
				if(i==j)
					continue;
				if(abs(a[i]-a[j])>m)
					dp[j][status]+=dp[i][nxt];
			}
		}
	long long ans=0;
	for(re int i=0; i<n; ++i)
		ans+=dp[i][(1<<n)-1];
	printf("%lld\n",ans);
	return 0;
}
