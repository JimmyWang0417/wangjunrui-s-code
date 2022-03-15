#include<cstdio>
#include<cstring>
#define re register
using namespace std;
int n,K,len,digit[205];
char str[205];
//int a[205];
bool dp[205][205][1005];
struct node
{
	int i,j,val;
	node() {}
	node(int ii,int jj,int v):i(ii),j(jj),val(v) {}
} pre[205][205][1005];
inline void write(int pos,int i,int j)
{
	if(pos==0)
		return;
	write(pos-1,pre[pos][i][j].i,pre[pos][i][j].j);
	printf("%d",pre[pos][i][j].val);
}
int main()
{
	scanf("%s%d",str,&K);
	n=strlen(str);
	for(re int i=n; i>=1; --i)
		digit[i]=str[i-1]-'0';
//	for(re int i=1; i<=n; ++i)
//		printf("%d",a[i]);
	for(re int i=K; i>=1; --i)
	{
		dp[1][digit[1]!=i][i%K]=true;
		pre[1][digit[1]!=i][i%K]=node(0,0,i);
	}
	for(re int pos=2; pos<=n; ++pos)
		for(re int i=0; i<=n; ++i)
			for(re int j=0; j<K; ++j)
				if(dp[pos-1][i][j])
				{
					for(re int k=0; k<=9; ++k)
					{
						dp[pos][i+(digit[pos]!=k)][(j*10+k)%K]=true;
						pre[pos][i+(digit[pos]!=k)][(j*10+k)%K]=node(i,j,k);
					}
				}
//	for(re int pos=1; pos<=n; ++pos)
//	{
//		for(re int i=0; i<=n; ++i)
//		{
//			for(re int j=0; j<K; ++j)
//				printf("\t dp[%d][%d][%d]=%d",pos,i,j,dp[pos][i][j]);
//			putchar('\n');
//		}
//		putchar('\n');
//	}
	for(re int i=0; i<=n; ++i)
		if(dp[n][i][0])
		{
			write(n,i,0);
			putchar('\n');
			return 0;
		}
	printf("-1\n");
	return 0;
}
