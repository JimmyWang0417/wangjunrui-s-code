#include<cstdio>
using namespace std;
#define b 27
#define ull unsigned long long
char s[1000002];
ull power[1000000]= {1},sum[1000001];
int m;
int wjr_strlen(const char *a)
{
	int len=0;
	while(a[len]!=0)len++;
	return len;
}
int main()
{
	for(int i=1; i<1000000; i++)
		power[i]=power[i-1]*b;
	scanf("%s",s+1);
	while(s[1]!='.')
	{
		m=wjr_strlen(s+1);
		for(int n=1,i; n<=m; n++)
		{
			sum[0]=0;
			if(m%n==0)
			{
				for(i=1; i<=m; i++)
					sum[i]=sum[i-1]*b+(ull)(s[i]-'a'+1);
				for(i=0; i<=m-n; i+=n)
					if(sum[n]!=sum[i+n]-sum[i]*power[n])
						break;
				if(i>m-n)
				{
					printf("%d\n",m/n);
					break;
				}
			}
		}
		scanf("%s",s+1);
	}
	return 0;
}
