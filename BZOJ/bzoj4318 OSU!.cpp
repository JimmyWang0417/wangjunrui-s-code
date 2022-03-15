#include<cstdio>
#define re register
using namespace std;
int n;
double len1,len2,ans;
int main()
{
	scanf("%d",&n);
	for(re int i=1; i<=n; ++i)
	{
		static double p;
		scanf("%lf",&p);
		ans=ans+(3*len2+3*len1+1)*p;
		len2=(len2+2*len1+1)*p;
		len1=(len1+1)*p;
	}
	printf("%.1lf\n",ans);
}
