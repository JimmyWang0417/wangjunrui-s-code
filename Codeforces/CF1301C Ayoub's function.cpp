#include<iostream>
#include<cstdio>
using namespace std;
int main()
{
	ios::sync_with_stdio(false);
	int T;
	cin>>T;
	while(T--)
	{
		int n,m;
		cin>>n>>m;
		int cnt=(n-m)%(m+1),sum=(n-m)/(m+1)+1;
		long long extra=1ll*cnt*sum*(sum+1)/2;
		cnt=(m+1)-cnt,--sum;
		extra+=1ll*cnt*sum*(sum+1)/2;
		printf("%lld\n",1ll*n*(n+1)/2-extra);
	}
	return 0;
}
