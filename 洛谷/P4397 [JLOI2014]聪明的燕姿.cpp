#include <cstdio>
#include <algorithm>
#define re register
#define ll long long
using namespace std;
const int S=2e9,N=1e5;
int prime[N+5],vis[N+5],cnt;
inline void primes(int n)
{
	vis[1]=1;
	for(re int i=2; i<=n; ++i)
	{
//		printf("%d\n",vis[i]);
		if(!vis[i])
		{
			vis[i]=i;
			prime[++cnt]=i;
		}
		for(re int j=1; j<=cnt; ++j)
		{
			if(vis[i]<prime[j]||prime[j]*i>n)
				break;
			vis[i*prime[j]]=prime[j];
		}
	}
//	for(re int i=1; i<=10; ++i)
//		printf("%d ",vis[i]);
}
int ans[10000000],tot;
inline bool isprime(int n)
{
	if(n==1)
		return false;
	if(n<=N)
		return vis[n]==n;
	for(re int i=1; prime[i]*prime[i]<=n; ++i)
		if(n%prime[i]==0)
			return false;
	return true;
}
inline void dfs(int pos,ll now,ll res)
{
	if(now==1)
	{
		ans[++tot]=res;
		return;
	}
	if(prime[pos]<now&&isprime(now-1))
		ans[++tot]=res*(now-1);
	ll p,tmp;
	for(re int i=pos; prime[i]*prime[i]<=now; ++i)
	{
		tmp=prime[i];
		p=prime[i]+1;
		for(; p<=now; tmp*=prime[i],p+=tmp)
			if(now%p==0)
				dfs(i+1,now/p,res*tmp);
	}
}
int main()
{
	int m;
	primes(N);
//	printf("%d\n",cnt);
//	for(re int i=1;i<=25; ++i)
//		printf("%d ",prime[i]);
	while(scanf("%d",&m)!=EOF)
	{
		dfs(1,m,1);
		printf("%d\n",tot);
		sort(ans+1,ans+1+tot);
		for(re int i=1; i<=tot; ++i)
			printf("%d ",ans[i]);
		if(tot)
			putchar('\n');
		tot=0;
	}
}
