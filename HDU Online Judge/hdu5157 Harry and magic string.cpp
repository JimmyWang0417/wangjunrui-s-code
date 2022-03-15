#include<cstdio>
#include<cstring>
#include<algorithm>
#define ll long long
#define re register
using namespace std;
const int N=2e5+5;
char str[N],s[N];
int n,len,p[N],dp1[N],dp2[N];
ll suf[N],pre[N],sum[N];
inline void solve()
{
	n=strlen(str);
	s[len=0]='$';
	s[++len]='#';
	for(re int i=0; i<n; ++i)
	{
		s[++len]=str[i];
		s[++len]='#';
	}
	s[++len]='\0';
}
inline void manacher()
{
	for(re int i=0,mid=0,maxx=0; i<len; ++i)
	{
		p[i]=maxx>i?min(maxx-i,p[(mid<<1)-i]):1;
		while(s[i-p[i]]==s[i+p[i]])
			++p[i];
		if(i+p[i]>maxx)
		{
			maxx=i+p[i];
			mid=i;
		}
	}
}
inline void work()
{
	solve();
	manacher();
	//printf("%s\n",s);
	for(re int i=2,l,r; i<len; ++i)
	{
		l=i-(p[i]-1),r=i;
		r=(r>>1)-1;
		l=(l-1)>>1;
		if(l<=r)
		{
			++dp1[l];
			--dp1[r+1];
		}
		l=i,r=(i+p[i]-1);
		r=(r>>1)-1;
		l=(l-1)>>1;
		if(l<=r)
		{
			++dp2[l];
			--dp2[r+1];
		}
	}
	pre[0]=dp1[0];
	suf[0]=dp2[0];
	for(re int i=1; i<n; ++i)
	{
		pre[i]=pre[i-1]+dp1[i];
		suf[i]=suf[i-1]+dp2[i];
	}
	sum[n-1]=pre[n-1];
	for(re int i=n-2; i>=0; --i)
		sum[i]=sum[i+1]+pre[i];
	ll ans=0;
	for(re int i=n-2; i>=0; --i)
		ans+=suf[i]*sum[i+1];
	printf("%lld\n",ans);
	fill(dp1,dp1+n+1,0);
	fill(dp2,dp2+n+1,0);
}
int main()
{
	while(scanf("%s",str)!=EOF)
		work();
}
