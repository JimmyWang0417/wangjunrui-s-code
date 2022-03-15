#include<cstdio>
#define re register
#define N 1510
using namespace std;
inline int min(int a,int b)
{
	return a<b?a:b;
}
inline int read()
{
	char s=getchar();
	bool f=false;
	int x=0;
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
struct node
{
	int num,child[N];
} a[N];
bool b[N];
int dp[N][2],n,root,x;
inline void DP(int x)
{
	dp[x][1]=1;
	dp[x][0]=0;
	if(a[x].num==0)return;
	for(re int i=1; i<=a[x].num; i++)
	{
		DP(a[x].child[i]);
		dp[x][0]+=dp[a[x].child[i]][1];
		dp[x][1]+=min(dp[a[x].child[i]][1],dp[a[x].child[i]][0]);
	}
}
int main()
{
	n=read();
	for(re int i=1; i<=n; i++)
	{
		x=read();
		a[x].num=read();
		for(re int j=1; j<=a[x].num; j++)
		{
			a[x].child[j]=read();
			b[a[x].child[j]]=true;
		}
	}
	root=0;
	while(b[root])root++;
	DP(root);
	printf("%d\n",min(dp[root][0],dp[root][1]));
	return 0;
}
