#include<cstdio>
#define re register
int st[(int)1e7+10],n;
int main()
{
	re int top=0;
	scanf("%d",&n);
	while(1)
	{
		st[++top]=n;
		if(n==1)
			break;
		if(n&1)
			n=n*3+1;
		else
			n/=2;
	}
	while(top)
	printf("%d ",st[top--]);
	return 0;
}
