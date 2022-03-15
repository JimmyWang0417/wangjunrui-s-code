#include<cmath>
#include<cstdio>
#include<algorithm>
#define re register
#define ll long long
using namespace std;
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
#define update(x,v) if((x)<0||(x)>(v))(x)=(v)
const int N=105,X=N*N<<1;
const ll INF=1ll<<62;
int n,d;
ll x[X],dp[2][X],h[N];
inline void solve()
{
	read(n);
	read(d);
	for(re int i=0; i<n; ++i)
		read(h[i]);
	if(abs(h[0]-h[n-1])>(n-1)*d)
	{
		printf("impossible\n");
		return;
	}
	int nx=0;
	for(re int i=0; i<n; ++i)
		for(re int j=-n+1; j<=n-1; ++j)
			x[nx++]=h[i]+j*d;
	stable_sort(x,x+nx);
	nx=unique(x,x+nx)-x;
	re int t=0;
	for(re int i=0; i<nx; ++i)
	{
		if(x[i]==h[0])
			dp[0][i]=0ll;
		else
			dp[0][i]=INF;
	}
	for(re int i=1,k; i<n; ++i)
	{
		k=0;
		for(re int j=0; j<nx; ++j)
		{
			while((k<nx&&x[k]<x[j]-d)||(k+1<nx&&x[k+1]<=x[j]+d&&dp[t][k+1]<=dp[t][k]))
				++k;
			dp[t^1][j]=(dp[t][k]==INF?INF:dp[t][k]+abs(x[j]-h[i]));
		}
		t^=1;
	}
	for(re int i=0; i<nx; ++i)
		if(x[i]==h[n-1])
		{
			printf("%lld\n",dp[t][i]);
			return;
		}
}
int main()
{
	int T;
	read(T);
	while(T--)
		solve();
}
