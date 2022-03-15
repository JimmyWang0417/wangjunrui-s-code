#include<cstdio>
#include<cstring>
#define re register
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
#define min(x,y) (x>y?y:x)
const int oo=0x3f3f3f3f;
int n,T,M1,M2,t[110],x,sum,dp[10010][110],kase;
bool has_train[110][10010][2];
int main()
{
	while(read(n),n!=0)
	{
		kase++;
		read(T);
		memset(t,0,sizeof(t));
		memset(has_train,0,sizeof(has_train));
		for(int i=1; i<=n-1; i++)
			read(t[i]);//t[i]:i~i+1站时间
		read(M1);
		for(int i=1; i<=M1; i++)
		{
			int t1;//左站出发时间
			read(t1);
			int sum=t1;
			for(int j=1; j<=n; j++)
			{
				has_train[j][sum][0]= 1;
				sum+=t[j];
			}
		}
		read(M2);
		for(int i=1; i<=M2; i++)
		{
			int t2;//右站出发时间
			read(t2);
			int sum=t2;
			for(int j=n; j>=1; j--)
			{
				has_train[j][sum][1]=1;
				sum+=t[j-1];
			}
		}
		for(int i=1; i<=n-1; i++)
			dp[T][i]=oo;
		dp[T][n] = 0;
		for(int i=T-1; i>=0; i--)
			for(int j=1; j<=n; j++)
			{
				dp[i][j]=dp[i+1][j]+1;
				if(j<n&&has_train[j][i][0]&&i+t[j]<=T)
					dp[i][j]=min(dp[i][j],dp[i+t[j]][j+1]);
				if(j>1&&has_train[j][i][1]&&i+t[j-1]<=T)
					dp[i][j]=min(dp[i][j],dp[i+t[j-1]][j-1]);
			}
		printf("Case Number %d: ",kase) ;
		if(dp[0][1] >= oo) puts("impossible");
		else printf("%d\n",dp[0][1]);
	}
	return 0;
}

