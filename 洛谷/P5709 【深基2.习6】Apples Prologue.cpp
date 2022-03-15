#include<cstdio>
#include<algorithm>
int main()
{
	int m,t,s,ans;
	scanf("%d%d%d",&m,&t,&s);
	if(t==0)
	{
		printf("%d\n",m);
		return 0;
	}
	ans=s/t;
	if(s%t!=0)
		++ans;
	printf("%d\n",std::max(0,m-ans));
}
