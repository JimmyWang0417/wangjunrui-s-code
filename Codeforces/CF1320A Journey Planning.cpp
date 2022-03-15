#include<cstdio>
#include<algorithm>
#include<iostream>
#include<cmath>
#include<vector>
#define re register
#define int  long long
#define calc(x) (x+M)
using namespace std;
const int N=2e6+5,M=1e6;
int n,b[N],ans[N],maxx=-1;
signed main()
{
	ios::sync_with_stdio(false);
	cin>>n;
	for(re int i=1; i<=n; ++i)
		cin>>b[i];
	for(re int i=1; i<=n; ++i)
		ans[calc(b[i]-i)]+=b[i];
	for(re int i=1; i<=n; ++i)
		maxx=max(maxx,ans[calc(b[i]-i)]);
	printf("%lld\n",maxx);
	return 0;
}
