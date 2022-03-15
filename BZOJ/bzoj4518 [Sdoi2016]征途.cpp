#include<cstdio>
#include<cstring>
#define re register
#define ll long long
template<typename T>
inline void read(T&x)
{
	x=0;
	char s=(char)getchar();
	bool f=false;
	while(!(s>='0'&&s<='9'))
	{
		if(s=='-')
			f=true;
		s=(char)getchar();
	}
	while(s>='0'&&s<='9')
	{
		x=(x<<1)+(x<<3)+s-'0';
		s=(char)getchar();
	}
	if(f)
		x=(~x)+1;
}
const ll INF=1e18;
const int N=3005;
int n,m;
ll sum[N],dp[N][N];
inline void DP(int id,int l,int r,int L,int R)
{
	int mid=l+r>>1,k=n+1;
	ll &ans=dp[id][mid];
	ans=INF;
	ll tmp;
	for(re int i=L; i<=R&&i<=mid; ++i)
	{
		tmp=dp[id-1][i]+(sum[mid]-sum[i])*(sum[mid]-sum[i]);
		if(ans>tmp)
		{
			ans=tmp;
			k=i;
		}
	}
	if(l<mid)
		DP(id,l,mid-1,L,k);
	if(mid<r)
		DP(id,mid+1,r,k,R);
}
int main()
{
	read(n);
	read(m);
	for(re int i=1; i<=n; ++i)
	{
		read(sum[i]);
		sum[i]+=sum[i-1];
	}
	for(re int i=1; i<=n; ++i)
		dp[1][i]=sum[i]*sum[i];
	for(re int i=2; i<=m; ++i)
		DP(i,1,n,1,n);
	printf("%lld\n",m*dp[m][n]-sum[n]*sum[n]);
	return 0;
}
