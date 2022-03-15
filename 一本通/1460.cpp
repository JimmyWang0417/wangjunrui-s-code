#include<cstdio>
#include<iostream>
using namespace std;
#define r register
#define ull unsigned long long
#define B 131
int n,m,a,b;
char s[int(5*1e5+2)];
ull power[int(5*1e5+2)]= {1},sum[int(5*1e5+2)],ans,s1,s2;
int main()
{
	scanf("%d%s",&n,s+1);
	for(r int i=1; i<=n; i++)
	{
		power[i]=power[i-1]*B;
		sum[i]=sum[i-1]*B+(ull)s[i];
	}
	scanf("%d",&m);
	while(m--)
	{
		scanf("%d%d",&a,&b);
		for(r int i=a; i<=b; i++)
			if((b-a+1)%(i-a+1)==0)
			{
				ans=0;
				for(r int j=0; j<=b-a; j+=i-a+1)
					ans+=power[j];
				s1=sum[b]-sum[a-1]*power[b-a+1];
				s2=(sum[i]-sum[a-1]*power[i-a+1])*ans;
				if(s1==s2)
				{
					printf("%d\n",i-a+1);
					break;
				}
			}
	}
}

