#include<cstdio>
#include<cstring>
#include<algorithm>
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
const int N=205;
int dp[N][N][N],color[N],n;
inline int DP(int i,int j,int k)
{
	if(i>j)
		return 0;
	int &ans=dp[i][j][k];
	if(ans>=0)
		return ans;
	int q=j;
	while(color[q]==color[j]&&q>=i)
		--q;
	++q;
	ans=DP(i,q-1,0)+(j-q+1+k)*(j-q+1+k);
	for(re int p=i; p<q; ++p)
		if(color[p]==color[j]&&color[p]!=color[p+1])
			ans=max(ans,DP(p+1,q-1,0)+DP(i,p,j-q+1+k));
	return ans;
}
int main()
{
	int T,kase=0;
	read(T);
	while(T--)
	{
		read(n);
		memset(dp,-1,sizeof(dp));
		for(re int i=0; i<n; ++i)
			read(color[i]);
		printf("Case %d: %d\n",++kase,DP(0,n-1,0));
	}
}

