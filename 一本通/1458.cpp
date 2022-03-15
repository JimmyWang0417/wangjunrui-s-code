#include<cstdio>
using namespace std;
#define N 1000002
#define ull unsigned long long
#define b 1000
char s[N];
ull sum[N],power[N]= {1};
int n;
int wjr_strlen(const char *a)
{
	int len=0;
	while(a[len]!=0)len++;
	return len;
}
int main()
{
	register int i,m;
	for(i=1; i<=100000; i++)
		power[i]=power[i-1]*b;
	while(scanf("%s",s+1)==1)
	{
		sum[0]=0;
		n=wjr_strlen(s+1);
		for(i=1; i<=n; i++)
			sum[i]=sum[i-1]*b+(ull)(s[i]);
		for(m=1; m<=n; m++)
			if(sum[m]==sum[n]-sum[n-m]*power[m])
				printf("%d ",m);
		putchar('\n');
	}
	return 0;
}
