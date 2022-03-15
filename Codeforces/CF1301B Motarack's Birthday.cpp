#include<iostream>
#include<algorithm>
#define re register
using namespace std;
const int N=100005;
int a[N],p[N],cnt;
inline void work()
{
	int n;
	cin>>n;
	for(re int i=1; i<=n; ++i)
		cin>>a[i];
	int maxx=~0x7fffffff,minn=0x7fffffff;
	for(re int i=1; i<=n; ++i)
		if(a[i]==-1)
		{
			if(i>1&&a[i-1]!=-1)
			{
				maxx=max(maxx,a[i-1]);
				minn=min(minn,a[i-1]);
			}
			if(i<n&&a[i+1]!=-1)
			{
				maxx=max(maxx,a[i+1]);
				minn=min(minn,a[i+1]);
			}
		}
	int k=(maxx+minn)/2,maxn=~0x7fffffff;
	if(a[1]==-1)
		a[1]=k;
	for(re int i=2; i<=n; ++i)
	{
		if(a[i]==-1)
			a[i]=k;
		maxn=max(maxn,abs(a[i]-a[i-1]));
	}
	printf("%d %d\n",maxn,k);
}
int main()
{
	int T;
	ios::sync_with_stdio(false);
	cin>>T;
	while(T--)
		work();
	return 0;
}
