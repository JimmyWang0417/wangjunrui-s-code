#include<iostream>
using namespace std;
int main()
{
	ios::sync_with_stdio(false);
	int T;
	cin>>T;
	while(T--)
	{
		int a,b;
		cin>>a>>b;
		if(a==b)
		{
			printf("0\n");
			continue;
		}
		if((b-a)&1)
			printf("%d\n",1+(a>b));
		else
			printf("%d\n",a>b?1:2);
	}
	return 0;
}
