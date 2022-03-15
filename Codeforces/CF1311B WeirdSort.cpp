#include<iostream>
#include <algorithm>
#define re register
using namespace std;
int a[105],p[105];
inline void work()
{
	int n,m;
	cin>>n>>m;
	for(re int i=1; i<=n; ++i)
		cin>>a[i];
	for(re int i=1; i<=m; ++i)
		cin>>p[i];
	sort(p+1,p+1+m);
	for(re int now=1; now<=n; ++now)
	{
		for(re int i=1; i<=m; ++i)
		{
			if(a[p[i]]>a[p[i]+1]&&p[i]+1<=n)
				swap(a[p[i]],a[p[i]+1]);
		}
	}
	for(re int i=1; i<n; ++i)
		if(a[i]>a[i+1])
		{
			printf("NO\n");
			return;
		}
	printf("YES\n");
}
int main()
{
	ios::sync_with_stdio(false);
	int T;
	cin>>T;
	while(T--)
		work();
	return 0;
}
