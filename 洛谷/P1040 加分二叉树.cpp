#include<cstdio>
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
int a[40],root[40][40],n;
long long dp[40][40];
inline long long DP(int l,int r)
{
	if(dp[l][r]>0)
		return dp[l][r];
	if(l==r)
		return a[l];
	if(r<l)
		return 1;
	for(re int i=l; i<=r; i++)
	{
		int v=DP(l,i-1)*DP(i+1,r)+a[i];
		if(v>dp[l][r])
		{
			dp[l][r]=v;
			root[l][r]=i;
		}
	}
	return dp[l][r];
}
inline void print(int l,int r)
{
	if(r<l)
		return;
	if(l==r)
	{
		printf("%d ",l);
		return;
	}
	printf("%d ",root[l][r]);
	print(l,root[l][r]-1);
	print(root[l][r]+1,r);
}
int main()
{
	read(n);
	for(re int i=1; i<=n; i++)
		read(a[i]);
	for(re int i=1; i<=n; i++)
		dp[i][i]=a[i];
	printf("%lld\n",DP(1,n));
	print(1,n);
	putchar('\n');
	return 0;
}

