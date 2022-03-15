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
const int N=15,CNT=376+5,mod=1e8;
int n,m,tot,status[CNT],dp[N][CNT],a[N];
char str[N];
int main()
{
	read(n),read(m);
	for(re int S=1; S<(1<<m); ++S)
		if((S&(S<<1))==0)
			status[++tot]=S;
//	for(re int i=0; i<=tot; ++i)
//		printf("%d ",i);
	a[0]=(1<<m)-1;
	for(re int i=1; i<=n; ++i)
	{
		for(re int j=0; j<m; ++j)
		{
			static int x;
			read(x);
			a[i]|=x<<j;
		}
	}
	for(re int i=0; i<=tot; ++i)
		dp[1][i]=1;
	for(re int pos=2; pos<=n; ++pos)
		for(re int i=0; i<=tot; ++i)
			if((a[pos-1]&status[i])==status[i])
				for(re int j=0; j<=tot; ++j)
					if((a[pos]&status[j])==status[j]&&(status[i]&status[j])==0)
						(dp[pos][j]+=dp[pos-1][i])%=mod;
	int ans=0;
	for(re int i=0; i<=tot; ++i)
		if((status[i]&a[n])==status[i])
			(ans+=dp[n][i])%=mod;
	printf("%d\n",ans);
	return 0;
}
