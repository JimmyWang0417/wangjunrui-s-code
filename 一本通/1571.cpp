#include<cstdio>
#include<cstring>
#define re register
#define ll long long
using namespace std;
inline long long read()
{
	char s=getchar();
	bool f=false;
	long long x=0;
	while(!(s>='0'&&s<='9'))
	{
		if(s=='-')
			f=true;
		s=getchar();
	}
	while(s>='0'&&s<='9')
	{
		x=(x<<1)+(x<<3)+s-'0';
		s=getchar();
	}
	return f?-x:x;
}
const int N=110;
ll dp[N][N][N],a[N],
s1[N],s2[N],s3[N];
int n;
inline void print(ll c[])
{
	for(re int i=c[0]; i>=1; i--)
		printf("%d",c[i]);
	putchar('\n');
}
inline void mark(ll c[])
{
	for(re int i=1; i<=c[0]; i++)
	{
		c[i+1]+=c[i]/10;
		c[i]%=10;
	}
	//print(c);
	while(c[c[0]+1])
	{
		c[0]++;
		c[c[0]+1]+=c[c[0]]/10;
		c[c[0]]%=10;
	}
}
inline void add(ll a[],ll b[],ll c[])
{
	c[0]=a[0]>b[0]?a[0]:b[0];
	for(re int i=1; i<=c[0]; i++)
		c[i]=a[i]+b[i];
	mark(c);
}
inline void mul(ll a1,ll a2,ll a3,ll s[])
{
	s[0]=s[1]=1;
	for(re int i=1; i<=s[0]; i++)
		s[i]*=a1;
	mark(s);
	//print(s);
	for(re int i=1; i<=s[0]; i++)
		s[i]*=a2;
//	for(re int i=0;i<=s[0];i++)
//	printf("%d\n",s[i]);
	mark(s);
	for(re int i=1; i<=s[0]; i++)
		s[i]*=a3;
	mark(s);
}
inline bool compare(ll a[],ll b[])
{
	if(a[0]!=b[0])
		return a[0]>b[0];
	for(re int i=a[0]; i>=1; i--)
		if(a[i]!=b[i])
			return a[i]>b[i];
	return false;
}
int main()
{
	n=read();
	for(re int i=1; i<=n; i++)
		a[i]=read();
	for(re int len=2; len<=n-1; len++)
		for(re int l=1,r; l<=n-len; l++)
		{
			r=l+len;
			dp[l][r][0]=60;
			for(re int k=l+1; k<r; k++)
			{
				memset(s1,0,sizeof(s1));
				memset(s2,0,sizeof(s2));
				memset(s3,0,sizeof(s3));
				mul(a[l],a[k],a[r],s1);
				add(dp[l][k],dp[k][r],s2);
				add(s1,s2,s3);
//				printf("%lld ",a[l]*a[k]*a[r]);
//				print(s1);
				if(compare(dp[l][r],s3))
					memcpy(dp[l][r],s3,sizeof(s3));
			}
		}
	print(dp[1][n]);
	return 0;
}
