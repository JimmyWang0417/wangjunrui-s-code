#include<cstdio>
#define re register
using namespace std;
const int N=4e6+10;
int n,m,a[N],maxx=-1e9,l,r;
long long sum;
int main()
{
	scanf("%d%d",&n,&m);
	for(re int i=1; i<=n; ++i)
		scanf("%d",&a[i]);
	for(re int left=1,right=1; right<=n; ++right)
	{
		sum+=a[right];
		while(sum>m)
			sum-=a[left++];
		if(sum>maxx)
		{
			l=left;
			r=right;
			maxx=sum;
		}
	}
	printf("%d %d %d\n",l,r,maxx);
	return 0;
}
