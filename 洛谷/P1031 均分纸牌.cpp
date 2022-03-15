/*https://www.luogu.org/problemnew/show/P1031*/
#include<cstdio>
using namespace std;
int n,a[101],sum,ans;
int main()
{
	scanf("%d",&n);
	for(register int i=1; i<=n; i++)
	{
		scanf("%d",&a[i]);
		sum+=a[i];
	}
	sum/=n;
	for(register int i=1;i<=n;i++)
	a[i]-=sum;
	for(register int i=1;i<n;i++)
	  if(a[i]!=0)
	    {
	    	a[i+1]+=a[i];
	    	a[i]=0;
	    	ans++;
		}
	printf("%d\n",ans);
}
