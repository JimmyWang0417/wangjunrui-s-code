#include<cstdio>
#include<cstring>
using namespace std;
int val,n;
int ans[20]= {0,1,5,2,8,3,9,2,8,7,7,8,4,7,3,8,4,1,5,4};
char str[105];
int main()
{
	while(scanf("%s",str)!=EOF)
	{
		n=strlen(str);
		if(n==1&&str[0]=='0')
			return 0;
		val=str[n-1]-'0';
		if(n>1)
			val+=(str[n-2]-'0')*10;

		printf("%d\n",	((int)ans[val%20]+val/20*4)%10);
	}
}
