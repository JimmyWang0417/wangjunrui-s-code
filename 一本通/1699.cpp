#include<cstdio>
#include<cstring>
#include<algorithm>
#define re register
using namespace std;
const int LEN=2e6+10;
int ans[LEN],n,pre,p[LEN],kase;
char a[LEN];
inline void kmp(int l,int r)
{
	p[1]=0;
	re int i=l+1,j=0;
	for(; i<=r; i++)
	{
		while(j&&a[i]!=a[j+l])
			j=p[j];
		if(a[i]==a[j+l])
			j++;
		p[i-l+1]=j;
	}
	int len=r-l+1;
	j=p[len];
	for(re int i=1; i<=len; i++)
		ans[i]++;
	while(j)
	{
		ans[len-j+1]--;
		j=p[j];
	}
}
int main()
{
	while(scanf("%s",a+1)!=EOF)
	{
		n=strlen(a+1);
		pre=1;
		for(re int i=1; i<=n; i++)
			a[i+n]=a[i];
		a[n*2+1]='\0';
		//printf("%s",a+1);
		for(re int i=2; i<=n*2; i++)
			if(a[i]==a[i-1])
			{
				kmp(pre,i-1);
				pre=i;
			}
		kmp(pre,n*2);
		printf("Case %d: ",++kase);
		for(re int i=0; i<n; i++)
			putchar((bool)ans[n-i]+'0');
		putchar('\n');
		fill(ans+1,ans+1+n,0);
	}
}
