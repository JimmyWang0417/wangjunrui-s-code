#include<cstdio>
#include<cmath>
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
const int N=5e5+5;
int n,a[N];
double dp1[N],dp2[N];
inline void DP(int l,int r,int L,int R,double *dp)
{
	//printf("%d %d %d %d\n",l,r,L,R);
	int mid=l+r>>1,k=n+1;
	double &ans=dp[mid];
	ans=0.0;
	for(re int i=L; i<=R&&i<=mid; ++i)
	{
		double tmp=a[i]-a[mid]+sqrt(abs(i-mid));
		//printf("%lf ",tmp);
		if(tmp>=ans)
		{
			ans=tmp;
			k=i;
		}
	}
	if(l<mid)
		DP(l,mid-1,L,k,dp);
	if(mid<r)
		DP(mid+1,r,k,R,dp);
	//putchar('\n');
}
int main()
{
	read(n);
	for(re int i=1; i<=n; ++i)
		read(a[i]);
	DP(1,n,1,n,dp1);
	for(re int i=1; i<=(n>>1); ++i)
		swap(a[i],a[n-i+1]);
	DP(1,n,1,n,dp2);
//	for(re int i=1; i<=n; ++i)
//		printf("%lf %lf\n",dp1[i],dp2[n-i+1]);
	for(re int i=1; i<=n; ++i)
		printf("%d\n",max((int)ceil(max(dp1[i],dp2[n-i+1])),0));
	return 0;
}
