#include<cstdio>
#include<cstring>
#define re register
using namespace std;
const int LEN=200000;
int n,p[LEN],sum[LEN],ans;
char a[LEN],b[LEN];
inline void pre()
{
	p[1]=0;
	for(re int i=1,j=0; i<n; i++)
	{
		while(j&&a[i+1]!=a[j+1])
			j=p[j];
		if(a[i+1]==a[j+1])
			j++;
		p[i+1]=j;
	}
}
int main()
{
	scanf("%s",a+1);
	n=strlen(a+1);
	pre();
	for(re int i=1; i<=n; i++)
		sum[i]=1;
	for(re int i=n; i>1; i--)
		sum[p[i]]+=sum[i];
	for(re int i=2; i<=n; i+=2)
		ans+=sum[i];
	printf("%d\n",ans);
	return 0;
}
