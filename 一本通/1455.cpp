#include<cstdio>
using namespace std;
#define inf 0x3f3f3f3f
#define N 1000010
#define ull unsigned long long
#define k1 27
char s1[N],s2[N];
int n,m,ans=0,t;
ull sum[N],power[N],s;
int wjr_strlen(const char *a)
{
	int len=0;
	while(a[len]!=0)len++;
	return len;
}
int main()
{
	power[0]=1;
	scanf("%d",&t);
	for(int i=1; i<1000000; i++)
		power[i]=power[i-1]*k1;
	while (t--)
	{
		scanf("%s%s",s1+1,s2+1);
		n=wjr_strlen(s1+1);
		m=wjr_strlen(s2+1);
		ans=s=sum[0]=0;
		for(int i=1; i<=m; i++)
			sum[i]=sum[i-1]*k1+(ull)(s2[i]-'A'+1);
		for(int i=1; i<=n; i++)
			s=s*k1+(ull)(s1[i]-'A'+1);
		for(int i=0; i<=m-n; i++)
			if(s==sum[i+n]-sum[i]*power[n])
				ans++;
		printf("%d\n",ans);
	}
	return 0;
}
