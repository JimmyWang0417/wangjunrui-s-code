#include<cstdio>
#include<cctype>
#include<iostream>
#define ull unsigned long long
int n;
ull ans,maxx;
inline void dfs(ull l,ull r,ull k,int dep)
{
	//printf("%lld %lld %lld %d\n",l,r,k,dep);
	if(l==r)
		return;
	if(l+(1ull<<dep)>k)
		dfs(l,l-1+(1ull<<dep),k,dep-1);
	else
	{
		dfs(l+(1ull<<dep),r,l+(1ull<<dep)+r-k,dep-1);
		ans|=1ull<<dep;
	}
}
ull k;
int main()
{
	//freopen("code.in","r",stdin),freopen("code.out","w",stdout);
	std::cin>>n>>k;
	for(int i=0; i<=n-1; ++i)
		maxx|=(1ull<<i);
	dfs(0,maxx,k,n-1);
	for(int i=n-1; i>=0; --i)
		if(ans&(1ull<<i))
			putchar('1');
		else
			putchar('0');
	putchar('\n');
	fclose(stdin),fclose(stdout);
	return 0;
}
