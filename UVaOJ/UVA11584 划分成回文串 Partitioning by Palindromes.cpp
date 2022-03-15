#include<cstdio>
#include<cstring>
#define re register
#define min(x,y) (x<y?x:y)
using namespace std;
template<typename T>
inline void read(T&x)
{
	x=0;
	char s=getchar();
	bool f=false;
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
	if(f)
		x=(~x)+1;
}
int t,n,dp[1010];
char s[1010];
bool flag[1010][1010];
int main()
{
	read(t);
	while(t--)
	{
		scanf("%s",s+1);
		n=strlen(s+1);
		memset(flag,false,sizeof(flag));
		for(re int i=1; i<=n; i++)
		{
			dp[i]=i;
			for(re int j=i; j>=1; j--)
			{
				if(i==j||s[i]==s[j]&&(j+1==i||flag[j+1][i-1]))
				{
					flag[j][i]=true;
					if(j==0)
						dp[i]=1;
					else
						dp[i]=min(dp[i],dp[j-1]+1);
				}
			}
		}
		printf("%d\n",dp[n]);
	}
	return 0;
}
