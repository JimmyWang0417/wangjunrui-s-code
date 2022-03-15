#include <iostream>
#include <algorithm>
#include <cstring>
#include <cstdio>
#include <cmath>
#define re register
using namespace std;
const int N=2e5+5;
int T;
inline void work()
{
	int a,b,c;
	int ansa,ansb,ansc,ans=0x7fffffff;
	cin>>a>>b>>c;
	for(re int nowa=1; nowa<=10000; ++nowa)
	{
		for(re int nowb=nowa; nowb<=100000; nowb+=nowa)
		{
			int sum=abs(nowb-b)+abs(nowa-a);
			int nc=c/nowb,nowc;
			if(abs(nc*nowb-c)<abs((nc+1)*nowb-c))
				nowc=nc*nowb;
			else
				nowc=(nc+1)*nowb;
			sum+=abs(nowc-c);
			if(sum<ans)
			{
				ans=sum;
				ansa=nowa,ansb=nowb,ansc=nowc;
			}
		}
	}
	printf("%d\n%d %d %d\n",ans,ansa,ansb,ansc);
}
signed main()
{
	ios::sync_with_stdio(false);
	cin>>T;
	while(T--)
		work();
	return 0;
}
