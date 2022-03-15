#include<cmath>
#include<cstdio>
using namespace std;
int n;
int main()
{
	scanf("%d",&n);
	int left=1,right=n,mid,ans=0;
//	printf("%d\n",n);
//	printf("%lf\n",6*log10(6)+1);
	while(left<=right)
	{
		mid=(left+right)>>1;
		if((mid*log10(mid)+1)>=n)
		{
//			printf("%d\n",mid);
			ans=mid;
			right=mid-1;
		}
		else
			left=mid+1;
	}
	printf("%d\n",ans);
	return 0;
}
