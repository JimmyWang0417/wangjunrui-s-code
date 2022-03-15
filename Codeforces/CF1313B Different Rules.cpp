#include<cstdio>
#include <iostream>
#include <algorithm>
#define int long long
using namespace std;
inline void work()
{
	int n,x,y;
	cin>>n>>x>>y;
	int now=x+y;
	printf("%lld %lld\n",min(max(now+1-n,1ll),n),min(now-1,n));
}
signed main()
{
	int T;
	ios::sync_with_stdio(false);
	cin>>T;
	while(T--)
		work();
}
