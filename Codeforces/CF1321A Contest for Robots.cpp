#include<cstdio>
#include<algorithm>
#include<iostream>
#include<cmath>
#define re register
using namespace std;
const int N=105;
bool flag[N];
int a[N],b[N],cnt,suma,sumb;
int main()
{
	ios::sync_with_stdio(false);
	int n;
	cin>>n;
	for(re int i=1; i<=n; ++i)
	{
		cin>>a[i];
		suma+=a[i];
	}
	for(re int i=1; i<=n; ++i)
	{
		cin>>b[i];
		sumb+=b[i];
	}
	for(re int i=1; i<=n; ++i)
		if(a[i]==1&&b[i]==0)
			++cnt;
	if(cnt==0)
		printf("-1\n");
	else
	{
		int ans=ceil((double)max(sumb-suma+1,0)/cnt)+1;
		printf("%d\n",ans);

	}
	return 0;
}
