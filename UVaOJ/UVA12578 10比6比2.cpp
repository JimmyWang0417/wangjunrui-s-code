#include<cstdio>
#include<cmath>
using namespace std;
const double PI=acos(-1);
int main()
{
	int T;
	double l,all,extra;
	scanf("%d",&T);
	while(T--)
	{
		scanf("%lf",&l);
		extra=PI*l*l*0.04;
		all=l*l*0.6;
		printf("%.2lf %.2lf\n",extra,all-extra);
	}
	return 0;
}
